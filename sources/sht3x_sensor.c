/******************************************************************************
* File Name:   sht3x_sensor.c
*
* Description: This file uses sensor-humidity-sht3x library APIs to demonstrate
*              the use of SHT35 digital humidity and temperature sensor
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
#include "ID_SCREEN_03.h"

/******************************************************************************
* Macros
*******************************************************************************/
#define NO_ERROR 0

/*******************************************************************************
* Function Name: sht3x_task
*********************************************************************************
* Summary: Reads humidity and temperature from the SHT35 sensor.
* Updates sensor status on the display and serial terminal.
*
* Parameters:
*  void
*
* Return:
*
*******************************************************************************/
void sht3x_task(void)
{
    char disp_string1[10] = " ";
    char disp_string2[10] = " ";

    struct sensor_data_t data;
    const uint8_t button_press_count_init = button_press_count;

    /* Updates the screen on the display */
    APPW_SetVarData(btn_stat, SHT3X_COUNT);

    printf("\x1b[2J\x1b[;H");
    printf("***********************************************************\r\n");
    printf("          SHT35: Humidity and Temperature Sensor           \r\n");
    printf("***********************************************************\r\n\n");
    printf("Press the USER Button SW2 to change the sensor\r\n\n");

    /* Starts the periodic measurement mode of SHT35 sensor */
    mtb_sht3x_start_periodic_measurement(&kit_i2c, REPEAT_MEDIUM, MPS_ONE_PER_SEC);

    for(;;)
    {
        /* Reads the SHT35 sensor data */
        data = mtb_sht3x_read(&kit_i2c);

        /* Updates the sensor data on the display and serial terminal */
        sprintf(disp_string1, "%.2f", data.humidity);
        APPW_SetText(ID_SCREEN_03, ID_TEXT_01, disp_string1);
        printf("Humidity : %.2f RH\r\n", data.humidity);

        sprintf(disp_string2, "%.2f", data.temperature);
        APPW_SetText(ID_SCREEN_03, ID_TEXT_02, disp_string2);
        printf("Temperature : %.2f degC\r\n\n\n", data.temperature);

        vTaskDelay(500/portTICK_PERIOD_MS);

        if (button_press_count_init != button_press_count)
        {
            mtb_sht3x_stop_measurement(&kit_i2c);
            break;
        }
    }
}

/* [] END OF FILE */
