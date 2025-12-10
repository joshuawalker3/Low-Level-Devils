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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "aht10.h"
#include "i2c-lcd.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct {
	int16_t temp;
	uint8_t humid;
	Temp_Unit units;
} dataPacket;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LCD_ADDR 0x27
#define STD_STACK 512
#define BUFF_READY_FLAG 0x01
#define CALC_COMP_FLAG 0x02
#define DATA_QUEUE_COUNT 3

#define TEMP_ROW ROW_01
#define TEMP_COL COL_07
#define RH_ROW ROW_02
#define RH_COL COL_05
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

I2C_HandleTypeDef hi2c2;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */
osThreadId_t aht10TaskHandle;
const osThreadAttr_t aht10Task_attributes = {
  .name = "aht10Task",
  .stack_size = STD_STACK,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t calculationTaskHandle;
const osThreadAttr_t calculationTask_attributes = {
  .name = "calculatonTask",
  .stack_size = STD_STACK * 2,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t lcdTaskHandle;
const osThreadAttr_t lcdTask_attributes = {
  .name = "lcdTask",
  .stack_size = STD_STACK,
  .priority = (osPriority_t) osPriorityNormal,
};

osEventFlagsId_t buffer_flag;
osEventFlagsAttr_t buffer_flag_attr = {
		.name = "bufferFlag",
		.attr_bits = 0,
		.cb_mem = NULL,
		.cb_size = 0
};

osMessageQueueId_t data_queue;
osMessageQueueAttr_t data_queue_attr = {
		.name = "dataQueue",
		.attr_bits = 0,
		.cb_mem = NULL,
		.cb_size = 0,
		.mq_mem = NULL,
		.mq_size = 0
};

Lcd_HandleTypeDef* lcd;
Aht10_HandleTypeDef* aht10;

const char* TEMP_LINE = "TEMP: ";
const char* RH_LINE = "RH: ";
const char* TEMP_SPACING = "      ";
const char* HUMID_SPACING = "    ";
const char* HUMID_UNIT = "%";
const char* CELSIUS = " C";
const char* FAHRENHEIT = " F";
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C2_Init(void);
void StartDefaultTask(void *argument);

/* USER CODE BEGIN PFP */
void StartAht10Task(void *arg);
void StartLcdTask(void *arg);
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

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

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
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
  lcd_open(lcd, &hi2c2, LCD_ADDR, NO_RTOS);
  aht10_open(aht10, &hi2c2, NO_RTOS);

  if (lcd_init(lcd) != HAL_OK) {
	  while (1) {
		  //
	  }
  }

  if (aht10_init(aht10, SENSOR_POWER_GPIO_Port, SENSOR_POWER_Pin, METRIC)) {
	  while (1) {
		  //
	  }
  }
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

  /* USER CODE BEGIN RTOS_QUEUES */
  data_queue = osMessageQueueNew(DATA_QUEUE_COUNT, sizeof(dataPacket), &data_queue_attr);
  if (data_queue == NULL) {
	  while(1) {
		  //
	  }
  }
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  //defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  aht10TaskHandle = osThreadNew(StartAht10Task, NULL, &aht10Task_attributes);
  if (aht10TaskHandle == NULL) {
  	  while(1) {
  		  //
  	  }
  }

  lcdTaskHandle = osThreadNew(StartLcdTask, NULL, &lcdTask_attributes);
    if (lcdTaskHandle == NULL) {
      	  while(1) {
      		  //
      	  }
   }
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  buffer_flag = osEventFlagsNew(&buffer_flag_attr);
  if (buffer_flag == NULL) {
  	  while(1) {
  		  //
  	  }
  }
  osEventFlagsSet(buffer_flag, CALC_COMP_FLAG);
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x20404768;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

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
  __HAL_RCC_GPIOF_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SENSOR_POWER_GPIO_Port, SENSOR_POWER_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : SENSOR_POWER_Pin */
  GPIO_InitStruct.Pin = SENSOR_POWER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SENSOR_POWER_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void StartAht10Task(void *arg) {
	HAL_StatusTypeDef status;

	aht10->mode = RTOS_MODE;

	uint8_t humidity = 101;
	int16_t temperature = -1;

	dataPacket packet = {
		.temp = temperature,
		.humid = humidity,
		.units = aht10->units
	};

	while(1) {
		status = aht10_ioctrl(aht10, POWER_ON);
		if (status != HAL_OK) {
			while(1) {
				osDelay(1);
			}
		}

		status =  aht10_read(aht10, &temperature, &humidity);
		if (status != HAL_OK) {
			while(1) {
				osDelay(1);
			}
		}

		packet.temp = temperature;
		packet.humid = humidity;

		status = aht10_ioctrl(aht10, POWER_OFF);
		if (status != HAL_OK) {
			while(1) {
				osDelay(1);
			}
		}

		osMessageQueuePut(data_queue, (void*)&packet, 1, osWaitForever);

		osDelay(5000);
	}
}

void StartLcdTask(void *arg) {
	int16_t curr_temp = -100;
	uint8_t curr_humid = 101;
	HAL_StatusTypeDef status;

	lcd->mode = RTOS_MODE;

	dataPacket packet;

	status = lcd_ioctrl(lcd, DDRAM_SET|TEMP_ROW|COL_01);
	if (status != HAL_OK) {
		while(1) {
			osDelay(1);
		}
	}
	status = lcd_write(lcd, (void*)TEMP_LINE, WRITE_STRING);
	if (status != HAL_OK) {
		while(1) {
			osDelay(1);
		}
	}

	status = lcd_ioctrl(lcd, DDRAM_SET|RH_ROW|COL_01);
	if (status != HAL_OK) {
		while(1) {
			osDelay(1);
		}
	}
	status = lcd_write(lcd, (void*)RH_LINE, WRITE_STRING);
	if (status != HAL_OK) {
		while(1) {
			osDelay(1);
		}
	}

	while (1) {
		osMessageQueueGet(data_queue, (void*)&packet, NULL, osWaitForever);

		if (packet.temp != curr_temp) {
			status = lcd_ioctrl(lcd, DDRAM_SET|TEMP_ROW|TEMP_COL);
			if (status != HAL_OK) {
				while(1) {
					osDelay(1);
				}
			}

			status = lcd_write(lcd, (void*)TEMP_SPACING, WRITE_STRING);
			if (status != HAL_OK) {
				while(1) {
					osDelay(1);
				}
			}

			status = lcd_ioctrl(lcd, DDRAM_SET|TEMP_ROW|TEMP_COL);
			if (status != HAL_OK) {
				while(1) {
					osDelay(1);
				}
			}

			status = lcd_write(lcd, (void*)&packet.temp, WRITE_INT16);
			if (status != HAL_OK) {
				while(1) {
					osDelay(1);
				}
			}

			if (packet.units == METRIC) {
				status = lcd_write(lcd, (void*)CELSIUS, WRITE_STRING);
			} else {
				status = lcd_write(lcd, (void*)FAHRENHEIT, WRITE_STRING);
			}

			curr_temp = packet.temp;

			if (status != HAL_OK) {
				while(1) {
					osDelay(1);
				}
			}
		}

		if (packet.humid != curr_humid) {
			status = lcd_ioctrl(lcd, DDRAM_SET|RH_ROW|RH_COL);
			if (status != HAL_OK) {
				while(1) {
					osDelay(1);
				}
			}

			status = lcd_write(lcd, (void*)HUMID_SPACING, WRITE_STRING);
			if (status != HAL_OK) {
				while(1) {
					osDelay(1);
				}
			}

			status = lcd_ioctrl(lcd, DDRAM_SET|RH_ROW|RH_COL);
			if (status != HAL_OK) {
				while(1) {
					osDelay(1);
				}
			}

			status = lcd_write(lcd, (void*)&(packet.humid), WRITE_UINT8);
			if (status != HAL_OK) {
				while(1) {
					osDelay(1);
				}
			}

			status = lcd_write(lcd, (void*)HUMID_UNIT, WRITE_STRING);

			curr_humid = packet.humid;

			if (status != HAL_OK) {
				while(1) {
					osDelay(1);
				}
			}
		}
	}
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the sensorTask thread.
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

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
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
