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
#define MAX_SIZE 200*64 + 1		// Max size of ARR table

#define FREQ_TMR 84000000UL   // timer freq [Hz]
#define FULL_STEP_DEG 1.8     // deg / steo
#define MICRO_STEPS 0.125f    // 1/8
#define PI 3.14159265358979323846

#define LUT_SIZE 100			//Size of LUT for neg arcsin

// Scalers
#define T_SCALER FREQ_TMR      // time scaler (y axis)
#define THETA_SCALER 1000000UL // angle scaler (x axis)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
DMA_HandleTypeDef hdma_tim2_up_ch3;

/* USER CODE BEGIN PV */
int32_t LUT_x[LUT_SIZE] =
{
            0,   10101,   20202,   30303,   40404,   50505,   60606,
        70707,   80808,   90909,  101010,  111111,  121212,  131313,
        141414,  151515,  161616,  171717,  181818,  191919,  202020,
        212121,  222222,  232323,  242424,  252525,  262626,  272727,
        282828,  292929,  303030,  313131,  323232,  333333,  343434,
        353535,  363636,  373737,  383838,  393939,  404040,  414141,
        424242,  434343,  444444,  454545,  464646,  474747,  484848,
        494949,  505050,  515151,  525252,  535353,  545454,  555555,
        565656,  575757,  585858,  595959,  606060,  616161,  626262,
        636363,  646464,  656565,  666666,  676767,  686868,  696969,
        707070,  717171,  727272,  737373,  747474,  757575,  767676,
        777777,  787878,  797979,  808080,  818181,  828282,  838383,
        848484,  858585,  868686,  878787,  888888,  898989,  909090,
        919191,  929292,  939393,  949494,  959595,  969696,  979797,
        989898, 1000000
};

int32_t LUT_y[LUT_SIZE] =
{
                0,    -848499,   -1697085,   -2545844,   -3394863,
         -4244229,   -5094030,   -5944354,   -6795287,   -7646921,
         -8499343,   -9352645,  -10206917,  -11062251,  -11918740,
        -12776479,  -13635562,  -14496087,  -15358151,  -16221854,
        -17087298,  -17954584,  -18823819,  -19695109,  -20568563,
        -21444293,  -22322412,  -23203036,  -24086286,  -24972283,
        -25861152,  -26753023,  -27648027,  -28546300,  -29447982,
        -30353218,  -31262156,  -32174950,  -33091759,  -34012746,
        -34938082,  -35867942,  -36802510,  -37741975,  -38686535,
        -39636394,  -40591766,  -41552875,  -42519953,  -43493243,
        -44473000,  -45459490,  -46452994,  -47453805,  -48462232,
        -49478601,  -50503254,  -51536554,  -52578883,  -53630649,
        -54692281,  -55764236,  -56847003,  -57941100,  -59047082,
        -60165544,  -61297123,  -62442504,  -63602428,  -64777691,
        -65969160,  -67177773,  -68404555,  -69650624,  -70917207,
        -72205657,  -73517466,  -74854290,  -76217978,  -77610601,
        -79034491,  -80492293,  -81987026,  -83522160,  -85101718,
        -86730410,  -88413802,  -90158563,  -91972782,  -93866446,
        -95852119,  -97945981, -100169480, -102552091, -105136281,
       -107987272, -111214941, -115033700, -119997578, -131946891
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
int32_t interpolate_from_LUT(int32_t x);
int32_t calculate_tk_scaled(int k, int32_t Theta_rad_scaled, int32_t T_scaled, int32_t alpha_rad_scaled);
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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  uint32_t timer_values[MAX_SIZE];

  // example parameters
  double alpha_deg = FULL_STEP_DEG * MICRO_STEPS;
  double alpha_rad = alpha_deg * PI / 180.0;

  int32_t alpha_rad_scaled = (int32_t)(alpha_rad * THETA_SCALER);

  double Theta_deg = 720.0;
  double Theta_rad = Theta_deg * PI / 180.0;
  int32_t Theta_rad_scaled = (int32_t)(Theta_rad * THETA_SCALER);

  double T_sec = 0.5;
  int32_t T_scaled = (int32_t)(T_sec * T_SCALER);

  int n_steps = (int)(Theta_deg / alpha_deg);

  // Calculate t_k and ARR
  int32_t t_k_scaled[n_steps+1];
  int k = 0;
  for (k = 0; k <= n_steps; k++) {
	  t_k_scaled[k] = calculate_tk_scaled(k, Theta_rad_scaled, T_scaled, alpha_rad_scaled);
  }

  double summ_test = 0;
  for (int k = 0; k < n_steps; k++) {
	  int32_t dt_scaled = t_k_scaled[k+1] - t_k_scaled[k];
	  int32_t ARR = dt_scaled - 1; //as the time scaler and the frequency is equal we don't need to do any further scaling
	  timer_values[k] = ARR;
	  summ_test += (double)ARR;
  }
  summ_test = summ_test / FREQ_TMR;
  timer_values[k+1] = 0;

  HAL_GPIO_WritePin(ENN_GPIO_Port, ENN_Pin, 0);
  HAL_GPIO_WritePin(DIR_GPIO_Port, DIR_Pin, 1);

  uint32_t DstAddress = (uint32_t) & (TIM2->ARR);

  HAL_TIM_Base_Start_IT(&htim2);

  HAL_DMA_Start_IT(&hdma_tim2_up_ch3, (uint32_t)timer_values, DstAddress, MAX_SIZE);

  __HAL_TIM_ENABLE_DMA(&htim2, TIM_DMA_CC3);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 41999999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 32;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);

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
  HAL_GPIO_WritePin(GPIOA, STEP_Pin|DIR_Pin|ENN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : USART_TX_Pin USART_RX_Pin */
  GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : STEP_Pin */
  GPIO_InitStruct.Pin = STEP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(STEP_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : DIR_Pin */
  GPIO_InitStruct.Pin = DIR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DIR_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ENN_Pin */
  GPIO_InitStruct.Pin = ENN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ENN_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

// Linear interpolation from the look up table using integers
// todo: Better search algo
int32_t interpolate_from_LUT(int32_t x) {
    int sign = 1;
    if (x < 0) {
        sign = -1;
        x = -x;
    }

    if (x <= (int32_t)LUT_x[0]) return sign * (int32_t)LUT_y[0];
    if (x >= (int32_t)LUT_x[LUT_SIZE - 1]) return sign * (int32_t)LUT_y[LUT_SIZE - 1];

    // bináris keresés helyett egyszerű lineáris (mert LUT kicsi)
    int idx = 0;
    while (idx < LUT_SIZE - 1 && x > (int32_t)LUT_x[idx+1]) idx++;

    int32_t x0 = LUT_x[idx];
    int32_t x1 = LUT_x[idx+1];
    int32_t y0 = LUT_y[idx];
    int32_t y1 = LUT_y[idx+1];

    // lineáris interpoláció
    int32_t dy = y1 - y0;
    int32_t dx = x1 - x0;
    int32_t dt = x - x0;

    // (dy * dt) / dx
    int32_t y = y0 + (int32_t)((int64_t)dy * dt / dx);

    return sign * y;
}

// Calculate the scaled t_k values
// todo: error if t_k is smaller than the pulse width
int32_t calculate_tk_scaled(int k, int32_t Theta_rad_scaled, int32_t T_scaled, int32_t alpha_rad_scaled) {
    int32_t pi_scaled = (int32_t)(PI * T_SCALER);

    int32_t neg_arcsin_arg_scaled = THETA_SCALER - 2 * THETA_SCALER * ((int64_t)k * alpha_rad_scaled) / (Theta_rad_scaled);

    int32_t neg_arcsin_scaled = interpolate_from_LUT(neg_arcsin_arg_scaled);

    int32_t tk_scaled = (int32_t)(( (int64_t)(neg_arcsin_scaled + pi_scaled/2) * T_scaled) / pi_scaled);


    return tk_scaled;
}

//Kikommentelem, mert megpróbálom output comparrel
/*
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	if (htim == &htim2)
	{
		HAL_GPIO_WritePin(STEP_GPIO_Port, STEP_Pin, 0); //typical low time for STEP is 100 ns, order of magnitude higher than clock of MCU
		HAL_GPIO_WritePin(STEP_GPIO_Port, STEP_Pin, 1);
		//HAL_GPIO_TogglePin(STEP_GPIO_Port, STEP_Pin);
	}
}

*/
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
