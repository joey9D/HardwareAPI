#pragma once

/**
 * @file hw_enum_stm32.hpp
 * @brief Platform-spezifische Enum-Definitionen für STM32-MCUs
 *
 * Dieser Header definiert typsichere enum class Werte, die die HAL-Makros kapseln.
 * Die Enums sind in Namespaces organisiert und unterstützen verschiedene STM32-Familien
 * mit Fallback-Werten für nicht unterstützte Features.
 */

// Platform-specific GPIO enums for STM32
#ifdef STM32_PLATFORM

// Use our central HAL include that handles family detection
#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"
#include <cstdint>

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
            // SPI - Common for all STM32 series
            SPI_AF0 = GPIO_AF0_SPI1, // SPI1 on AF0

#ifdef GPIO_AF1_SPI2
            SPI_AF1 = GPIO_AF1_SPI2, // SPI2 on AF1 (für STM32G0)
#endif
#ifdef GPIO_AF4_SPI2
            SPI_AF4 = GPIO_AF4_SPI2, // für andere STM32-Familien
#endif
#ifdef GPIO_AF5_SPI1
            SPI_AF5 = GPIO_AF5_SPI1, // für andere STM32-Familien
#endif

        // CAN/FDCAN - Nur verfügbar wenn definiert
#ifdef GPIO_AF3_FDCAN1
            CAN_AF3 = GPIO_AF3_FDCAN1,
#endif

        // UCPD (USB-C Power Delivery) - Nur verfügbar wenn definiert
#ifdef GPIO_AF0_UCPD1
            UCPD_AF0 = GPIO_AF0_UCPD1,
#endif
#ifdef GPIO_AF1_UCPD1
            UCPD_AF1 = GPIO_AF1_UCPD1,
#endif
#ifdef GPIO_AF3_UCPD1
            UCPD_AF3 = GPIO_AF3_UCPD1,
#endif
#ifdef GPIO_AF4_UCPD1
            UCPD_AF4 = GPIO_AF4_UCPD1,
#endif
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
#ifdef HAL_SPI_MODULE_ENABLED
        // ============================================================================

        /**
         * @brief SPI-Betriebsmodus (Master oder Slave)
         *
         * Definiert, ob das SPI-Interface als Master oder Slave arbeitet.
         * - Master: Generiert den Clock und kontrolliert NSS
         * - Slave: Empfängt Clock und NSS vom Master
         */
        enum class SpiMode : uint32_t
        {
            Master = SPI_MODE_MASTER,
            Slave = SPI_MODE_SLAVE,
        };

        /**
         * @brief SPI-Datenrichtung (Vollduplex/Halbduplex/Nur-RX)
         *
         * Bestimmt die Richtung der Datenübertragung und welche Leitungen verwendet werden.
         * Hinweis: Für Transmit-Only wird HalfDuplex mit gesetztem BIDIOE-Bit verwendet.
         */
        enum class SpiDirection : uint32_t
        {
            FullDuplex = SPI_DIRECTION_2LINES,    ///< 2 Leitungen: MOSI + MISO gleichzeitig aktiv
            RxOnly = SPI_DIRECTION_2LINES_RXONLY, ///< 2 Leitungen: nur MISO aktiv (Receive Only)
            HalfDuplex = SPI_DIRECTION_1LINE,     ///< 1 Leitung: bidirektional (Tx ODER Rx)
        };

        /**
         * @brief SPI-Datengröße (4-16 Bits pro Frame)
         *
         * Definiert die Anzahl der Bits pro SPI-Datenframe.
         * Die meisten Anwendungen verwenden 8-Bit (Byte) oder 16-Bit (Halbwort).
         */
        enum class SpiDataSize : uint32_t
        {
            Bits4 = SPI_DATASIZE_4BIT,   ///< 4-Bit pro Frame
            Bits5 = SPI_DATASIZE_5BIT,   ///< 5-Bit pro Frame
            Bits6 = SPI_DATASIZE_6BIT,   ///< 6-Bit pro Frame
            Bits7 = SPI_DATASIZE_7BIT,   ///< 7-Bit pro Frame
            Bits8 = SPI_DATASIZE_8BIT,   ///< 8-Bit pro Frame (Standard für die meisten Anwendungen)
            Bits9 = SPI_DATASIZE_9BIT,   ///< 9-Bit pro Frame
            Bits10 = SPI_DATASIZE_10BIT, ///< 10-Bit pro Frame
            Bits11 = SPI_DATASIZE_11BIT, ///< 11-Bit pro Frame
            Bits12 = SPI_DATASIZE_12BIT, ///< 12-Bit pro Frame
            Bits13 = SPI_DATASIZE_13BIT, ///< 13-Bit pro Frame
            Bits14 = SPI_DATASIZE_14BIT, ///< 14-Bit pro Frame
            Bits15 = SPI_DATASIZE_15BIT, ///< 15-Bit pro Frame
            Bits16 = SPI_DATASIZE_16BIT  ///< 16-Bit pro Frame (Halbwort)
        };

        enum class SpiClockPolarity : uint32_t
        {
            Low = SPI_POLARITY_LOW,
            High = SPI_POLARITY_HIGH,
        };

        enum class SpiClockPhase : uint32_t
        {
            FirstEdge = SPI_PHASE_1EDGE,
            SecondEdge = SPI_PHASE_2EDGE,
        };

        enum class SpiNSS : uint32_t
        {
            Soft = SPI_NSS_SOFT,
            Hard_In = SPI_NSS_HARD_INPUT,
            Hard_Out = SPI_NSS_HARD_OUTPUT,
        };

        enum class SpiNSSPMode : uint32_t
        {
            Enable = SPI_NSS_PULSE_ENABLE,
            Disable = SPI_NSS_PULSE_DISABLE
        };

        enum class SpiBaudRatePrescaler : uint32_t
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

        enum class SpiFirstBit : uint32_t
        {
            MSB = SPI_FIRSTBIT_MSB,
            LSB = SPI_FIRSTBIT_LSB,
        };

        enum class SpiTIMode : uint32_t
        {
            Disable = SPI_TIMODE_DISABLE,
            Enable = SPI_TIMODE_ENABLE,
        };

        enum class SpiCRCCalculation : uint32_t
        {
            Disable = SPI_CRCCALCULATION_DISABLE,
            Enable = SPI_CRCCALCULATION_ENABLE,
        };

        //         enum class SpiCRCPolynomial : uint32_t
        //         {
        // #ifdef SPI_CRC_POLYNOMIAL_7
        //             Polynomial7 = SPI_CRC_POLYNOMIAL_7,
        //             Polynomial8 = SPI_CRC_POLYNOMIAL_8,
        //             Polynomial16 = SPI_CRC_POLYNOMIAL_16,
        // #else
        //             // Fallback values for STM32G0xx which doesn't support configurable CRC polynomials
        //             Polynomial7 = 7,
        //             Polynomial8 = 8,
        //             Polynomial16 = 16,
        // #endif
        //         };

        enum class SpiCRCLength : uint32_t
        {
            Length_Data = SPI_CRC_LENGTH_DATASIZE,
            Length8 = SPI_CRC_LENGTH_8BIT,
            Length16 = SPI_CRC_LENGTH_16BIT,
        };

        // ============================================================================
        // DMA Enums
        // ============================================================================

        /**
         * @brief DMA Request Type
         *
         */
        enum class DmaRequest : uint32_t
        {
            SPI1_TX = DMA_REQUEST_SPI1_TX,
            SPI1_RX = DMA_REQUEST_SPI1_RX,
#ifdef SPI2
            SPI2_TX = DMA_REQUEST_SPI2_TX,
            SPI2_RX = DMA_REQUEST_SPI2_RX,
#endif
        };

        /**
         * @brief DMA Transfer-Richtung
         *
         * Definiert die Richtung des DMA-Transfers: von Peripherie zu Speicher,
         * von Speicher zu Peripherie oder von Speicher zu Speicher.
         */
        enum class DmaDirection : uint32_t
        {
            PeriphToMem = DMA_PERIPH_TO_MEMORY,
            MemToPeriph = DMA_MEMORY_TO_PERIPH,
            MemToMem = DMA_MEMORY_TO_MEMORY,
        };

        /**
         * @brief DMA Adress-Inkrement-Modus
         *
         * Definiert, ob die Adresse bei jedem Transfer-Schritt erhöht wird.
         */
        enum class DmaPeriphInc : uint32_t
        {
            Disable = DMA_PINC_DISABLE,
            Enable = DMA_PINC_ENABLE,
        };

        /**
         * @brief DMA Memory-Inkrement-Modus
         *
         * Bestimmt, ob die Adresse bei jedem Transfer-Schritt erhöht wird.
         */
        enum class DmaMemInc : uint32_t
        {
            Enable = DMA_MINC_ENABLE,
            Disable = DMA_MINC_DISABLE,
        };

        /**
         * @brief DMA Daten-Ausrichtung
         *
         * Bestimmt die Größe der Daten, die bei jedem Transfer übertragen werden.
         *
         */
        enum class DmaPeriphDataSizeAlignment : uint32_t
        {
            Byte = DMA_PDATAALIGN_BYTE,         ///< 8-Bit Daten (uint8_t)
            HalfWord = DMA_PDATAALIGN_HALFWORD, ///< 16-Bit Daten (uint16_t)
            Word = DMA_PDATAALIGN_WORD,         ///< 32-Bit Daten (uint32_t)
        };

        enum class DmaMemDataSizeAlignment : uint32_t
        {
            Byte = DMA_MDATAALIGN_BYTE,         ///< 8-Bit Daten (uint8_t)
            HalfWord = DMA_MDATAALIGN_HALFWORD, ///< 16-Bit Daten (uint16_t)
            Word = DMA_MDATAALIGN_WORD,         ///< 32-Bit Daten (uint32_t)
        };

        /**
         * @brief DMA Betriebsmodus
         *
         * Definiert, ob der DMA-Kanal im normalen oder zirkulären Modus arbeitet.
         * Zirkulärer Modus startet automatisch neu nach Transfer-Ende.
         */
        enum class DmaMode : uint32_t
        {
            Normal = DMA_NORMAL,
            Circular = DMA_CIRCULAR,
        };

        /**
         * @brief DMA Kanal-Priorität
         *
         * Bestimmt die Priorität des DMA-Kanals bei Konflikten mit anderen Kanälen.
         */
        enum class DmaPriority : uint32_t
        {
            Low = DMA_PRIORITY_LOW,
            Medium = DMA_PRIORITY_MEDIUM,
            High = DMA_PRIORITY_HIGH,
            VeryHigh = DMA_PRIORITY_VERY_HIGH
        };
#endif // HAL_SPI_MODULE_ENABLED

    } // namespace STM32
} // namespace HW_API

#endif // STM32_PLATFORM
