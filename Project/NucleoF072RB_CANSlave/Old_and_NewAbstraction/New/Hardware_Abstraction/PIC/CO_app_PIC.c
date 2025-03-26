// PIC Version (using Timer1)
#include "CO_app_PIC.h"
#include <xc.h>

CANopenNodePIC* canopen_node;

void canopen_app_init(CANopenNodePIC* node) {
    canopen_node = node;
    CO_CANmodule_init(node->canOpenStack->CANmodule, node->can_hw, ...);
    CO_CANsetNormalMode(node->canOpenStack->CANmodule);

    // Configure Timer1 for 1ms interrupts
    T1CON = 0x8030; // Prescaler 1:8, 16-bit mode
    TMR1 = 0;
    PR1 = 2000; // Adjust for 1ms @ Fosc=16MHz
    _T1IE = 1;  // Enable Timer1 interrupt
}

uint8_t canopen_app_process() {
    if (_T1IF) {
        _T1IF = 0; // Clear interrupt flag
        CO_process(canopen_node->canOpenStack, false, 1000, NULL);
        return 1;
    }
    return 0;
}
