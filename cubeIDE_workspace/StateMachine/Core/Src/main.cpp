/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "SSD1305.hpp"
#include "state_machine.hpp"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
enum states
{
	setNum1 = 0,
	setNum2 = 1,
	setNum3 = 2
};


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define dmaCyclerTimer htim5
#define configedADC hadc1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim5;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM5_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
void DrawGUI_main(SSD1305* display, uint8_t memslot, axes fixedax, axes trackedax, uint16_t setdeg, float refX, float refY, float refZ);
void DrawYline_main(SSD1305* display, uint8_t x, SSD1305_COLOR color);
void DisplayMemslot_main(SSD1305* display, uint8_t memslot);
void DisplayFixedAx_main(SSD1305* display, axes fixedax);
void DisplayTrackedAx_main(SSD1305* display, axes trackedax);
void DisplaySetAngle_main(SSD1305* display, uint16_t setdeg, int selectedDigit = -1);
void DisplaySetAngle_main(SSD1305* display, uint8_t* digits, int selectedDigit = -1);
void DisplayRefDegs_main(SSD1305* display, float refX, float refY, float refZ);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_TIM5_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  numpadEnable();
  HAL_GPIO_WritePin(OLED_RESET_NOT_GPIO_Port, OLED_RESET_NOT_Pin, GPIO_PIN_SET);

  SSD1305 display(&hi2c1, 0x3C, 128, 32);
  display.Init();
  display.Fill(Black);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint8_t number[3] = {0,0,0};
  uint8_t currentNum = 0;
  states currentState = setNum1;

  //DrawGUI_main(&display, 3, x, y, 130, 131, 12.3, 1.8);
  MemorySlot initialSettings =
  {
		  1,//uint8_t number;
		  y,//axes fixAx;
		  z,//axes trackedAx;
		  110,//uint16_t setDegree;
  };
  Accelerometer dummyAccel;
  StateSetFixTrackDeg stateSetFixTrackDeg(initialSettings);
  mainMachine machine(&stateSetFixTrackDeg, &display, &dummyAccel);
  while (1)
  {
	  machine.run();
	  /*if(adcValue2Digit() != 10)
	  {
		  currentNum = adcValue2Digit();
	  }

	  switch (currentState) {
		case setNum1:
			number[0] = currentNum;
			if(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin))
			{
				HAL_Delay(10);
				while(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin)){__NOP();}
				HAL_Delay(10);
				currentState = setNum2;
				currentNum = number[1];
			}
			break;
		case setNum2:
			number[1] = currentNum;
			if(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin))
			{
				HAL_Delay(10);
				while(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin)){__NOP();}
				HAL_Delay(10);
				currentState = setNum3;
				currentNum = number[2];
			}
			break;
		case setNum3:
			number[2] = currentNum;
			if(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin))
			{
				HAL_Delay(10);
				while(HAL_GPIO_ReadPin(PINK_BTN_GPIO_Port, PINK_BTN_Pin)){__NOP();}
				HAL_Delay(10);
				currentState = setNum1;
				currentNum = number[0];
			}
			break;
		default:
			break;
	  }

	  DisplaySetAngle_main(&display, number, currentState);
	  display.WriteBitmapToScreen();*/
	  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 84-1;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 10000-1;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OLED_RESET_NOT_GPIO_Port, OLED_RESET_NOT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OLED_RESET_NOT_Pin */
  GPIO_InitStruct.Pin = OLED_RESET_NOT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OLED_RESET_NOT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PINK_BTN_Pin */
  GPIO_InitStruct.Pin = PINK_BTN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(PINK_BTN_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
#define LINE_1_Y 0
#define LINE_2_Y 11
#define LINE_3_Y 22

void DrawGUI_main(SSD1305* display, uint8_t memslot, axes fixedax, axes trackedax, uint16_t setdeg, float refX, float refY, float refZ)
{
	//MEM section -> x = 0..21
	display->SetCursor(0, LINE_1_Y);
	display->WriteString("MEM", Font_7x10, White);

	DisplayMemslot_main(display, memslot);

	DrawYline_main(display, 23, White);

	//Fixed, Tracked, Angle -> x = 22...78
	display->SetCursor(25, LINE_1_Y);
	display->WriteString("FixAx:", Font_7x10, White);
	display->SetCursor(25, LINE_2_Y);
	display->WriteString("Track:", Font_7x10, White);
	display->SetCursor(25, LINE_3_Y);
	display->WriteString("Deg:", Font_7x10, White);

	DisplayFixedAx_main(display, fixedax);
	DisplayTrackedAx_main(display, trackedax);
	DisplaySetAngle_main(display, setdeg);

	DrawYline_main(display, 76, White);

	//REF section -> x = 78...
	display->SetCursor(78, LINE_1_Y);
	display->WriteString("rx", Font_7x10, White);
	display->SetCursor(78, LINE_2_Y);
	display->WriteString("ry", Font_7x10, White);
	display->SetCursor(78, LINE_3_Y);
	display->WriteString("rz", Font_7x10, White);

	DisplayRefDegs_main(display, refX, refY, refZ);

	//Put all to display
	display->WriteBitmapToScreen();
}

void DrawYline_main(SSD1305* display, uint8_t x, SSD1305_COLOR color)
{
	for(uint8_t i = 0; i < display->GetHeight(); i++)
	{
		display->DrawPixel(x, i, color);
	}
}

void DisplayMemslot_main(SSD1305* display, uint8_t memslot)
{
	char memslotDigit = memslot + '0';
	display->SetCursor(5, 12);
	display->WriteChar(memslotDigit, Font_11x18, White);
}

void DisplayFixedAx_main(SSD1305* display, axes fixedax)
{
	char axesChar;
	switch (fixedax) {
		case x:
			axesChar = 'x';
			break;
		case y:
			axesChar = 'y';
			break;
		case z:
			axesChar = 'z';
			break;
		default:
			break;
	}

	display->SetCursor(67, LINE_1_Y);
	display->WriteChar(axesChar, Font_7x10, White);
}

void DisplayTrackedAx_main(SSD1305* display, axes trackedax)
{
	char axesChar;
	switch (trackedax) {
		case x:
			axesChar = 'x';
			break;
		case y:
			axesChar = 'y';
			break;
		case z:
			axesChar = 'z';
			break;
		default:
			break;
	}

	display->SetCursor(67, LINE_2_Y);
	display->WriteChar(axesChar, Font_7x10, White);
}

void DisplaySetAngle_main(SSD1305* display, uint16_t setdeg, int selectedDigit)
{
	char digits[3];

    digits[0] = ((130/100)%10) + '0';
    digits[1] = ((130/10)%10) + '0';
    digits[2] = (130%10) + '0';

    FontDef font = Font_7x10;
	for(int i = 0; i<3; i++)
	{
	  display->SetCursor(53 + i*font.FontWidth, LINE_3_Y);
	  if(i == selectedDigit)
	  {
		  display->WriteChar(digits[i], font, Black);
	  }
	  else
	  {
		  display->WriteChar(digits[i], font, White);
	  }
	}
}

void DisplaySetAngle_main(SSD1305* display, uint8_t* digits, int selectedDigit)
{
    FontDef font = Font_7x10;
	for(int i = 0; i<3; i++)
	{
	  display->SetCursor(53 + i*font.FontWidth, LINE_3_Y);
	  if(i == selectedDigit)
	  {
		  display->WriteChar(digits[i] + '0', font, Black);
	  }
	  else
	  {
		  display->WriteChar(digits[i] + '0', font, White);
	  }
	}
}

void DisplayRefDegs_main(SSD1305* display, float refX, float refY, float refZ)
{
	char refDegStr[6];
	snprintf(refDegStr, sizeof(refDegStr), "%05.1f", refX);
	display->SetCursor(93, LINE_1_Y);
	display->WriteString(refDegStr, Font_7x10, White);

	snprintf(refDegStr, sizeof(refDegStr), "%05.1f", refY);
	display->SetCursor(93, LINE_2_Y);
	display->WriteString(refDegStr, Font_7x10, White);

	snprintf(refDegStr, sizeof(refDegStr), "%05.1f", refZ);
	display->SetCursor(93, LINE_3_Y);
	display->WriteString(refDegStr, Font_7x10, White);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
