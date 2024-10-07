/******************************************************************************
* File Name:   radar_sensor.c
*
* Description: This file contains all the functions and variables required for
*               proper operation of BGT60LTR11AIP radar sensor.
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
#include "ID_SCREEN_02.h"

/******************************************************************************
* Macros
*******************************************************************************/
/* Radar sensor GPIOs state */
#define INACTIVE    (0)
#define ACTIVE      (1)

/*******************************************************************************
* Global Variables
*******************************************************************************/
uint32_t T_DET_Status = 0;
uint32_t P_DET_Status = 0;
uint16_t P_DET_prev = -1;
uint16_t T_DET_prev = -1;

/*******************************************************************************
* Function Name: radar_task
*********************************************************************************
* Summary: Reads the radar sensor GPIOs to detect target presence and direction.
* Updates sensor status on the display and serial terminal.
*
* Parameters:
*  void
*
* Return:
*
*******************************************************************************/
void radar_task(void)
{
    char *status[] = {"Presence: Detected", "Presence: Not Detected", "Approaching", 
                       "Departing", "           "};

    const uint8_t button_press_count_init = button_press_count;

    /* Updates the screen on the display */
    APPW_SetVarData(btn_stat, RADAR_COUNT);

    printf("\x1b[2J\x1b[;H");
    printf("***********************************************************\r\n");
    printf("               BGT60LTR11AIP: Radar Sensor                 \r\n");
    printf("***********************************************************\r\n\n");
    printf("Press the USER Button SW2 to change the sensor\r\n\n");

    for (;;)
    {
        /* Get P_DET and T_DET status. */
        P_DET_Status = cyhal_gpio_read(P_DET);
        T_DET_Status = cyhal_gpio_read(T_DET);

        switch (T_DET_Status)
        {
            case INACTIVE:
                switch (P_DET_Status)
                {
                    case INACTIVE:
                        if (P_DET_prev  != P_DET_Status)
                        {
                            /* Updates the status on serial terminal and TFT display*/
                            T_DET_prev  = T_DET_Status;
                            P_DET_prev  = P_DET_Status;
                            APPW_SetText(ID_SCREEN_02, ID_TEXT_01, status[0]);
                            APPW_SetText(ID_SCREEN_02, ID_TEXT_02, status[3]);
                            APPW_SetVarData(T_DET_Stat, ACTIVE);
                            APPW_SetVarData(P_DET_Stat, ACTIVE);
                            printf("Motion: Detected\r\n");
                            printf("Direction: Departing\r\n\n\n");
                        }
                        break;
                    case ACTIVE:
                        if (P_DET_prev  != P_DET_Status)
                        {
                            /* Updates the status on serial terminal and TFT display*/
                            T_DET_prev  = T_DET_Status;\
                            P_DET_prev  = P_DET_Status;
                            APPW_SetText(ID_SCREEN_02, ID_TEXT_01, status[0]);
                            APPW_SetText(ID_SCREEN_02, ID_TEXT_02, status[2]);
                            APPW_SetVarData(T_DET_Stat, ACTIVE);
                            APPW_SetVarData(P_DET_Stat, INACTIVE);
                            printf("Motion: Detected\r\n");
                            printf("Direction: Approaching\r\n\n\n");
                        }
                        break;
                    default:
                        break;
                }
                break;
            case ACTIVE:
                if (T_DET_prev  != T_DET_Status)
                {
                    /* Updates the status on serial terminal and TFT display*/
                    T_DET_prev  = T_DET_Status;
                    APPW_SetVarData(T_DET_Stat, INACTIVE);
                    APPW_SetText(ID_SCREEN_02, ID_TEXT_01, status[1]);
                    APPW_SetText(ID_SCREEN_02, ID_TEXT_02, status[4]);
                    printf("Motion: Not Detected\r\n");
                    printf("Direction: NA\r\n\n\n");
                }
                break;
            default:
                break;
        }

        if (button_press_count_init != button_press_count)
        {
            break;
        }
    }
}

/* [] END OF FILE */
