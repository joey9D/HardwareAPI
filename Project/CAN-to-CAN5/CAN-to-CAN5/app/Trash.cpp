namespace nket::protocol {

// ---------------------------------------------------------------------------
// A generic 64-bit hall-call bitmask: 8 bytes × 8 bits = 64 floors.
// Usage:
//   HallCallDisplayData d = parseHallUpCallDisplayFrontSide(data);
//   d.extractActiveFloors();
//   for(uint8_t i=0; i<d.floorCount; ++i) {
//     uint8_t floor = d.floors[i];
//     // handle active floor...
//   }

// struct HallCallDisplayData 
// {
//     static constexpr uint8_t NumFloors   = 64;
//     static constexpr uint8_t NumBytes    = 8;
//     static constexpr uint8_t MaxActive   = NumFloors;

//     uint8_t bits[NumBytes];           // raw CAN payload
//     uint8_t floors[MaxActive];        // filled by extractActiveFloors()
//     uint8_t floorCount = 0;           // number of entries in `floors[]`

//     /// bit-test for a single floor (1…64)
//     bool isSet(uint8_t floor) const noexcept 
//     {
//         if (floor < 1 || floor > NumFloors) return false;
//         auto idx = (floor - 1) / 8;    // byte index
//         auto b   = (floor - 1) % 8;    // bit index
//         return (bits[idx] >> b) & 0x1;
//     }

//     /// Populate `floors[]` with all set bits, in ascending order.
//     void extractActiveFloors() noexcept 
//     {
//         floorCount = 0;
//         for (uint8_t byteIdx = 0; byteIdx < NumBytes; ++byteIdx) 
//         {
//             uint8_t mask = bits[byteIdx];
//             while (mask && floorCount < MaxActive) 
//             {
//                 // find least-significant set bit
//                 uint8_t bit = __builtin_ctz(mask);  
//                 uint8_t fl  = byteIdx * 8 + bit + 1; 
//                 floors[floorCount++] = fl;
//                 mask &= uint8_t(mask - 1);      // clear that bit
//             }
//         }
//     }
// };

// // Four parsers (one per message ID), all identical internally:
// inline HallCallDisplayData parseHallUpCallDisplayFrontSide(const uint8_t* data) 
// {
//     HallCallDisplayData d{};
//     for (int i = 0; i < HallCallDisplayData::NumBytes; ++i) 
//     {
//         d.bits[i] = data[i];
//     }
//     return d;
// }
// inline HallCallDisplayData parseHallDownCallDisplayFrontSide(const uint8_t* data) 
// {
//     HallCallDisplayData d{};
//     for (int i = 0; i < HallCallDisplayData::NumBytes; ++i) 
//     {
//         d.bits[i] = data[i];
//     }
//     return d;
// }
// inline HallCallDisplayData parseHallUpCallDisplayRearSide(const uint8_t* data) 
// {
//     HallCallDisplayData d{};
//     for (int i = 0; i < HallCallDisplayData::NumBytes; ++i) 
//     {
//         d.bits[i] = data[i];
//     }
//     return d;
// }
// inline HallCallDisplayData parseHallDownCallDisplayRearSide(const uint8_t* data) 
// {
//     HallCallDisplayData d{};
//     for (int i = 0; i < HallCallDisplayData::NumBytes; ++i) 
//     {
//         d.bits[i] = data[i];
//     }
//     return d;
// }
}
