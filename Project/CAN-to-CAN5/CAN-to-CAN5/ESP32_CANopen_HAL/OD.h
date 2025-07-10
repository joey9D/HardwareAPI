#ifndef OD_H
#define OD_H

#include <stdint.h>

typedef struct {
    uint16_t index;
    uint8_t subIndex;
    uint32_t value;
} OD_entry_t;

extern OD_entry_t OD_entries[];
extern uint32_t OD_entryCount;

#endif // OD_H
