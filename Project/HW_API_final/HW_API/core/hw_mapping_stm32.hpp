#pragma once

#include "../drivers/stm32_hal_wrapper/common/stm32_hal_inc.hpp"

namespace HW_API {
namespace STM32 {

// DMA-Mapping für SPI-Peripherie basierend auf STM32-Familie
struct SPIDMAMapping {
    DMA_Channel_TypeDef* txChannel;
    DMA_Channel_TypeDef* rxChannel;
    uint32_t txRequest;
    uint32_t rxRequest;
};

// DMA-Mapping pro SPI-Instanz - automatisch abhängig von der definierten STM32-Familie
#if defined(STM32G0)
// STM32G0-spezifisches Mapping
inline SPIDMAMapping getSPIDMAMapping(SPI_TypeDef* spi) {
    if (spi == SPI1)
        return {DMA1_Channel3, DMA1_Channel2, DMA_REQUEST_SPI1_TX, DMA_REQUEST_SPI1_RX};
    else if (spi == SPI2)
        return {DMA1_Channel5, DMA1_Channel4, DMA_REQUEST_SPI2_TX, DMA_REQUEST_SPI2_RX};
    // usw.
    return {nullptr, nullptr, 0, 0}; // Fehlerfall
}
#elif defined(STM32F4)
// STM32F4-spezifisches Mapping (andere Struktur)
inline SPIDMAMapping getSPIDMAMapping(SPI_TypeDef* spi) {
    if (spi == SPI1)
        return {DMA2_Stream3, DMA2_Stream2, DMA_CHANNEL_3, DMA_CHANNEL_3};
    // usw.
    return {nullptr, nullptr, 0, 0}; // Fehlerfall
}
#else
// Fallback für unbekannte STM32-Familien
#error "Unsupported STM32 family for DMA mapping"
#endif

} // namespace STM32
} // namespace HW_API