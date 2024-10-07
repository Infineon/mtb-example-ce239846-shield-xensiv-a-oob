/******************************************************************************
* File Name:   pasco2_sensor.c
*
* Description: This file uses PAS CO2 library APIs to demonstrate the use of
*              CO2 sensor.
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
#include "ID_SCREEN_07.h"

/******************************************************************************
* Macros
*******************************************************************************/
#define PIN_XENSIV_PASCO2_I2C_SDA       CYBSP_I2C_SDA
#define PIN_XENSIV_PASCO2_I2C_SCL       CYBSP_I2C_SCL

/* Default atmospheric pressure to compensate for (hPa) */
#define DEFAULT_PRESSURE_REF_HPA        (0x3F7)

/*******************************************************************************
* Function Name: pasco2_task
*********************************************************************************
* Summary: Reads the CO2 ppm values from the PAS CO2 sensor.
* Updates sensor data on the display and serial terminal.
*
* Parameters:
*  void
*
* Return:
*
*******************************************************************************/
void pasco2_task(void)
{
    /* Status variable to indicate the result of various operations */
    cy_rslt_t result;

    uint16_t ppm;
    char disp_string1[10] = " ";
    const uint8_t button_press_count_init = button_press_count;

    /* Updates the screen on the display */
    APPW_SetVarData(btn_stat, PASCO2_COUNT);

    printf("\x1b[2J\x1b[;H");
    printf("***********************************************************\r\n");
    printf("                 XENSIV PAS CO2 5V Sensor                  \r\n");
    printf("***********************************************************\r\n\n");
    printf("Press the USER Button SW2 to change the sensor\r\n\n");

    /* Get the CO2 sensor object */
    xensiv_pasco2 = shield_xensiv_a_get_co2_sensor();

    for (;;)
    {
        /* Reads the CO2 data from the sensor */
        result = xensiv_pasco2_mtb_read(xensiv_pasco2, DEFAULT_PRESSURE_REF_HPA, &ppm);
        
        if (result == CY_RSLT_SUCCESS)
        {
            if (ppm<=THRESHOLD_PPM)
            {
                /* Green user LED is turned on when the ppm value goes less than 1000 */
                cyhal_gpio_write(CYBSP_LED_RGB_GREEN, CYBSP_LED_STATE_ON);
                cyhal_gpio_write(CYBSP_LED_RGB_RED, CYBSP_LED_STATE_OFF);

            }
            else
            {
                /* Red user LED is turned on when the ppm value go beyond 1000 */
                cyhal_gpio_write(CYBSP_LED_RGB_GREEN, CYBSP_LED_STATE_OFF);
                cyhal_gpio_write(CYBSP_LED_RGB_RED, CYBSP_LED_STATE_ON);
            }
            
            /* Updates the sensor data on the display and serial terminal */
            sprintf(disp_string1, "%d ppm", ppm);
            APPW_SetText(ID_SCREEN_07, ID_TEXT_01, disp_string1);
            printf("CO2 %d ppm.\r\n\n", ppm);
        }

           vTaskDelay(100/portTICK_PERIOD_MS);

        if (button_press_count_init != button_press_count)
        {
            cyhal_gpio_write(CYBSP_LED_RGB_GREEN, CYBSP_LED_STATE_OFF);
            cyhal_gpio_write(CYBSP_LED_RGB_RED, CYBSP_LED_STATE_OFF);
            break;
        }
    }
}

/* [] END OF FILE */