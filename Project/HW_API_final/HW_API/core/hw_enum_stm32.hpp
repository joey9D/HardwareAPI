#pragma once

// Platform-specific GPIO enums for STM32
#ifdef STM32_PLATFORM

// Use our central HAL include that handles family detection
#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"

namespace HW_API
{
    namespace STM32
    {
        // ============================================================================
        // GPIO Enums
        // ============================================================================
        enum class Mode : uint32_t
        {
            Input = GPIO_MODE_INPUT,
            Output_Push_Pull = GPIO_MODE_OUTPUT_PP,
            Output_Open_Drain = GPIO_MODE_OUTPUT_OD,
            Alternate_Push_Pull = GPIO_MODE_AF_PP,
            Alternate_Open_Drain = GPIO_MODE_AF_OD,
            Analog = GPIO_MODE_ANALOG,
            Interrupt_Rising = GPIO_MODE_IT_RISING,
            Interrupt_Falling = GPIO_MODE_IT_FALLING,
            Interrupt_RisingFalling = GPIO_MODE_IT_RISING_FALLING,
            Event_Rising = GPIO_MODE_EVT_RISING,
            Event_Falling = GPIO_MODE_EVT_FALLING,
            Event_RisingFalling = GPIO_MODE_EVT_RISING_FALLING,
        };

        enum class Pull : uint32_t
        {
            None = GPIO_NOPULL,
            Up = GPIO_PULLUP,
            Down = GPIO_PULLDOWN,
        };

        enum class Speed : uint32_t
        {
            Low = GPIO_SPEED_FREQ_LOW,
            Medium = GPIO_SPEED_FREQ_MEDIUM,
            High = GPIO_SPEED_FREQ_HIGH,
            Very_High = GPIO_SPEED_FREQ_VERY_HIGH,
        };

        enum class Port : uint8_t
        {
            A = 0,
            B = 1,
            C = 2,
            D = 3,
            E = 4,
            F = 5,
            G = 6,
            H = 7,
            I = 8,
        };

        enum class Alternate : uint8_t
        {
            None = 0xFF,
            // SPI - Only available alternate functions in STM32G0xx
            SPI_AF0 = GPIO_AF0_SPI1, // SPI1 on AF0
            SPI_AF1 = GPIO_AF1_SPI2, // SPI2 on AF1 (STM32G0 uses AF1 for SPI2)
#ifdef GPIO_AF4_SPI2
            SPI_AF4 = GPIO_AF4_SPI2, // nur falls vorhanden
#endif
#ifdef GPIO_AF5_SPI1
            SPI_AF5 = GPIO_AF5_SPI1, // nur falls vorhanden
#endif
        // Higher AF numbers for SPI don't exist in STM32G0xx
        // CAN/FDCAN - Not available in STM32G0xx, use UCPD instead
#ifdef GPIO_AF3_FDCAN1
            CAN_AF3 = GPIO_AF3_FDCAN1, // nur falls vorhanden
#endif
            // UCPD (USB-C Power Delivery) available in STM32G0xx
            UCPD_AF0 = GPIO_AF0_UCPD1,
            UCPD_AF1 = GPIO_AF1_UCPD1,
            UCPD_AF3 = GPIO_AF3_UCPD1,
            UCPD_AF4 = GPIO_AF4_UCPD1
        };

        enum class ExtiTrigger : uint32_t
        {
            None = 0,
            Rising = GPIO_MODE_IT_RISING,
            Falling = GPIO_MODE_IT_FALLING,
            RisingFalling = GPIO_MODE_IT_RISING_FALLING,
        };

        // ============================================================================
        // SPI Enums
        // ============================================================================

        enum class SpiMode
        {
            Master = SPI_MODE_MASTER,
            Slave = SPI_MODE_SLAVE,
        };

        enum class SpiDirection
        {
            FullDuplex = SPI_DIRECTION_2LINES,        // 2 Leitungen: MOSI + MISO gleichzeitig aktiv
            RxOnly = SPI_DIRECTION_2LINES_RXONLY,     // 2 Leitungen: nur MISO aktiv (Receive Only)
            HalfDuplex = SPI_DIRECTION_1LINE,         // 1 Leitung: bidirektional (Tx ODER Rx)
            TxOnly = 0x1000,                          // Custom: Transmit Only (implementiert als Half-Duplex mit BIDIOE)
        };

        enum class SpiDataSize : uint32_t
        {
            Bits4 = SPI_DATASIZE_4BIT,
            Bits5 = SPI_DATASIZE_5BIT,
            Bits6 = SPI_DATASIZE_6BIT,
            Bits7 = SPI_DATASIZE_7BIT,
            Bits8 = SPI_DATASIZE_8BIT,
            Bits9 = SPI_DATASIZE_9BIT,
            Bits10 = SPI_DATASIZE_10BIT,
            Bits11 = SPI_DATASIZE_11BIT,
            Bits12 = SPI_DATASIZE_12BIT,
            Bits13 = SPI_DATASIZE_13BIT,
            Bits14 = SPI_DATASIZE_14BIT,
            Bits15 = SPI_DATASIZE_15BIT,
            Bits16 = SPI_DATASIZE_16BIT
        };

        enum class SpiClockPolarity
        {
            Low = SPI_POLARITY_LOW,
            High = SPI_POLARITY_HIGH,
        };

        enum class SpiClockPhase
        {
            FirstEdge = SPI_PHASE_1EDGE,
            SecondEdge = SPI_PHASE_2EDGE,
        };

        enum class SpiNSS
        {
            Soft = SPI_NSS_SOFT,
            Hard_In = SPI_NSS_HARD_INPUT,
            Hard_Out = SPI_NSS_HARD_OUTPUT,
        };

        // SPI NSSP Mode - Not available in STM32G0xx, so we provide fallback
        enum class SpiNSSPMode
        {
#ifdef SPI_NSSP_MODE_SOFTWARE
            Software = SPI_NSSP_MODE_SOFTWARE,
            Hardware = SPI_NSSP_MODE_HARDWARE,
#else
            // Fallback for STM32G0xx which doesn't have NSSP mode
            Software = 0,
            Hardware = 1,
#endif
        };

        enum class SpiBaudRatePrescaler
        {
            Prescaler2 = SPI_BAUDRATEPRESCALER_2,
            Prescaler4 = SPI_BAUDRATEPRESCALER_4,
            Prescaler8 = SPI_BAUDRATEPRESCALER_8,
            Prescaler16 = SPI_BAUDRATEPRESCALER_16,
            Prescaler32 = SPI_BAUDRATEPRESCALER_32,
            Prescaler64 = SPI_BAUDRATEPRESCALER_64,
            Prescaler128 = SPI_BAUDRATEPRESCALER_128,
            Prescaler256 = SPI_BAUDRATEPRESCALER_256,
        };

        enum class SpiFirstBit
        {
            MSB = SPI_FIRSTBIT_MSB,
            LSB = SPI_FIRSTBIT_LSB,
        };

        enum class SpiTIMode
        {
            Disable = SPI_TIMODE_DISABLE,
            Enable = SPI_TIMODE_ENABLE,
        };

        enum class SpiCRCCalculation
        {
            Disable = SPI_CRCCALCULATION_DISABLE,
            Enable = SPI_CRCCALCULATION_ENABLE,
        };

        enum class SpiCRCPolynomial
        {
#ifdef SPI_CRC_POLYNOMIAL_7
            Polynomial7 = SPI_CRC_POLYNOMIAL_7,
            Polynomial8 = SPI_CRC_POLYNOMIAL_8,
            Polynomial16 = SPI_CRC_POLYNOMIAL_16,
#else
            // Fallback values for STM32G0xx which doesn't support configurable CRC polynomials
            Polynomial7 = 7,
            Polynomial8 = 8,
            Polynomial16 = 16,
#endif
        };

        // CRC Length - Not available in STM32G0xx, provide fallback values
        enum class SpiCRCLength
        {
#ifdef SPI_CRC_LENGTH_DATASIZE
            Length_Data = SPI_CRC_LENGTH_DATASIZE,
            Length8 = SPI_CRC_LENGTH_8BIT,
            Length16 = SPI_CRC_LENGTH_16BIT,
#else
            // Fallback values for STM32G0xx
            Length_Data = 0,
            Length8 = 8,
            Length16 = 16,
#endif
        };

    } // namespace STM32
} // namespace HW_API

#endif // STM32_PLATFORM
