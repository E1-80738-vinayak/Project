/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include<stdio.h>
#include<string.h>
#include "lcd.h"
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
CAN_HandleTypeDef hcan1;

I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN1_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
CAN_RxHeaderTypeDef RxHeader;
uint8_t RxData[5];
char temp_str[20];
char ldr_str[20];
char seatbelt_str[20];
char door_str[20];


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET); // blue
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData);
}

void fancontrol(uint8_t a)
{
	if(a > 5)
	{
//		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_SET);
//		HAL_Delay(1000);
//		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
		lcd_put_cur(0, 0);
		lcd_send_string("FAN ON");
		HAL_Delay(1000);
		lcd_clear();
	}
	else
	{
//		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14,GPIO_PIN_SET);
//		HAL_Delay(1000);
//		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
		lcd_put_cur(0, 0);
		lcd_send_string("FAN OFF");
		HAL_Delay(1000);
		lcd_clear();
	}
}
void lightcontrol(uint8_t b)
{
	if(b > 3)
	{
//		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13,GPIO_PIN_SET);
//		HAL_Delay(1000);
//		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
		lcd_put_cur(0, 0);
		lcd_send_string("LIGHT ON");
		HAL_Delay(1000);
		lcd_clear();
	}
	else
	{
//		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15,GPIO_PIN_SET);
//		HAL_Delay(1000);
//		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
		lcd_put_cur(0, 0);
		lcd_send_string("LIGHT OFF");
		HAL_Delay(1000);
		lcd_clear();
	}

}

void seat_belt_status(uint8_t seatbelt)
{
	if(seatbelt==1)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_SET);
		HAL_Delay(1000);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
		lcd_put_cur(0, 0);
		lcd_send_string("Seat Belt Opened");
		HAL_Delay(1000);
		lcd_clear();
	}
	else
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14,GPIO_PIN_SET);
		HAL_Delay(1000);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
		lcd_put_cur(0, 0);
		lcd_send_string("Seat Belt Closed");
		HAL_Delay(1000);
		lcd_clear();
	}
}
void door_status(uint8_t door)
{
	if(door==1)
		{
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13,GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
			lcd_put_cur(0, 0);
			lcd_send_string("Door Is Open");
			HAL_Delay(1000);
			lcd_clear();
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15,GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
			lcd_put_cur(0, 0);
			lcd_send_string("Door Is Closed");
			HAL_Delay(1000);
			lcd_clear();
		}
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
  MX_CAN1_Init();
  MX_I2C1_Init();
  lcd_init();
  HAL_Delay(200);
  lcd_clear();

  /* USER CODE BEGIN 2 */
	HAL_CAN_Start(&hcan1);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
	HAL_Delay(100);
	HAL_Delay(100);
	/* USER CODE END 2 */
	HAL_Delay(3000);
	lcd_put_cur(0, 0);
	lcd_send_string("Vehicle Automat-");
	lcd_put_cur(1, 0);
	lcd_send_string("ion Using CAN");
	//lcd_send_data(0xDF);
	HAL_Delay(3000);
	lcd_clear();

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {

	  //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
		if(RxData[0] == 'S'){
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET); //
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);

		}


		uint8_t a=RxData[1];
		sprintf(temp_str,"%d\n", a);
		lcd_put_cur(0, 0);
		// just a random string display into LCD
		lcd_send_string("Temperarture : ");
		// LCD cursor point at row 1 column 0
		lcd_put_cur(1, 0);
		// print the temperature value to LCD display
		lcd_send_string(temp_str);
		// LCD cursor point at row 1 column 2
		lcd_put_cur(1, 2);
		// print the (degree) sign into LCD
		lcd_send_data(0xDF);
		// LCD cursor point at row 1 column 3
		lcd_put_cur(1, 3);
		// print the (Celsius) sign into LCD
		lcd_send_data('C');
		HAL_Delay(1000);
		lcd_clear();
		fancontrol(a);
		HAL_Delay(1000);


		uint8_t b=RxData[2];
		sprintf(ldr_str,"%d\n", b);
		lcd_put_cur(0, 0);
		// just a random string display into LCD
		lcd_send_string("LDR Status : ");
		// LCD cursor point at row 1 column 0
		lcd_put_cur(1, 0);
		// print the temperature value to LCD display
		lcd_send_string(ldr_str);
		HAL_Delay(1000);
		lcd_clear();
		lightcontrol(b);
		HAL_Delay(1000);

		uint8_t seatbelt=RxData[3];
		sprintf(seatbelt_str,"%d\n", seatbelt);
		lcd_put_cur(0, 0);
		// just a random string display into LCD
		lcd_send_string("LDR Status : ");
		// LCD cursor point at row 1 column 0
		lcd_put_cur(1, 0);
		// print the temperature value to LCD display
		lcd_send_string(seatbelt_str);
		HAL_Delay(1000);
		lcd_clear();
		HAL_Delay(1000);
		seat_belt_status(seatbelt);
		HAL_Delay(1000);

		uint8_t door=RxData[4];
		sprintf(door_str,"%d\n", door);
		lcd_put_cur(0, 0);
		// just a random string display into LCD
		lcd_send_string("LDR Status : ");
		// LCD cursor point at row 1 column 0
		lcd_put_cur(1, 0);
		// print the temperature value to LCD display
		lcd_send_string(door_str);
		HAL_Delay(1000);
		lcd_clear();
		door_status(door);




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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 18;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_2TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */
  CAN_FilterTypeDef canFilterConfig;
  canFilterConfig.FilterActivation=CAN_FILTER_ENABLE;
  canFilterConfig.SlaveStartFilterBank=14;
  canFilterConfig.FilterBank=2;
  canFilterConfig.FilterFIFOAssignment=CAN_RX_FIFO0;
  canFilterConfig.FilterScale=CAN_FILTERSCALE_32BIT;
  canFilterConfig.FilterMode=CAN_FILTERMODE_IDMASK;
  canFilterConfig.FilterMaskIdLow=0x0000;
  canFilterConfig.FilterMaskIdHigh=0xFF00;
  canFilterConfig.FilterIdLow=0x0000;
  canFilterConfig.FilterIdHigh=0x1500;
  HAL_CAN_ConfigFilter(&hcan1, &canFilterConfig);
  /* USER CODE END CAN1_Init 2 */

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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
