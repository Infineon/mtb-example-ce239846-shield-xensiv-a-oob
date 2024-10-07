/******************************************************************************
* File Name:   sensors_task.h
*
* Description: This file contains declaration of tasks and functions related
*              to the sensors and display present on the SHIELD_XENSIV_A
*              sensor shield.
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
#include "cybsp.h"
#include "cy_retarget_io.h"
#include "FreeRTOS.h"
#include "task.h"
#include "GUI.h"
#include "semphr.h"
#include "Generated/Resource.h"
#include "shield_xensiv_a.h"

/******************************************************************************
* Macros
*******************************************************************************/
#define SENSORS_TASK_STACK_SIZE        (1024*2)
#define SENSORS_TASK_PRIORITY          (configMAX_PRIORITIES-5)
#define TFT_TASK_STACK_SIZE            (1024*5)
#define TFT_TASK_PRIORITY              (configMAX_PRIORITIES - 3)
#define GPIO_INTERRUPT_PRIORITY        (3u)
#define T_DET                          (SHIELD_XENSIV_A_PIN_RADAR_GPIO2)
#define P_DET                          (SHIELD_XENSIV_A_PIN_RADAR_GPIO1)
#define RADAR_SEL                      (SHIELD_XENSIV_A_PIN_RADAR_SEL)
#define RADAR_COUNT                    (1)
#define SHT3X_COUNT                    (2)
#define BMI270_COUNT                   (3)
#define BMM350_COUNT                   (4)
#define DPS368_COUNT                   (5)
#define PASCO2_COUNT                   (6)
#define THRESHOLD_PPM                  (1000)

/*******************************************************************************
* Global Variables
*******************************************************************************/
extern volatile uint8_t button_press_count;
extern cyhal_i2c_t kit_i2c;
extern cyhal_i2c_cfg_t kit_i2c_cfg;
extern mtb_bmi270_t* bmi_dev;
extern mtb_bmi270_data_t sens_data;
extern mtb_bmm350_t* bmm_dev;
extern mtb_bmm350_data_t* mag_data;
extern xensiv_dps3xx_t* pressure_sensor;
extern xensiv_pasco2_t* xensiv_pasco2;
extern char *status;
extern char disp_string1;
extern char disp_string2;
extern char disp_string3;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
void btn_interrupt_handler(void* handler_arg, cyhal_gpio_event_t event);
void wait_for_switch_press_and_release(void);
void tft_task(void *arg);
void sensors_task(void *arg);
void radar_task(void);
void sht3x_task(void);
void dps368_task(void);
void bmi270_task(void);
void bmm350_task(void);
void pasco2_task(void);

/* [] END OF FILE */
