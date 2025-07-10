/**
 * @file    singleton.h
 *
 * @brief   Beschreibung
 *
 * @author  M. Grathwohl
 * @editor  K. Singh
 *
 * @date    2023/08/09
 *
 */

#ifndef _SINGLETON_H_
#define _SINGLETON_H_




//beware to make constructor of client class private
// ============================================================================
// Singleton Helper Macros for C++
// ----------------------------------------------------------------------------
// This header defines macros to implement the Singleton pattern in a safe,
// modular, and maintainable way.
//
// Why use these macros instead of writing the singleton manually?
// - Prevents copy/move constructors (ensures only one instance exists)
// - Centralizes pattern for consistency across classes
// - Splits declaration (.h) and definition (.cpp) cleanly
// ============================================================================


// SIMPLE MACRO (not recommended for large projects)
// ----------------------------------------------------------------------------
// Defines a singleton with everything inline in the header
// Usage in class header:
//   class MyClass {
//     SINGLETON(MyClass)
//   };
//
// Downside: This creates the instance **in every translation unit** that includes the header.
// That bloats code size and can lead to linker issues in embedded projects.
//
// Recommended only for header-only utilities or very small systems.

// Suitable for small projects or header-only libraries

#define SINGLETON(classname)    public: static classname& instance() { static classname instance; return instance; }

// PREFERRED: Split declaration and definition for better separation
// ----------------------------------------------------------------------------
// Use in the .h file of your class:
//
//   class MyClass {
//       SINGLETON_DECLARE(MyClass)
//   };
//
// This macro:
// - Declares `instance()` static method
// - Makes the constructor private
// - Deletes copy and assignment operators
//
// This avoids multiple definitions and improves encapsulation.

#define SINGLETON_DECLARE(className) \
    public: \
        static className& instance(); \
    private: \
        className(); \
        className(const className&) = delete; \
        className& operator=(const className&) = delete;


// Use in the .cpp file:
//
//   SINGLETON_DEFINE(MyClass)
//
// This macro defines the singleton method instance()
// The object is created exactly once, in a single translation unit.

#define SINGLETON_DEFINE(classname) \
    classname& classname::instance() { \
        static classname instance; \
        return instance; \
    }
// Note: Avoid defining instance() in header-only macros
//        to prevent multiple weak symbols or code duplication.


// Remove any existing code that defines instance() in the macro.
#endif /* _SINGLETON_H_ */
