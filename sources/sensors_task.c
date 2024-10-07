/******************************************************************************
* File Name:   sensors_task.c
*
* Description: This file contain tasks, functions and variables related to the
*              sensors_task and tft task required for initialization of all the
*              sensors and display present on the SHIELD_XENSIV_A sensor shield.
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

/******************************************************************************
* Macros
*******************************************************************************/
/* Wait time for sensor ready (milliseconds) */
#define WAIT_SENSOR_RDY_MS              (1000)


/*******************************************************************************
* Global Variables
*******************************************************************************/
volatile uint8_t button_press_count = 0;
uint8_t button_prev = -1;

SemaphoreHandle_t xSwitchSemaphore = NULL;

/* Configure GPIO interrupt */
cyhal_gpio_callback_data_t switch_cb_data =
{
    .callback     = btn_interrupt_handler,
    .callback_arg = NULL
};

mtb_bmm350_t* bmm_dev;
mtb_bmi270_t* bmi_dev;
xensiv_dps3xx_t* pressure_sensor;
xensiv_pasco2_t* xensiv_pasco2;

/*******************************************************************************
* Function Name: void tft_task(void *arg)
*********************************************************************************
* Summary: The Following functions are performed in this task
*           1. Initializes the emWin display engine
*           2. Displays the sensors data
*
* Parameters:
*  arg: task argument (unused)
*
* Return:
*  None
*
*******************************************************************************/
void tft_task(void *arg)
{
    /* Calling the AppWizard application entry point*/
    MainTask();
}

/*******************************************************************************
* Function Name: sensors_task
*********************************************************************************
* Summary: The Following functions are performed in this task
*           1. Initializes multiple sensors present on SHIELD_XENSIV_A
*           2. Switches the sensors functionality based on the button press event
* Parameters:
*  void
*
* Return:
*
*******************************************************************************/
void sensors_task(void *arg)
{
    /* Status variable to indicate the result of various operations */
    cy_rslt_t result;

    printf("\x1b[2J\x1b[;H");
    printf("***********************************************************\r\n");
    printf("              XENSIV Sensor Shield: OOB demo               \r\n");
    printf("***********************************************************\r\n\n");
    printf("Press the USER Button SW2 to change the sensor\r\n\n");

    /* Initialize the User Button */
    result = cyhal_gpio_init(CYBSP_USER_BTN, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_PULLUP, CYBSP_BTN_OFF);

    /* Register callback function - btn_interrupt_handler and pass the value global_count */
    cyhal_gpio_register_callback(CYBSP_USER_BTN, &switch_cb_data);

    /* Enable falling edge interrupt event with interrupt priority set to 3 */
    cyhal_gpio_enable_event(CYBSP_USER_BTN, CYHAL_GPIO_IRQ_FALL, GPIO_INTERRUPT_PRIORITY, true);

    if(CY_RSLT_SUCCESS != result)
    {
        CY_ASSERT(0);
    }

    /* Create a semaphore */
    xSwitchSemaphore = xSemaphoreCreateBinary();

    /* Select the onboard radar sensor using RADAR_SEL pin */
    result = cyhal_gpio_init(RADAR_SEL, CYHAL_GPIO_DIR_OUTPUT,
                                 CYHAL_GPIO_DRIVE_STRONG, false);
    if(CY_RSLT_SUCCESS != result)
    {
        CY_ASSERT(0);
    }

    /* Initialize the P_DET and T_DET pins */
    result = cyhal_gpio_init(P_DET, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, false);
    if(CY_RSLT_SUCCESS != result)
    {
        CY_ASSERT(0);
    }
    result = cyhal_gpio_init(T_DET, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, false);
    if(CY_RSLT_SUCCESS != result)
    {
        CY_ASSERT(0);
    }

    /* Initialize the baseboard user LEDs */
    cyhal_gpio_init(CYBSP_LED_RGB_GREEN, CYHAL_GPIO_DIR_OUTPUT,
                                     CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);

    cyhal_gpio_init(CYBSP_LED_RGB_RED, CYHAL_GPIO_DIR_OUTPUT,
                                     CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);

    for(;;)
    {
        wait_for_switch_press_and_release();
        /* Updates the sensors functionality based on the button press event */
        switch(button_press_count)
        {
            case RADAR_COUNT:
                radar_task();
                break;
            case SHT3X_COUNT:
                sht3x_task();
                break;
            case BMI270_COUNT:
                bmi270_task();
                break;
            case BMM350_COUNT:
                bmm350_task();
                break;
            case DPS368_COUNT:
                dps368_task();
                break;
            case PASCO2_COUNT:
                pasco2_task();
                button_press_count = RADAR_COUNT;
                break;
            default:
                break;
        }
    }
}

/*******************************************************************************
* Function Name: void btn_interrupt_handler(void* handler_arg, cyhal_gpio_event_t event)
********************************************************************************
*
* Summary: GPIO interrupt handler.
*
* Parameters:
*  handler_arg: (unused)
*  event: (unused)
*
* Return:
*  None
*
*******************************************************************************/
void btn_interrupt_handler(void* handler_arg, cyhal_gpio_event_t event)
{
    button_press_count++;
    CY_UNUSED_PARAMETER(event);
    xSemaphoreGiveFromISR(xSwitchSemaphore, NULL);
    portYIELD_FROM_ISR(pdTRUE);
}

/*******************************************************************************
* Function Name: void wait_for_switch_press_and_release(void)
********************************************************************************
*
* Summary: This implements a semaphore wait.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void wait_for_switch_press_and_release(void)
{
    /* Semaphore wait (wait for switch to be released) */
    xSemaphoreTake(xSwitchSemaphore, portMAX_DELAY);
}

/* [] END OF FILE */
