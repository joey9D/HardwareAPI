/**
 * @file    singleton.h
 *
 * @brief   Beschreibung
 *
 * @author  M. Grathwohl
 *
 * @date    2023/08/09
 *
 */

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

//beware to make constructor of client class private!
//#define SINGLETON(classname)    public: static classname& instance() { static classname instance; return instance; }


// singleton.h (modify this file)

#define SINGLETON(classname)    public: static classname& instance() { static classname instance; return instance; }

#define SINGLETON_DECLARE(className) \
    public: \
        static className& instance(); \
    private: \
        className(); \
        className(const className&) = delete; \
        className& operator=(const className&) = delete;

// Definition macro (use in .cpp)
#define SINGLETON_DEFINE(classname) \
    classname& classname::instance() { \
        static classname instance; \
        return instance; \
    }


// Remove any existing code that defines instance() in the macro
#endif /* _SINGLETON_H_ */
