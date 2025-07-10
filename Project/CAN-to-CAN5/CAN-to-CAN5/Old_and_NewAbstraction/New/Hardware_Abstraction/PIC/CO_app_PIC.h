#ifndef CO_APP_PIC_H
#define CO_APP_PIC_H

#include "CO_driver_PIC.h"



// PIC Version
typedef struct {
    uint8_t desiredNodeID;
    uint8_t activeNodeID;
    uint32_t baudrate;
    CO_CANmodule_PIC* can_hw;
    CO_t* canOpenStack;
} CANopenNodePIC;

void canopen_app_init(CICopenNodePIC* node);
uint8_t canopen_app_process(void);

#endif // CO_APP_PIC_H
