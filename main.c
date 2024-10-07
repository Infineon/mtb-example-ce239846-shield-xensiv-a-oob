/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the SHIELD_XENSIV_A Sensor Hub
*              Example for ModusToolbox.
*
* Related Document: See README.md
*
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
#include "cyhal.h"
#include "cybsp.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "cy_retarget_io.h"
#include "sensors_task.h"

/******************************************************************************
* Macros
*******************************************************************************/
/* SPI baud rate in Hz */
#define SPI_FREQ_HZ                (1200000UL)
/* SPI transfer bits per frame */
#define BITS_PER_FRAME             (8)

/*******************************************************************************
* Global Variables
*******************************************************************************/
/* This enables RTOS aware debugging. */
volatile int uxTopUsedPriority;

/* HAL structure for I2C */
cyhal_i2c_t kit_i2c;

/* I2C configuration structure */
cyhal_i2c_cfg_t kit_i2c_cfg = {
    .is_slave = false,
    .address = 0,
    .frequencyhal_hz = 400000
};

cyhal_spi_t mSPI;

/*******************************************************************************
* Function Name: main
*********************************************************************************
* Summary:
*  System entrance point. This function initializes BSP, retarget IO, sets up
*  the TFT and sensors tasks, and then starts the RTOS scheduler.
*
* Parameters:
*  void
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;

#if defined (CY_DEVICE_SECURE)
    cyhal_wdt_t wdt_obj;

    /* Clear watchdog timer so that it doesn't trigger a reset */
    result = cyhal_wdt_init(&wdt_obj, cyhal_wdt_get_max_timeout_ms());
    CY_ASSERT(CY_RSLT_SUCCESS == result);
    cyhal_wdt_free(&wdt_obj);
#endif

    /* This enables RTOS aware debugging in OpenOCD. */
    uxTopUsedPriority = configMAX_PRIORITIES - 1;

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    /* Board init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Enable global interrupts */
    __enable_irq();

    /* Initialize retarget-io to use the debug UART port */
    result = cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX,
                                 CY_RETARGET_IO_BAUDRATE);

    CY_ASSERT(result == CY_RSLT_SUCCESS);

    /* Initialize the I2C peripheral */
    result = cyhal_i2c_init(&kit_i2c, SHIELD_XENSIV_A_PIN_I2C_SDA, SHIELD_XENSIV_A_PIN_I2C_SCL, NULL);
    /* I2C init failed. Stop program execution */
    if(CY_RSLT_SUCCESS != result)
    {
        CY_ASSERT(0);
    }

    /* Configure the I2C peripheral */
    result =   cyhal_i2c_configure(&kit_i2c, &kit_i2c_cfg);
    /* I2C config failed. Stop program execution */
    if(CY_RSLT_SUCCESS != result)
    {
        CY_ASSERT(0);
    }

    /* Select the display SPI CS */
    result = cyhal_gpio_init(SHIELD_XENSIV_A_PIN_SPI_CS_SEL0, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, true);
    if (CY_RSLT_SUCCESS == result)
    {
        /* Initialize the SPI peripheral */
        result = cyhal_spi_init(&mSPI, SHIELD_XENSIV_A_PIN_SPI_MOSI, SHIELD_XENSIV_A_PIN_SPI_MISO, SHIELD_XENSIV_A_PIN_SPI_SCK,
                SHIELD_XENSIV_A_PIN_SPI_CS, NULL, BITS_PER_FRAME, CYHAL_SPI_MODE_00_MSB, false);
        if (CY_RSLT_SUCCESS == result)
        {
            /* Set SPI frequency to 10MHz */
            result = cyhal_spi_set_frequency(&mSPI, SPI_FREQ_HZ);
            if(CY_RSLT_SUCCESS != result)
            {
                CY_ASSERT(0);
            }
        }
    }

    /* Initialize the SHIELD_XENSIV_A */
    result = shield_xensiv_a_init(&kit_i2c, &mSPI, NULL, NULL);
    if (CY_RSLT_SUCCESS != result)
    {
        CY_ASSERT(0);
    }

    /* Create the TFT task */
    if (xTaskCreate(tft_task, "tftTask", TFT_TASK_STACK_SIZE,
    NULL, TFT_TASK_PRIORITY, NULL) != pdPASS)
    {
        CY_ASSERT(0);
    }

    /* Create the sensors task */
    if (xTaskCreate(sensors_task, "sensorsTask", SENSORS_TASK_STACK_SIZE,
    NULL, SENSORS_TASK_PRIORITY, NULL) != pdPASS)
    {
        CY_ASSERT(0);
    }

    /* Start the FreeRTOS scheduler. */
    vTaskStartScheduler();

    /* Should never get here. */
    CY_ASSERT(0);
}

/* [] END OF FILE */
