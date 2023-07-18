/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;
/* USER CODE BEGIN PTD */

typedef struct
{
	char buf[5];
} QUEUE_t;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

UART_HandleTypeDef huart3;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for NothingTask */
osThreadId_t NothingTaskHandle;
uint32_t NothingTaskBuffer[ 128 ];
osStaticThreadDef_t NothingTaskControlBlock;
const osThreadAttr_t NothingTask_attributes = {
  .name = "NothingTask",
  .cb_mem = &NothingTaskControlBlock,
  .cb_size = sizeof(NothingTaskControlBlock),
  .stack_mem = &NothingTaskBuffer[0],
  .stack_size = sizeof(NothingTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for UpperCaseTask */
osThreadId_t UpperCaseTaskHandle;
uint32_t UpperCaseTaskBuffer[ 128 ];
osStaticThreadDef_t UpperCaseTaskControlBlock;
const osThreadAttr_t UpperCaseTask_attributes = {
  .name = "UpperCaseTask",
  .cb_mem = &UpperCaseTaskControlBlock,
  .cb_size = sizeof(UpperCaseTaskControlBlock),
  .stack_mem = &UpperCaseTaskBuffer[0],
  .stack_size = sizeof(UpperCaseTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for LowerCaseTask */
osThreadId_t LowerCaseTaskHandle;
uint32_t LowerCaseTaskBuffer[ 128 ];
osStaticThreadDef_t LowerCaseTaskControlBlock;
const osThreadAttr_t LowerCaseTask_attributes = {
  .name = "LowerCaseTask",
  .cb_mem = &LowerCaseTaskControlBlock,
  .cb_size = sizeof(LowerCaseTaskControlBlock),
  .stack_mem = &LowerCaseTaskBuffer[0],
  .stack_size = sizeof(LowerCaseTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for ReceiveTask */
osThreadId_t ReceiveTaskHandle;
uint32_t ReceiveTaskBuffer[ 128 ];
osStaticThreadDef_t ReceiveTaskControlBlock;
const osThreadAttr_t ReceiveTask_attributes = {
  .name = "ReceiveTask",
  .cb_mem = &ReceiveTaskControlBlock,
  .cb_size = sizeof(ReceiveTaskControlBlock),
  .stack_mem = &ReceiveTaskBuffer[0],
  .stack_size = sizeof(ReceiveTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for USARTQueueFirstTask */
osMessageQueueId_t USARTQueueFirstTaskHandle;
uint8_t USARTQueueBuffer[ 10 * sizeof( QUEUE_t ) ];
osStaticMessageQDef_t USARTQueueControlBlock;
const osMessageQueueAttr_t USARTQueueFirstTask_attributes = {
  .name = "USARTQueueFirstTask",
  .cb_mem = &USARTQueueControlBlock,
  .cb_size = sizeof(USARTQueueControlBlock),
  .mq_mem = &USARTQueueBuffer,
  .mq_size = sizeof(USARTQueueBuffer)
};
/* Definitions for USARTQueueSecondTask */
osMessageQueueId_t USARTQueueSecondTaskHandle;
uint8_t USARTQueueSecondTaskBuffer[ 10 * sizeof( QUEUE_t ) ];
osStaticMessageQDef_t USARTQueueSecondTaskControlBlock;
const osMessageQueueAttr_t USARTQueueSecondTask_attributes = {
  .name = "USARTQueueSecondTask",
  .cb_mem = &USARTQueueSecondTaskControlBlock,
  .cb_size = sizeof(USARTQueueSecondTaskControlBlock),
  .mq_mem = &USARTQueueSecondTaskBuffer,
  .mq_size = sizeof(USARTQueueSecondTaskBuffer)
};
/* Definitions for USARTQueueThirdTask */
osMessageQueueId_t USARTQueueThirdTaskHandle;
uint8_t USARTQueueThirdTaskBuffer[ 10 * sizeof( QUEUE_t ) ];
osStaticMessageQDef_t USARTQueueThirdTaskControlBlock;
const osMessageQueueAttr_t USARTQueueThirdTask_attributes = {
  .name = "USARTQueueThirdTask",
  .cb_mem = &USARTQueueThirdTaskControlBlock,
  .cb_size = sizeof(USARTQueueThirdTaskControlBlock),
  .mq_mem = &USARTQueueThirdTaskBuffer,
  .mq_size = sizeof(USARTQueueThirdTaskBuffer)
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
void StartDefaultTask(void *argument);
void StartNothingTask(void *argument);
void StartUpperCaseTask(void *argument);
void StartLowerCaseTask(void *argument);
void StartReceiveTask(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char buff[5] = {};
uint8_t flag;
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
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of USARTQueueFirstTask */
  USARTQueueFirstTaskHandle = osMessageQueueNew (10, sizeof(QUEUE_t), &USARTQueueFirstTask_attributes);

  /* creation of USARTQueueSecondTask */
  USARTQueueSecondTaskHandle = osMessageQueueNew (10, sizeof(QUEUE_t), &USARTQueueSecondTask_attributes);

  /* creation of USARTQueueThirdTask */
  USARTQueueThirdTaskHandle = osMessageQueueNew (10, sizeof(QUEUE_t), &USARTQueueThirdTask_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of NothingTask */
  NothingTaskHandle = osThreadNew(StartNothingTask, NULL, &NothingTask_attributes);

  /* creation of UpperCaseTask */
  UpperCaseTaskHandle = osThreadNew(StartUpperCaseTask, NULL, &UpperCaseTask_attributes);

  /* creation of LowerCaseTask */
  LowerCaseTaskHandle = osThreadNew(StartLowerCaseTask, NULL, &LowerCaseTask_attributes);

  /* creation of ReceiveTask */
  ReceiveTaskHandle = osThreadNew(StartReceiveTask, NULL, &ReceiveTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
          if(huart == &huart3)
          {
        	  flag = 1;
          }
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartNothingTask */
/**
* @brief Function implementing the NothingTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartNothingTask */
void StartNothingTask(void *argument)
{
  /* USER CODE BEGIN StartNothingTask */
	QUEUE_t msg;
  /* Infinite loop */
  for(;;)
  {
	  osMessageQueueGet(USARTQueueFirstTaskHandle, &msg, 0, osWaitForever);
	  HAL_UART_Transmit_IT(&huart3, (uint8_t*)msg.buf, 4);

	osDelay(1);
  }
  /* USER CODE END StartNothingTask */
}

/* USER CODE BEGIN Header_StartUpperCaseTask */
/**
* @brief Function implementing the UpperCaseTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartUpperCaseTask */
void StartUpperCaseTask(void *argument)
{
  /* USER CODE BEGIN StartUpperCaseTask */
	QUEUE_t msg;
  /* Infinite loop */
  for(;;)
  {
	  osMessageQueueGet(USARTQueueSecondTaskHandle, &msg, 0, osWaitForever);
	  HAL_UART_Transmit_IT(&huart3, (uint8_t*)msg.buf, 4);
    osDelay(1);
  }
  /* USER CODE END StartUpperCaseTask */
}

/* USER CODE BEGIN Header_StartLowerCaseTask */
/**
* @brief Function implementing the LowerCaseTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLowerCaseTask */
void StartLowerCaseTask(void *argument)
{
  /* USER CODE BEGIN StartLowerCaseTask */
    QUEUE_t msg;
  /* Infinite loop */
  for(;;)
  {
	  osMessageQueueGet(USARTQueueThirdTaskHandle, &msg, 0, osWaitForever);
	  HAL_UART_Transmit_IT(&huart3, (uint8_t*)msg.buf, 4);

	  osDelay(1);
  }
  /* USER CODE END StartLowerCaseTask */
}

/* USER CODE BEGIN Header_StartReceiveTask */
/**
* @brief Function implementing the ReceiveTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartReceiveTask */
void StartReceiveTask(void *argument)
{
  /* USER CODE BEGIN StartReceiveTask */
	QUEUE_t msg;
  /* Infinite loop */
  for(;;)
  {
	  HAL_UART_Receive_IT(&huart3, (uint8_t*)buff, 5);

	  	if (flag)
	  	{
	  		if(buff[0] == '1'){
	  		strcpy(msg.buf,buff+1);
	  		osMessageQueuePut(USARTQueueFirstTaskHandle, &msg, 0, osWaitForever);
	  		}
	  		else if (buff[0] == '2')
	  		{
	  			for(int i=1; i<strlen(buff); i++)
			  	  {
				  if(buff[i]>='a' && buff[i]<='z')
					  {
					  buff[i] = buff[i] - 32;
					  }
				  }

			strcpy(msg.buf,buff+1);
			osMessageQueuePut(USARTQueueSecondTaskHandle, &msg, 0, osWaitForever);
	  		}
	  		else if (buff[0] == '3')
	  		{
	  			for(int i=0; i<strlen(buff+1); i++)
				  {
				  if((buff+1)[i]>='A' && (buff+1)[i]<='Z')
				  	  {
					  (buff+1)[i] = (buff+1)[i] + 32;
				  	  }
				  }

			strcpy(msg.buf,buff+1);
			osMessageQueuePut(USARTQueueThirdTaskHandle, &msg, 0, osWaitForever);
	  		}

	  		flag = 0;
	  	}
    osDelay(1);
  }
  /* USER CODE END StartReceiveTask */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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

