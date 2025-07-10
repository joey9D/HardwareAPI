#include "OD.h"

OD_entry_t OD_entries[] = {
    {0x1000, 0x00, 0xDEADBEEF},
    {0x1018, 0x00, 0x04},
};

uint32_t OD_entryCount = sizeof(OD_entries) / sizeof(OD_entry_t);
