/******************************************************************************
* File Name:   bmm350_sensor.c
*
* Description: This file uses sensor-orientation-bmm350 library APIs to
*              demonstrate the use of BMM350 magnetometer sensor.
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
#include "ID_SCREEN_05.h"

/*******************************************************************************
* Function Name: bmm350_task
*********************************************************************************
* Summary: Reads the magnetometer data x, y, z axes of the shield from
* the BMM350 sensor. Updates the sensor data on the display and serial terminal.
*
* Parameters:
*  void
*
* Return:
*
*******************************************************************************/
void bmm350_task(void)
{
    char disp_string1[15] = " ";
    char disp_string2[15] = " ";
    char disp_string3[15] = " ";

    mtb_bmm350_data_t mag_data;

    const uint8_t button_press_count_init = button_press_count;

    /* Updates the screen on the display */
    APPW_SetVarData(btn_stat, BMM350_COUNT);

    printf("\x1b[2J\x1b[;H");
    printf("***********************************************************\r\n");
    printf("               BMM350: Magnetometer Sensor                 \r\n");
    printf("***********************************************************\r\n\n");
    printf("Press the USER Button SW2 to change the sensor\r\n\n");

    printf("\nCompensated Magnetometer data with delay\r\n\n");
    printf("Mag_X(uT), Mag_Y(uT), Mag_Z(uT)\r\n\n");

    /* Get the magnetometer sensor object */
    bmm_dev = shield_xensiv_a_get_mag_sensor();

    for(;;)
    {
        /* Reads the x, y, z magnetometer data */
        mtb_bmm350_read(bmm_dev, &mag_data);

        /* Updates the sensor data on the display and serial terminal */
        sprintf(disp_string1, "%f", (double) mag_data.sensor_data.x);
        APPW_SetText(ID_SCREEN_05, ID_TEXT_04, disp_string1);
        sprintf(disp_string2, "%f", (double) mag_data.sensor_data.y);
        APPW_SetText(ID_SCREEN_05, ID_TEXT_05, disp_string2);
        sprintf(disp_string3, "%f", (double) mag_data.sensor_data.z);
        APPW_SetText(ID_SCREEN_05, ID_TEXT_06, disp_string3);

        printf("%f, %f, %f\r\n\n", (double) mag_data.sensor_data.x,
                   (double) mag_data.sensor_data.y, (double) mag_data.sensor_data.z);

        vTaskDelay(500/portTICK_PERIOD_MS);

        if (button_press_count_init != button_press_count)
        {
            break;
        }
    }

}

/* [] END OF FILE */
