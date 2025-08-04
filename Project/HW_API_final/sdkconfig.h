/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    sdkconfig.h
  * @author  HW_API Project
  * @brief   ESP-IDF SDK configuration file for ESP32-C6
  *          Based on ESP-IDF v5.3.1 configuration
  *          Minimal configuration for GPIO and basic functionality
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 Espressif Systems (Shanghai) Co. Ltd.
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
#ifndef SDKCONFIG_H
#define SDKCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* ########################## Target Configuration ########################## */
/**
  * @brief ESP32-C6 Target Configuration
  */
#define CONFIG_IDF_TARGET_ESP32C6 1
#define CONFIG_IDF_TARGET "esp32c6"

/* ########################## Architecture Configuration ##################### */
#define CONFIG_IDF_TARGET_ARCH_RISCV 1
#define CONFIG_RISCV 1
#define CONFIG_ESP32C6 1

/* ########################## GPIO Configuration ############################# */
/**
  * @brief GPIO driver configuration
  */
#define CONFIG_GPIO_ESP32 1
#define CONFIG_GPIO_CTRL_FUNC_IN_IRAM 1

/* ########################## System Configuration ########################### */
/**
  * @brief Basic system configuration
  */
#define CONFIG_ESP_SYSTEM_EVENT_LOOP_STACK_SIZE 2304
#define CONFIG_ESP_SYSTEM_EVENT_TASK_STACK_SIZE 2304
#define CONFIG_ESP_MAIN_TASK_STACK_SIZE 3584

/* ########################## FreeRTOS Configuration ######################### */
/**
  * @brief Minimal FreeRTOS configuration
  */
#define CONFIG_FREERTOS_HZ 1000
#define CONFIG_FREERTOS_MAX_TASK_NAME_LEN 16
#define CONFIG_FREERTOS_NUMBER_OF_CORES 1
#define CONFIG_FREERTOS_TASK_NOTIFICATION_ARRAY_ENTRIES 1
#define CONFIG_FREERTOS_UNICORE 1

/* ########################## Hardware Support Configuration ################# */
/**
  * @brief ESP32-C6 hardware capabilities
  */
#define CONFIG_ESP_CONSOLE_UART_DEFAULT 1
#define CONFIG_ESP_CONSOLE_UART_NUM 0

/* ########################## Memory Configuration ########################### */
/**
  * @brief Memory layout configuration
  */
#define CONFIG_ESP32C6_DEFAULT_CPU_FREQ_MHZ 160
#define CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ 160

/* ########################## Log Configuration ############################## */
/**
  * @brief Logging configuration - minimal for embedded use
  */
#define CONFIG_LOG_DEFAULT_LEVEL 3  // LOG_LEVEL_INFO
#define CONFIG_LOG_MAXIMUM_LEVEL 5  // LOG_LEVEL_VERBOSE

/* ########################## ROM Configuration ############################## */
/**
  * @brief ROM code configuration
  */
#define CONFIG_ESP32C6_REV_MIN_0 1

/* ########################## SOC Configuration ############################## */
/**
  * @brief System on Chip configuration
  */
#define CONFIG_SOC_UART_SUPPORTED 1
#define CONFIG_SOC_GPIO_SUPPORTED 1

/* ########################## Driver Configuration ########################### */
/**
  * @brief Enable essential drivers
  */
#define CONFIG_ESP_TIMER_TASK_STACK_SIZE 3584

/* ########################## Compatibility Definitions ##################### */
/**
  * @brief Compatibility definitions for ESP-IDF integration
  */
#ifndef portTICK_PERIOD_MS
#define portTICK_PERIOD_MS (1000 / CONFIG_FREERTOS_HZ)
#endif

#ifndef pdMS_TO_TICKS
#define pdMS_TO_TICKS(xTimeInMs) ((TickType_t)((xTimeInMs) * CONFIG_FREERTOS_HZ / 1000))
#endif

#ifdef __cplusplus
}
#endif

#endif /* SDKCONFIG_H */
