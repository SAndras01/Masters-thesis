/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BTN_FIX_AX_Pin GPIO_PIN_2
#define BTN_FIX_AX_GPIO_Port GPIOE
#define BTN_TRACKED_AX_Pin GPIO_PIN_3
#define BTN_TRACKED_AX_GPIO_Port GPIOE
#define BTN_MEM_SLOT_Pin GPIO_PIN_4
#define BTN_MEM_SLOT_GPIO_Port GPIOE
#define BTN_OK_Pin GPIO_PIN_5
#define BTN_OK_GPIO_Port GPIOE
#define BNT_SET_Pin GPIO_PIN_6
#define BNT_SET_GPIO_Port GPIOE
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define MOT1_DIR_Pin GPIO_PIN_0
#define MOT1_DIR_GPIO_Port GPIOF
#define MOT1_SPREAD_Pin GPIO_PIN_1
#define MOT1_SPREAD_GPIO_Port GPIOF
#define MOT1_MS1_Pin GPIO_PIN_2
#define MOT1_MS1_GPIO_Port GPIOF
#define MOT1_MS2_Pin GPIO_PIN_3
#define MOT1_MS2_GPIO_Port GPIOF
#define MOT2_DIR_Pin GPIO_PIN_4
#define MOT2_DIR_GPIO_Port GPIOF
#define MOT2_SPREAD_Pin GPIO_PIN_5
#define MOT2_SPREAD_GPIO_Port GPIOF
#define MOT2_MS1_Pin GPIO_PIN_6
#define MOT2_MS1_GPIO_Port GPIOF
#define MOT2_MS2_Pin GPIO_PIN_7
#define MOT2_MS2_GPIO_Port GPIOF
#define MOT_ENN_Pin GPIO_PIN_8
#define MOT_ENN_GPIO_Port GPIOF
#define OLED_RES_Pin GPIO_PIN_9
#define OLED_RES_GPIO_Port GPIOF
#define ENCODER1_CS_Pin GPIO_PIN_10
#define ENCODER1_CS_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define RMII_MDC_Pin GPIO_PIN_1
#define RMII_MDC_GPIO_Port GPIOC
#define TRG_RB_OUT_Pin GPIO_PIN_2
#define TRG_RB_OUT_GPIO_Port GPIOC
#define MOT1_STEP_Pin GPIO_PIN_0
#define MOT1_STEP_GPIO_Port GPIOA
#define RMII_REF_CLK_Pin GPIO_PIN_1
#define RMII_REF_CLK_GPIO_Port GPIOA
#define RMII_MDIO_Pin GPIO_PIN_2
#define RMII_MDIO_GPIO_Port GPIOA
#define NUMPAD_A_OUT_Pin GPIO_PIN_3
#define NUMPAD_A_OUT_GPIO_Port GPIOA
#define NUMPAD_VREF_Pin GPIO_PIN_6
#define NUMPAD_VREF_GPIO_Port GPIOA
#define RMII_CRS_DV_Pin GPIO_PIN_7
#define RMII_CRS_DV_GPIO_Port GPIOA
#define RMII_RXD0_Pin GPIO_PIN_4
#define RMII_RXD0_GPIO_Port GPIOC
#define RMII_RXD1_Pin GPIO_PIN_5
#define RMII_RXD1_GPIO_Port GPIOC
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define ENCODER2_CS_Pin GPIO_PIN_11
#define ENCODER2_CS_GPIO_Port GPIOF
#define BTN_FREE_MOOVE_Pin GPIO_PIN_7
#define BTN_FREE_MOOVE_GPIO_Port GPIOE
#define BTN_EXTERNAL_EXTRA_Pin GPIO_PIN_8
#define BTN_EXTERNAL_EXTRA_GPIO_Port GPIOE
#define BTN_ONBRD_EXTRA1_Pin GPIO_PIN_9
#define BTN_ONBRD_EXTRA1_GPIO_Port GPIOE
#define BTN_ONBRD_EXTRA2_Pin GPIO_PIN_10
#define BTN_ONBRD_EXTRA2_GPIO_Port GPIOE
#define BTN_ONBRD_EXTRA3_Pin GPIO_PIN_11
#define BTN_ONBRD_EXTRA3_GPIO_Port GPIOE
#define BTN_ONBRD_EXTRA4_Pin GPIO_PIN_12
#define BTN_ONBRD_EXTRA4_GPIO_Port GPIOE
#define MOT1_DIAG_Pin GPIO_PIN_13
#define MOT1_DIAG_GPIO_Port GPIOE
#define MOT2_DIAG_Pin GPIO_PIN_14
#define MOT2_DIAG_GPIO_Port GPIOE
#define RMII_TXD1_Pin GPIO_PIN_13
#define RMII_TXD1_GPIO_Port GPIOB
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define USB_SOF_Pin GPIO_PIN_8
#define USB_SOF_GPIO_Port GPIOA
#define USB_VBUS_Pin GPIO_PIN_9
#define USB_VBUS_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define MOT2_STEP_Pin GPIO_PIN_15
#define MOT2_STEP_GPIO_Port GPIOA
#define RMII_TX_EN_Pin GPIO_PIN_11
#define RMII_TX_EN_GPIO_Port GPIOG
#define RMII_TXD0_Pin GPIO_PIN_13
#define RMII_TXD0_GPIO_Port GPIOG
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB
#define MOT_ENN_RB_Pin GPIO_PIN_0
#define MOT_ENN_RB_GPIO_Port GPIOE
#define TRG_SIGNAL_Pin GPIO_PIN_1
#define TRG_SIGNAL_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
