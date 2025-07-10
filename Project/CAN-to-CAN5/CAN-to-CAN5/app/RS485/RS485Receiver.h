#pragma once
#include "RS485Protocol.h"

class RS485Receiver {
public:
    static bool tryReceive(RS485Frame& outFrame);
};
