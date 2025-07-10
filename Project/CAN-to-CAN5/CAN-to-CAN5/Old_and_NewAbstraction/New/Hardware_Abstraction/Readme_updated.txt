# STM32 Universal Hardware Abstraction Layer

## Supported Series
| Series       | Features                          | Boards Tested          |
|--------------|-----------------------------------|------------------------|
| STM32F0      | Basic GPIO, CAN                   | 	                    |
| STM32F4      | TFT (LTDC), FDCAN                 |                        |
| STM32H7      | Dual-core, Chrom-ART Accelerator  |                        |
| STM32WL      | LoRa, Sub-GHz RF                  |                        |

## Quick Start
1. Select your board and series:
```bash
cmake -DSTM32_SERIES=H7 -DBOARD=disco_h743 ..