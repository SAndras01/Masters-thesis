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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// AS5147U CRC8 calculation (AMS polynomial 0x1D)
static uint8_t AS5x47_CalcCRC8(uint16_t data)
{
    uint8_t crc = 0xC4;
    uint8_t bytes[2] = { (uint8_t)(data >> 8), (uint8_t)(data & 0xFF) };

    for (int i = 0; i < 2; i++) {
        crc ^= bytes[i];
        for (int bit = 0; bit < 8; bit++) {
            if (crc & 0x80)
                crc = ((crc << 1) ^ 0x1D) & 0xFF;
            else
                crc = (crc << 1) & 0xFF;
        }
    }
    crc ^= 0xFF;
    return crc;
}


uint16_t AS5x47_Read16(SPI_HandleTypeDef *hspi, GPIO_TypeDef *CS_Port, uint16_t CS_Pin, uint16_t address)
{
    uint8_t tx[2];
    uint8_t rx[2];
    uint16_t cmd = (0x4000u | (address & 0x3FFFu)); // bit14=1 -> read

    tx[0] = (uint8_t)(cmd >> 8);
    tx[1] = (uint8_t)(cmd & 0xFF);

    // 1) Parancs elküldése
    HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(hspi, tx, 2, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_SET);

    // 2) Dummy read a válaszért
    uint8_t dummy[2] = { 0xFF, 0xFF };
    HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(hspi, dummy, rx, 2, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_SET);

    uint16_t result = ((uint16_t)rx[0] << 8) | rx[1];
    return result;
}

void AS5x47_WriteRegister(SPI_HandleTypeDef *hspi, GPIO_TypeDef *CS_Port, uint16_t CS_Pin, uint16_t address, uint16_t data)
{
    uint8_t frame[3];

    // Első 24-bit frame: write command
    uint16_t cmd = (address & 0x3FFFu);  // bit14=0 (write)
    uint8_t crc_cmd = AS5x47_CalcCRC8(cmd);

    frame[0] = (uint8_t)(cmd >> 8);
    frame[1] = (uint8_t)(cmd & 0xFF);
    frame[2] = crc_cmd;

    HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(hspi, frame, 3, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_SET);

    HAL_Delay(1); // kis szünet a két frame között

    // Második 24-bit frame: data + CRC
    uint8_t crc_data = AS5x47_CalcCRC8(data);
    frame[0] = (uint8_t)(data >> 8);
    frame[1] = (uint8_t)(data & 0xFF);
    frame[2] = crc_data;

    HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(hspi, frame, 3, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(CS_Port, CS_Pin, GPIO_PIN_SET);
}


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
  MX_USART2_UART_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  /*
  uint16_t address = 0x0019;

  uint16_t data = 0;
  uint16_t data2 = 0;
  uint16_t rawAng = 0;
  uint16_t rawAngComp = 0;

  uint16_t frame = address & 0x3FFF;

  (frame) ^= (-(1) ^ (frame)) & (1UL << (14)); //Mert Read


  //READ settings
  HAL_Delay(10);
  HAL_GPIO_WritePin(ENCODER1_CS_GPIO_Port, ENCODER1_CS_Pin, GPIO_PIN_RESET);
  HAL_Delay(10);
  HAL_SPI_Transmit(&hspi1, (uint8_t *)&frame, 1, HAL_MAX_DELAY);
  HAL_Delay(10);
  HAL_GPIO_WritePin(ENCODER1_CS_GPIO_Port, ENCODER1_CS_Pin, GPIO_PIN_SET);

  HAL_Delay(10);
  HAL_GPIO_WritePin(ENCODER1_CS_GPIO_Port, ENCODER1_CS_Pin, GPIO_PIN_RESET);
  HAL_Delay(10);
  HAL_SPI_Receive(&hspi1, (uint8_t *)&data, 1, HAL_MAX_DELAY);;
  HAL_Delay(10);
  HAL_GPIO_WritePin(ENCODER1_CS_GPIO_Port, ENCODER1_CS_Pin, GPIO_PIN_SET);
  HAL_Delay(10);


  //Disable DAEC
  frame = address & 0x3FFF;

  uint16_t data2write = 0b1 << 4;

  //Write settings
  HAL_Delay(10);
  HAL_GPIO_WritePin(ENCODER1_CS_GPIO_Port, ENCODER1_CS_Pin, GPIO_PIN_RESET);
  HAL_Delay(10);
  HAL_SPI_Transmit(&hspi1, (uint8_t *)&frame, 1, HAL_MAX_DELAY);
  HAL_Delay(10);
  HAL_GPIO_WritePin(ENCODER1_CS_GPIO_Port, ENCODER1_CS_Pin, GPIO_PIN_SET);

  HAL_Delay(10);
  HAL_GPIO_WritePin(ENCODER1_CS_GPIO_Port, ENCODER1_CS_Pin, GPIO_PIN_RESET);
  HAL_Delay(10);
  HAL_SPI_Transmit(&hspi1, (uint8_t *)&data2write, 1, HAL_MAX_DELAY);;
  HAL_Delay(10);
  HAL_GPIO_WritePin(ENCODER1_CS_GPIO_Port, ENCODER1_CS_Pin, GPIO_PIN_SET);
  HAL_Delay(10);


  //READ settings
  (frame) ^= (-(1) ^ (frame)) & (1UL << (14)); //Mert Read

  HAL_Delay(10);
  HAL_GPIO_WritePin(ENCODER1_CS_GPIO_Port, ENCODER1_CS_Pin, GPIO_PIN_RESET);
  HAL_Delay(10);
  HAL_SPI_Transmit(&hspi1, (uint8_t *)&frame, 1, HAL_MAX_DELAY);
  HAL_Delay(10);
  HAL_GPIO_WritePin(ENCODER1_CS_GPIO_Port, ENCODER1_CS_Pin, GPIO_PIN_SET);

  HAL_Delay(10);
  HAL_GPIO_WritePin(ENCODER1_CS_GPIO_Port, ENCODER1_CS_Pin, GPIO_PIN_RESET);
  HAL_Delay(10);
  HAL_SPI_Receive(&hspi1, (uint8_t *)&data2, 1, HAL_MAX_DELAY);;
  HAL_Delay(10);
  HAL_GPIO_WritePin(ENCODER1_CS_GPIO_Port, ENCODER1_CS_Pin, GPIO_PIN_SET);
  HAL_Delay(10);


*/

  char MSG[64] = {'\0'};
  float scaler = 16383.0;
  float angle, angleWcomp;
  uint16_t rawAng = 0;
  uint16_t rawAngComp = 0;

  // 1) Olvasd ki az eredeti értéket
  uint16_t settings1 = AS5x47_Read16(&hspi1, ENCODER1_CS_GPIO_Port, ENCODER1_CS_Pin, 0x0019);

  // 2) Állítsd be a bit4-et
  settings1 |= (0 << 4);
  AS5x47_WriteRegister(&hspi1, ENCODER1_CS_GPIO_Port, ENCODER1_CS_Pin, 0x0019, settings1);

  // 3) Ellenőrizd visszaolvasással
  uint16_t verify = AS5x47_Read16(&hspi1, ENCODER1_CS_GPIO_Port, ENCODER1_CS_Pin, 0x0019);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  rawAng = AS5x47_Read16(&hspi1, ENCODER1_CS_GPIO_Port, ENCODER1_CS_Pin, 0x3FFE);
	  rawAngComp = AS5x47_Read16(&hspi1, ENCODER1_CS_GPIO_Port, ENCODER1_CS_Pin, 0x3FFF);

	  rawAng &= 0x3FFF;        // 14 bites adat
	  rawAngComp &= 0x3FFF;

	  angle = (float)rawAng/scaler * (float)360;
	  angleWcomp = (float)rawAngComp/scaler * (float)360;

	  // kurzor vissza a terminál elejére (2 sorral fel), képernyő frissítés
	  snprintf(MSG, sizeof(MSG), "\033[H\033[J"); // clear screen (opcionális)
	  HAL_UART_Transmit(&huart2, (uint8_t*)MSG, strlen(MSG), 100);

	  // első sor
	  snprintf(MSG, sizeof(MSG), "Raw angle   : %05.3f °\r\n", angle);
	  HAL_UART_Transmit(&huart2, (uint8_t*)MSG, strlen(MSG), 100);

	  // második sor
	  snprintf(MSG, sizeof(MSG), "With comp   : %05.3f °\r\n", angleWcomp);
	  HAL_UART_Transmit(&huart2, (uint8_t*)MSG, strlen(MSG), 100);

	  HAL_Delay(200); // frissítés ~20 Hz-en
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
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|ENCODER1_CS_Pin, GPIO_PIN_RESET);

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

  /*Configure GPIO pin : ENCODER1_CS_Pin */
  GPIO_InitStruct.Pin = ENCODER1_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(ENCODER1_CS_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
