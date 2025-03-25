#ifndef _STM32FACTORY_HPP
#define _STM32FACTORY_HPP

/* header guard to prevent c++ namemangling */
#ifdef  __cplusplus
    extern "C"{
#endif /* __cplusplus */


/**
 * @brief   STM32 family.
 *          
 */
#if defined(STM32F4xx)
    #include "stm32f4xx.hpp"
#elif defined(STM32G0xx)
    #include "stm32g0xx.hpp"
#else
    #error "Platform family is not defined. Select a supported STM32 family."
#endif


#ifdef __cplusplus
    }
#endif /* __cplusplus */
#endif /* _STM32FACTORY_HPP */