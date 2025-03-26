#ifndef CO_DRIVER_PIC_H
#define CO_DRIVER_PIC_H

#include <xc.h>
#include <stdint.h>

// CANopen Configuration Flags
#define CO_CONFIG_LSS (CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE | CO_CONFIG_LSS_SLAVE)
#define CO_CONFIG_NMT (CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE | CO_CONFIG_GLOBAL_FLAG_TIMERNEXT)

// PIC-specific CAN Handle
typedef struct {
    volatile uint8_t* can_ctrl_reg;
    uint16_t baudrate;
} CO_CANmodule_PIC;

// Locking Macros (Disable Interrupts)
#define CO_LOCK_CAN_SEND(CAN_MODULE) INTCONbits.GIE = 0
#define CO_UNLOCK_CAN_SEND(CAN_MODULE) INTCONbits.GIE = 1

#endif // CO_DRIVER_PIC_H
