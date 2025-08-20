#pragma once

#include "../spi/spi_stm32.hpp"
#include "../spi/dma_stm32.hpp"

/**
 * @brief Verknüpft ein SPI-Objekt mit einem DMA-Objekt
 *
 * Diese Funktion setzt die bidirektionale Verknüpfung zwischen einem SPI- und einem DMA-Objekt.
 * Das DMA-Objekt erhält den SPI-Handle und das SPI-Objekt erhält eine Referenz auf das DMA-Objekt.
 *
 * @param spiObject Referenz auf das SPI-Objekt
 * @param dmaObject Referenz auf das DMA-Objekt
 */
inline void linkSpiWithDma(Spi &spiObject, Dma &dmaObject)
{
    // SPI-Handle an DMA übergeben
    dmaObject.setSpiHandle(spiObject.get_handle());

    // DMA-Objekt im SPI-Objekt registrieren
    spiObject.set_dma(&dmaObject);
}