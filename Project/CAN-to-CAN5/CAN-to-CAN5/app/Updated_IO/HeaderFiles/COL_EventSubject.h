#pragma once
#include "COL_EventTypes.h"
#include <array>
#include <cstdint>


// === Observer Interfaces ===
class IInputObserver 
{
public:
    virtual void onInputEvent(const libCOL_numbered_input_t& input) = 0;
    virtual ~IInputObserver() = default;
};

class IOutputObserver 
{
public:
    virtual void onOutputEvent(const libCOL_numbered_output_t& output) = 0;
    virtual ~IOutputObserver() = default;
};

class IODObserver 
{
public:
    virtual void onODMappingChanged(uint8_t index, const virtualIOMapping_data_t& mapping) = 0;
};

class IRPDOObserver 
{
public:
    virtual void onRPDOReceived(const virtualIOMapping_data_t& output) = 0;
    virtual ~IRPDOObserver() = default;
};

class ITPDOObserver 
{
public:
    virtual void onTPDOTransmitRequest(const virtualIOMapping_data_t& input) = 0;
    virtual ~ITPDOObserver() = default;
};

// === Subject Types ===
constexpr size_t MaxObservers = 8;
constexpr size_t MaxHandlers = 4;

class InputEventSubject 
{
    std::array<IInputObserver*, MaxObservers> observers{};
    size_t count = 0;

public:
    void registerObserver(IInputObserver* obs) 
    {
        if (count < MaxObservers) observers[count++] = obs;
    }

    void notifyInput(const libCOL_numbered_input_t& input) 
    {
        for (size_t i = 0; i < count; ++i) observers[i]->onInputEvent(input);
    }
};

class OutputEventSubject 
{
    std::array<IOutputObserver*, MaxObservers> observers{};
    size_t count = 0;

public:
    void registerObserver(IOutputObserver* obs) 
    {
        if (count < MaxObservers) observers[count++] = obs;
    }

    void notifyOutput(const libCOL_numbered_output_t& output) 
    {
        for (size_t i = 0; i < count; ++i) observers[i]->onOutputEvent(output);
    }
};

class ODMappingSubject 
{
    std::array<IODObserver*, MaxObservers> observers{};
    size_t count = 0;

public:
    void registerObserver(IODObserver* obs) 
    {
        if (count < MaxObservers) observers[count++] = obs;
    }

    void notify(uint8_t index, const virtualIOMapping_data_t& mapping) 
    {
        for (size_t i = 0; i < count; ++i) observers[i]->onODMappingChanged(index, mapping);
    }
};

class RPDOEventSubject 
{
    std::array<IRPDOObserver*, MaxObservers> observers{};
    size_t count = 0;

public:
    void registerObserver(IRPDOObserver* obs) 
    {
        if (count < MaxObservers) observers[count++] = obs;
    }

    void notifyrpdo(const virtualIOMapping_data_t& output) 
    {
        for (size_t i = 0; i < count; ++i) observers[i]->onRPDOReceived(output);
    }
};

class TPDOEventSubject 
{
    std::array<ITPDOObserver*, MaxObservers> observers{};
    size_t count = 0;

public:
    void registerObserver(ITPDOObserver* obs) 
    {
        if (count < MaxObservers)
            observers[count++] = obs;
    }

    void notifyTPDO(const virtualIOMapping_data_t& input) 
    {
        for (size_t i = 0; i < count; ++i)
            observers[i]->onTPDOTransmitRequest(input);
    }
};

// === Low Size Handler ===
template<typename T>
struct SimpleInputHandler 
{
    libCOL_inputBasicFunction_t fn;
    T callback;

    bool matches(libCOL_inputBasicFunction_t bf) const { return fn == bf; }
    void call(const libCOL_input_t& in) const { callback(in); }
};

template<typename T>
struct SimpleOutputHandler 
{
    libCOL_outputBasicFunction_t fn;
    T callback;

    bool matches(libCOL_outputBasicFunction_t bf) const { return fn == bf; }
    void call(const libCOL_output_t& out) const { callback(out); }
};

template<typename T>
struct SimpleRPDOHandler 
{
    libCOL_outputBasicFunction_t fn;
    T callback;

    bool matches(libCOL_outputBasicFunction_t bf) const { return fn == bf; }
    void call(const virtualIOMapping_data_t& mapping) const { callback(mapping); }
};

template<typename T>
struct SimpleTPDOHandler 
{
    libCOL_inputBasicFunction_t fn;
    T callback;

    bool matches(libCOL_inputBasicFunction_t bf) const { return fn == bf; }
    void call(const virtualIOMapping_data_t& in) const { callback(in); }
};




// === Observer Template ===
template<typename Handler>
class GenericInputObserverT : public IInputObserver 
{
public:
    uint8_t myLiftMask = 0xFF, myFloor = 0xFF, mydoor = 0xFF;
    std::array<Handler, MaxHandlers> handlers{};
    size_t handlerCount = 0;

    template<typename F>
    void addHandler(libCOL_inputBasicFunction_t fn, F&& cb) 
    {
        if (handlerCount < handlers.size())
            handlers[handlerCount++] = Handler{fn, std::forward<F>(cb)};
    }

    void onInputEvent(const libCOL_numbered_input_t& wrapper) override 
    {
        const auto& in = wrapper.input;
        if (in.lift.raw != myLiftMask || in.floor != myFloor || in.door.raw != mydoor) return;

        for (size_t i = 0; i < handlerCount; ++i)
            if (handlers[i].matches(in.basicfunction))
                return handlers[i].call(in);
    }
};

class SimpleInputObserver : public IInputObserver {
    public:
        uint8_t myLiftMask = 0xFF;
        uint8_t myFloor = 0xFF;
        uint8_t myDoor = 0xFF;
    
        // Callback: static function that takes instance + input
        void (*callback)(GPIOHandler*, const libCOL_input_t&) = nullptr;
        GPIOHandler* instance = nullptr;
    
        void configure(libCOL_inputBasicFunction_t fn, GPIOHandler* inst, void (*cb)(GPIOHandler*, const libCOL_input_t&)) {
            myFunction = fn;
            instance = inst;
            callback = cb;
        }
    
        void onInputEvent(const libCOL_numbered_input_t& wrapper) override {
            const auto& in = wrapper.input;
            if (in.lift.raw != myLiftMask || in.floor != myFloor || in.door.raw != myDoor) return;
    
            if (callback && instance)
                callback(instance, in);  // <-- key line
        }
    
    private:
        libCOL_inputBasicFunction_t myFunction{};
    };
    

template<typename Handler>
class GenericOutputObserverT : public IOutputObserver 
{
public:
    uint8_t myLiftMask = 0xFF, myFloor = 0xFF, mydoor = 0xFF;
    std::array<Handler, MaxHandlers> handlers{};
    size_t handlerCount = 0;

    template<typename F>
    void addHandler(libCOL_outputBasicFunction_t fn, F&& cb) 
    {
        if (handlerCount < handlers.size())
            handlers[handlerCount++] = Handler{fn, std::forward<F>(cb)};
    }

    void onOutputEvent(const libCOL_numbered_output_t& wrapper) override 
    {
        const auto& out = wrapper.output;
        if (!(out.lift.raw & myLiftMask) || out.floor != myFloor || out.door.raw != mydoor) return;

        for (size_t i = 0; i < handlerCount; ++i)
            if (handlers[i].matches(out.basicfunction))
                return handlers[i].call(out);
    }
};


// === OD Change Logger (Optional) ===
class ODLogger : public IODObserver 
{
public:
    void onODMappingChanged(uint8_t, const virtualIOMapping_data_t&) override {}
};

template<typename Handler>
class GenericTPDOObserverT : public ITPDOObserver 
{
public:
    std::array<Handler, MaxHandlers> handlers{};
    size_t handlerCount = 0;

    template<typename F>
    void addHandler(libCOL_inputBasicFunction_t fn, F&& cb) 
    {
        if (handlerCount < handlers.size())
            handlers[handlerCount++] = Handler{fn, std::forward<F>(cb)};
    }

    void onTPDOTransmitRequest(const virtualIOMapping_data_t& in) override 
    {
        for (size_t i = 0; i < handlerCount; ++i)
            if (handlers[i].matches(static_cast<libCOL_inputBasicFunction_t>(in.basicFunction)))
                return handlers[i].call(in);
    }
};


template<typename Handler>
class GenericRPDOObserverT : public IRPDOObserver 
{
public:
    std::array<Handler, MaxHandlers> handlers{};
    size_t handlerCount = 0;

    template<typename F>
    void addHandler(libCOL_outputBasicFunction_t fn, F&& cb) 
    {
        if (handlerCount < handlers.size()) 
        {
            handlers[handlerCount++] = Handler{fn, std::forward<F>(cb)};
        }
    }

    // void onRPDOReceived(const virtualIOMapping_data_t& mapping) override {
    //     for (size_t i = 0; i < handlerCount; ++i) {
    //         if (handlers[i].matches(mapping.basicFunction)) {
    //             handlers[i].call(mapping);
    //             return;
    //         }
    //     }
    // }
    void onRPDOReceived(const virtualIOMapping_data_t& map) override 
    {
        for (size_t i = 0; i < handlerCount; ++i)
            if (handlers[i].matches(static_cast<libCOL_outputBasicFunction_t>(map.basicFunction)))
                return handlers[i].call(map);
    }
};

// class RPDOHandler : public IRPDOObserver {          
// public:
//     void onRPDOReceived(const virtualIOMapping_data_t& mapping) override {
//         // Handle RPDO received event
//     }
// };
// === Global Event Bus ===
struct COL_EventBus 
{
    InputEventSubject input;
    OutputEventSubject output;
    ODMappingSubject od;
    RPDOEventSubject rpdo;
    TPDOEventSubject tpdo;
};

inline COL_EventBus g_eventBus; // Ob es vermeidbar ist , gucken ??

// === Type Aliases ===

using MyInputObserver = SimpleInputObserver;
using MyOutputObserver = GenericOutputObserverT<SimpleOutputHandler<void(*)(const libCOL_output_t&)>>;
using MyRPDOObserver = GenericRPDOObserverT<SimpleRPDOHandler<void(*)(const virtualIOMapping_data_t&)>>;
using MyTPDOObserver = GenericTPDOObserverT<SimpleTPDOHandler<void(*)(const virtualIOMapping_data_t&)>>;

