/******************************************************************************
* File Name:    dps368_sensor.c
*
* Description:  This file contains all the functions and variables required for
*               proper operation of DPS368 sensor.
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
#include "ID_SCREEN_06.h"

/*******************************************************************************
* Function Name: dps368_task
*********************************************************************************
* Summary: Measures the pressure and temperature from the DPS368 sensor.
* Updates sensor data on the display and serial terminal.
*
* Parameters:
*  void
*
* Return:
*
*******************************************************************************/
void dps368_task(void)
{
    float pressure, temperature;

    char disp_string1[20] = " ";
    char disp_string2[30] = " ";

    const uint8_t button_press_count_init = button_press_count;

    /* Updates the screen on the display */
    APPW_SetVarData(btn_stat, DPS368_COUNT);

    printf("\x1b[2J\x1b[;H");
    printf("***********************************************************\r\n");
    printf("                DPS368: Pressure Sensor                    \r\n");
    printf("***********************************************************\r\n\n");
    printf("Press the USER Button SW2 to change the sensor\r\n\n");

    /* Get the pressure sensor object */
    pressure_sensor = shield_xensiv_a_get_pressure_sensor();

    for(;;)
    {
        /* Reads the pressure and temperature data from the sensor */
        xensiv_dps3xx_read(pressure_sensor, &pressure, &temperature);

        /* Updates the sensor data on the display and serial terminal */
        sprintf(disp_string1, "%.2lf hPa", (double) pressure);
        APPW_SetText(ID_SCREEN_06, ID_TEXT_01, disp_string1);
        printf("Pressure   : %0.2lf hPa\r\n", (double) pressure);

        sprintf(disp_string2, "%.2lf degC", (double) temperature);
        APPW_SetText(ID_SCREEN_06, ID_TEXT_02, disp_string2);
        printf("Temperature: %0.2lf degC\r\n\n\n", (double) temperature);


        vTaskDelay(300/portTICK_PERIOD_MS);

        if (button_press_count_init != button_press_count)
        {
            break;
        }
    }
}

/* [] END OF FILE */
