#pragma once
#include <cstdint>
#include "CiA417_LiftTypes.h"

enum class COL_EventType 
{
    InputChanged,
    OutputReceived,
    RPDO_Received,
    TPDO_Transmitted,
    NMT_StateChanged,
    FunctionActivated,
    FunctionAcknowledged,
    Error,
    Custom
};

struct COL_Event 
{
    COL_EventType type;
    uint8_t sourceNodeId;
    union 
    {
        const libCOL_numbered_input_t* input;
        const libCOL_numbered_output_t* output;
        const void* custom;
    } payload;
};
