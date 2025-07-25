// Minimal startup code for STM32C031C6
// Vector table and basic initialization

#include <stdint.h>

// Stack pointer (defined in linker script)
extern uint32_t _estack;

// Main function
extern int main(void);

// Reset handler
void Reset_Handler(void);

// Default handler
void Default_Handler(void) {
    while(1);
}

// Weak aliases for interrupt handlers
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));

// Vector table
__attribute__((section(".isr_vector")))
uint32_t vector_table[] = {
    (uint32_t)&_estack,         // Initial stack pointer
    (uint32_t)Reset_Handler,    // Reset handler
    (uint32_t)NMI_Handler,      // NMI handler
    (uint32_t)HardFault_Handler, // Hard fault handler
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    (uint32_t)SVC_Handler,      // SVCall handler
    0,                          // Reserved
    0,                          // Reserved
    (uint32_t)PendSV_Handler,   // PendSV handler
    (uint32_t)SysTick_Handler,  // SysTick handler
    // External interrupts for STM32C031C6 would go here...
};

// Reset handler implementation
void Reset_Handler(void) {
    // Copy data from flash to RAM
    extern uint32_t _sidata, _sdata, _edata;
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;
    while (dst < &_edata) {
        *dst++ = *src++;
    }
    
    // Zero out BSS section
    extern uint32_t _sbss, _ebss;
    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0;
    }
    
    // Call main
    main();
    
    // Should never reach here
    while(1);
}
