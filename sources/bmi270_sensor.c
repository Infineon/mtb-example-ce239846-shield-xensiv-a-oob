/******************************************************************************
* File Name:   bmi270_sensor.c
*
* Description: This file uses sensor-motion-bmi270 library APIs to demonstrate
*              the use of BMI270 motion sensor.
*
*******************************************************************************
* Copyright 2024, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

/*******************************************************************************
* Header Files
*******************************************************************************/
#include "sensors_task.h"
#include <stdlib.h>
#include "ID_SCREEN_04.h"

/*******************************************************************************
* Global Variables
*******************************************************************************/
typedef enum
{
    ORIENTATION_NULL            = 0,    /* Default orientation state used for initialization purposes */
    ORIENTATION_TOP_EDGE        = 1,    /* Top edge of the board points towards the ceiling */
    ORIENTATION_BOTTOM_EDGE     = 2,    /* Bottom edge of the board points towards the ceiling */
    ORIENTATION_LEFT_EDGE       = 3,    /* Left edge of the board (USB connector side) points towards the ceiling */
    ORIENTATION_RIGHT_EDGE      = 4,    /* Right edge of the board points towards the ceiling */
    ORIENTATION_DISP_UP         = 5,    /* Display faces up (towards the sky/ceiling) */
    ORIENTATION_DISP_DOWN       = 6     /* Display faces down (towards the ground) */
} orientation_t;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
static cy_rslt_t motion_sensor_update_orientation(orientation_t *orientation_result);

/*******************************************************************************
* Function Name: bmi270_task
*********************************************************************************
* Summary: Reads the BMI270 sensor data to the shield orientation.
* Updates the shield orientation on the display and serial terminal.
*
* Parameters:
*  void
*
* Return:
*
*******************************************************************************/
void bmi270_task(void)
{
    /* Status variable to indicate the result of various operations */
    cy_rslt_t result;

    /* Variable used to store the orientation information */
    orientation_t orientation;

    char *status[] = {"DISP_UP", "DISP_DOWN", "TOP_EDGE",
            "BOTTOM_EDGE", "LEFT_EDGE", "RIGHT_EDGE"};

    const uint8_t button_press_count_init = button_press_count;

    /* Updates the screen on the display */
    APPW_SetVarData(btn_stat, BMI270_COUNT);

    printf("\x1b[2J\x1b[;H");
    printf("***********************************************************\r\n");
    printf("                 BMI270: Motion Sensor                     \r\n");
    printf("***********************************************************\r\n\n");
    printf("Press the USER Button SW2 to change the sensor\r\n\n");

    for(;;)
    {
        /* Get current orientation */
        result = motion_sensor_update_orientation(&orientation);
        if(CY_RSLT_SUCCESS != result)
        {
            CY_ASSERT(0);
        }
        switch(orientation)
        {
            /* Updates the sensor data on the display and serial terminal */
            case ORIENTATION_TOP_EDGE:
                APPW_SetText(ID_SCREEN_04, ID_TEXT_02, status[2]);
                printf("Orientation = TOP_EDGE\r\n\n");
                break;
            case ORIENTATION_BOTTOM_EDGE:
                APPW_SetText(ID_SCREEN_04, ID_TEXT_02, status[3]);
                printf("Orientation = BOTTOM_EDGE\r\n\n");
                break;
            case ORIENTATION_LEFT_EDGE:
                APPW_SetText(ID_SCREEN_04, ID_TEXT_02, status[4]);
                printf("Orientation = LEFT_EDGE\r\n\n");
                break;
            case ORIENTATION_RIGHT_EDGE:
                APPW_SetText(ID_SCREEN_04, ID_TEXT_02, status[5]);
                printf("Orientation = RIGHT_EDGE\r\n\n");
                break;
            case ORIENTATION_DISP_UP:
                APPW_SetText(ID_SCREEN_04, ID_TEXT_02, status[0]);
                printf("Orientation = DISP_UP\r\n\n");
                break;
            case ORIENTATION_DISP_DOWN:
                APPW_SetText(ID_SCREEN_04, ID_TEXT_02, status[1]);
                printf("Orientation = DISP_DOWN\r\n\n");
                break;
            default:
                break;
        }
        vTaskDelay(500/portTICK_PERIOD_MS);

        if (button_press_count_init != button_press_count)
        {
            break;
        }
    }
}

/*******************************************************************************
 * Function Name: motion_sensor_update_orientation
 ********************************************************************************
 * Summary:
 *  Function that updates the orientation status to one of the 6 types,
 *  'ORIENTATION_UP, ORIENTATION_DOWN, TOP_EDGE, BOTTOM_EDGE,
 *  LEFT_EDGE, and RIGHT_EDGE'. This functions detects the axis that is most perpendicular
 *  to the ground based on the absolute value of acceleration in that axis.
 *  The sign of the acceleration signifies whether the axis is facing the ground
 *  or the opposite.
 *
 * Return:
 *  CY_RSLT_SUCCESS upon successful orientation update, else a non-zero value
 *  that indicates the error.
 *
 *******************************************************************************/
static cy_rslt_t motion_sensor_update_orientation(orientation_t *orientation_result)
{
    /* Status variable */
    cy_rslt_t result = CY_RSLT_SUCCESS;
    int16_t abs_x, abs_y, abs_z;

    mtb_bmi270_data_t sens_data = {0};

    /* Get the motion sensor object */
    bmi_dev = shield_xensiv_a_get_motion_sensor();

    /* Read x, y, z components of acceleration */
    result =  mtb_bmi270_read(bmi_dev, &sens_data);
    if (CY_RSLT_SUCCESS != result)
    {
        printf("Reading IMU data failed\r\n");
    }
    abs_x = abs(sens_data.sensor_data.acc.x);
    abs_y = abs(sens_data.sensor_data.acc.y);
    abs_z = abs(sens_data.sensor_data.acc.z);

    if ((abs_z > abs_x) && (abs_z > abs_y))
        {
            if (sens_data.sensor_data.acc.z < 0)
            {
                /* Display faces down (towards the ground) */
                *orientation_result = ORIENTATION_DISP_DOWN;
            }
            else
            {
                /* Display faces up (towards the sky/ceiling) */
                *orientation_result = ORIENTATION_DISP_UP;
            }
        }
        /* Y axis (parallel with shorter edge of board) is most aligned with
         * gravity.
         */
        else if ((abs_y > abs_x) && (abs_y > abs_z))
        {
            if (sens_data.sensor_data.acc.y > 0)
            {
                /* Display has an inverted landscape orientation */
                *orientation_result = ORIENTATION_TOP_EDGE;
            }
            else
            {
                /* Display has landscape orientation */
                *orientation_result = ORIENTATION_BOTTOM_EDGE;
            }
        }
        /* X axis (parallel with longer edge of board) is most aligned with
         * gravity.
         */
        else
        {
            if (sens_data.sensor_data.acc.x< 0)
            {
                /* Display has an inverted portrait orientation */
                *orientation_result = ORIENTATION_LEFT_EDGE;
            }
            else
            {
                /* Display has portrait orientation */
                *orientation_result = ORIENTATION_RIGHT_EDGE;
            }
        }
    return result;
}

/* [] END OF FILE */
