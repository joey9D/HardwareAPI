/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32g0xx_hal.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../../app/MainApp.h"
#include "../../app/CANopenNode.h"
#include <array>
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
FDCAN_HandleTypeDef hfdcan1;
FDCAN_HandleTypeDef hfdcan2;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
//static void MX_FDCAN1_Init();
static void MX_USART1_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_FDCAN2_Init();
/* USER CODE BEGIN PFP */

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
	//CANopenNode::instance().setCANNodeParameter(&hcan, &htim3, MX_CAN_Init);
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/
//  int a =5;
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
//  MX_FDCAN1_Init(); // CAN Definiton inside abstraction layer
  MX_USART1_UART_Init();
  MX_TIM2_Init();
//  MX_FDCAN2_Init(); // CAN Definiton inside abstraction layer

  /* USER CODE BEGIN 2 */
  MainApp App;
  App.loop();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  __NOP();
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
	  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

	  /** Initializes the RCC Oscillators according to the specified parameters
	  * in the RCC_OscInitTypeDef structure.
	  */
	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
	  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
	  RCC_OscInitStruct.PLL.PLLN = 8;
	  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  /** Initializes the CPU, AHB and APB buses clocks
	  */
	  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	                              |RCC_CLOCKTYPE_PCLK1;
	  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

	  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	  {
	    Error_Handler();
	  }
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
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
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB13 PB14 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_I2C2;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}


//static void MX_FDCAN2_Init()
//{
//	typedef struct
//	{
//		uint32_t Baudrate;
//		uint32_t N_Prescaler;
//		uint32_t N_SyncJumpWidth;
//		uint32_t N_TimeSeg1;
//		uint32_t N_TimeSeg2;
//		uint32_t D_Prescaler;
//		uint32_t D_SyncJumpWidth;
//		uint32_t D_TimeSeg1;
//		uint32_t D_TimeSeg2;
//		uint8_t  StdFilters;
//		uint8_t  ExtFilters;
//	} FDCAN_Baud_Parameter_t;
//
//	static uint8_t isInit = 0;
//	/* USER CODE BEGIN CAN_Init 0 */
//	if(isInit == 0)
//	{
//		isInit = 1;
//		// Define the baud rate parameters for FDCAN
//		// Only 250 and 50Kbit are configured here for 64 MHz clock :: Todo :: Add values for more baudrates
//		// Todo :: Initially Filters are also set to 0, but can be configured later
//		std::array<FDCAN_Baud_Parameter_t,8> para_can =
//		{{
//			{1000, 2, 0, 0, 0, 0, 0, 0, 0, 0,       0}, // 1000 kbit/s
//			{800, 3, 0, 0, 0, 0, 0, 0, 0, 0,        0}, // 800 kbit/s
//			{500, 4, 0, 0, 0, 0, 0, 0, 0, 0,        0}, // 500 kbit/s
//			{250, 2, 20, 107, 20, 8, 6, 25, 6, 0,   0}, // 250 kbit/s // Set
//			{125, 16, 0, 0, 0, 0, 0, 0, 0, 0,0}, // 125 kbit/s
//			{50, 8, 21, 138, 21, 32, 16, 23, 16, 0, 0}, // 50 kbit/s  //Set
//			{20, 200, 0, 0, 0, 0, 0, 0, 0, 0,0}, // 20 kbit/s
//			{10, 200, 0, 0, 0, 0, 0, 0, 0, 0,0} //10 kbit/s
//
//		}};
//
//
//		FDCAN_Baud_Parameter_t para_can_val = para_can.at(5);//default baudrate 50
//
////		for(uint8_t i=0; i<para_can.size(); i++)
////		{
////			if(baud == para_can.at(i).Baudrate)
////			{
////				para_can_val = para_can.at(i);
////				break;
////			}
////		}
//
//	  hfdcan2.Instance = FDCAN2;
//	  hfdcan2.Init.ClockDivider = FDCAN_CLOCK_DIV1;
//	  hfdcan2.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
//	  hfdcan2.Init.Mode = FDCAN_MODE_NORMAL;
//	  hfdcan2.Init.AutoRetransmission = DISABLE;
//	  hfdcan2.Init.TransmitPause = DISABLE;
//	  hfdcan2.Init.ProtocolException = DISABLE;
//	  hfdcan2.Init.NominalPrescaler = para_can_val.N_Prescaler;
//	  hfdcan2.Init.NominalSyncJumpWidth = para_can_val.N_SyncJumpWidth;
//	  hfdcan2.Init.NominalTimeSeg1 = para_can_val.N_TimeSeg1;
//	  hfdcan2.Init.NominalTimeSeg2 = para_can_val.N_TimeSeg2;
//	  hfdcan2.Init.DataPrescaler = para_can_val.D_Prescaler;
//	  hfdcan2.Init.DataSyncJumpWidth = para_can_val.D_SyncJumpWidth;
//	  hfdcan2.Init.DataTimeSeg1 = para_can_val.D_TimeSeg1;
//	  hfdcan2.Init.DataTimeSeg2 = para_can_val.D_TimeSeg2;
//	  hfdcan2.Init.StdFiltersNbr = para_can_val.StdFilters;
//	  hfdcan2.Init.ExtFiltersNbr = para_can_val.ExtFilters;
//	  hfdcan2.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
//	  if (HAL_FDCAN_Init(&hfdcan2) != HAL_OK)
//	  {
//		Error_Handler();
//	  }
//    }
//}


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
