#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

// ESP32-spezifische FreeRTOS Konfiguration
// Diese Datei kann in HW_API/drivers/esp32_hal_wrapper/ liegen

#define configUSE_PREEMPTION            1
#define configUSE_IDLE_HOOK             0
#define configUSE_TICK_HOOK             0
#define configCPU_CLOCK_HZ              160000000
#define configTICK_RATE_HZ              1000
#define configMAX_PRIORITIES            25
#define configMINIMAL_STACK_SIZE        512
#define configTOTAL_HEAP_SIZE           ( ( size_t ) ( 230 * 1024 ) )
#define configMAX_TASK_NAME_LEN         16
#define configUSE_TRACE_FACILITY        1
#define configUSE_16_BIT_TICKS          0
#define configIDLE_SHOULD_YIELD         1
#define configUSE_MUTEXES               1
#define configQUEUE_REGISTRY_SIZE       10
#define configCHECK_FOR_STACK_OVERFLOW  2
#define configUSE_RECURSIVE_MUTEXES     1
#define configUSE_MALLOC_FAILED_HOOK    1
#define configUSE_APPLICATION_TASK_TAG  0

// ESP32-spezifische Defines
#define configNUM_CORES                 1
#define configUSE_CORE_AFFINITY         1

#endif /* FREERTOS_CONFIG_H */
