#ifndef __STM32G0XX_HPP
#define __STM32G0XX_HPP

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

/**
  * @brief STM32 Family
  */
 #if !defined (STM32G0)
 #define STM32G0
 #endif /* STM32G0 */
 
 /* Uncomment the line below according to the target STM32G0 device used in your
    application
   */
 
 #if !defined (STM32G071xx) && !defined (STM32G081xx) && !defined (STM32G070xx) \
  && !defined (STM32G030xx) && !defined (STM32G031xx) && !defined (STM32G041xx) \
  && !defined (STM32G0B0xx) && !defined (STM32G0B1xx) && !defined (STM32G0C1xx) \
  && !defined (STM32G050xx) && !defined (STM32G051xx) && !defined (STM32G061xx)
   /* #define STM32G0B0xx */   /*!< STM32G0B0xx Devices */
   /* #define STM32G0B1xx */   /*!< STM32G0B1xx Devices */
   /* #define STM32G0C1xx */   /*!< STM32G0C1xx Devices */
   /* #define STM32G070xx */   /*!< STM32G070xx Devices */
   /* #define STM32G071xx */   /*!< STM32G071xx Devices */
   /* #define STM32G081xx */   /*!< STM32G081xx Devices */
   /* #define STM32G050xx */   /*!< STM32G050xx Devices */
   /* #define STM32G051xx */   /*!< STM32G051xx Devices */
   /* #define STM32G061xx */   /*!< STM32G061xx Devices */
   /* #define STM32G030xx */   /*!< STM32G030xx Devices */
   /* #define STM32G031xx */   /*!< STM32G031xx Devices */
   /* #define STM32G041xx */   /*!< STM32G041xx Devices */
 #endif


/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.
  */
#if !defined  (USE_HAL_DRIVER)
/**
 *  @brief Comment the line below if you will not use the peripherals drivers.
    In this case, these drivers will not be included and the application code will
    be based on direct access to peripherals registers
    */
/*#define USE_HAL_DRIVER */
#endif /* USE_HAL_DRIVER */

/**
 * Includes the cmsis header file.
 */
#if defined(STM32G0B1xx)
  #include "stm32g0b1xx.h"
#elif defined(STM32G0C1xx)
  #include "stm32g0c1xx.h"
#elif defined(STM32G0B0xx)
  #include "stm32g0b0xx.h"
#elif defined(STM32G071xx)
  #include "stm32g071xx.h"
#elif defined(STM32G081xx)
  #include "stm32g081xx.h"
#elif defined(STM32G070xx)
  #include "stm32g070xx.h"
#elif defined(STM32G031xx)
  #include "stm32g031xx.h"
#elif defined(STM32G041xx)
  #include "stm32g041xx.h"
#elif defined(STM32G030xx)
  #include "stm32g030xx.h"
#elif defined(STM32G051xx)
  #include "stm32g051xx.h"
#elif defined(STM32G061xx)
  #include "stm32g061xx.h"
#elif defined(STM32G050xx)
  #include "stm32g050xx.h"
#else
 #error "Please select first the target STM32G0xx device used in your application (in stm32g0xx.h file)"
#endif

#if defined (USE_HAL_DRIVER)
 #include "stm32g0xx_hal.h"
#endif /* USE_HAL_DRIVER */


#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif /* __STM32G0XX_HPP */