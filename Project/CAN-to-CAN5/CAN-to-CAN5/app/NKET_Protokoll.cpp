#include "NKET_Protokoll.h"



ElevatorStatusMastertoLOP0 NKET_Protokoll::parseElevatorStatuslandData0(const uint8_t* data) 
{
    ElevatorStatusMastertoLOP0 msg{};
    msg.reserved0      = data[0];
    msg.currentFloor   = data[1];
    msg.ElevatorDataMastertoLOP0    = data[2];
    msg.reserved3      = data[3];
    msg.reserved4      = data[4];
    msg.AttendantDataMastertoLOP0 = data[5];
    msg.LoadDataMastertoLOP0 = data[6];
    msg.runningSpeed   = data[7];
    return msg;
}


ElevatorStatusMastertoLOP1 NKET_Protokoll::parseElevatorStatuslandData1(const uint8_t* data) 
{
    ElevatorStatusMastertoLOP1 msg{};
    msg.reserved0                               = data[0];
    msg.ElevatorSpecialAccessMastertoLOP1       = data[1];
    msg.ElevatorSpecialIndicationMastertoLOP1   = data[2];
    msg.reserved3                               = data[3];
    msg.reserved4                               = data[4];
    msg.ElevatorStateMastertoLOP1               = data[5];
    return msg;
}


ElevatorStatusMastertoLOP2 NKET_Protokoll::parseElevatorStatuslandData2(const uint8_t* data) 
{
    ElevatorStatusMastertoLOP2 msg{};
    msg.FloorAscL = data[0];
    msg.FloorAscM = data[1];
    msg.FloorAscH = data[2];
    return msg;
}

ElevatorStatusMastertoLOP3 NKET_Protokoll::parseElevatorStatuslandData3(const uint8_t* data) 
{
    ElevatorStatusMastertoLOP3 msg{};
    msg.ElevatorStateMastertoLOP3 = data[0]; 
    return msg;
}

FloorBitfield NKET_Protokoll::parseFloorBitfield(const uint8_t* data) 
{
    FloorBitfield bitfield{};
    for (int i = 0; i < 8; ++i) {
        bitfield.data[i] = data[i];
    }
    return bitfield;
}


FloorMessage NKET_Protokoll::parseFloorMessage(const uint8_t* data) 
{
    FloorMessage msg{};
    msg.floor = data[1]; // Byte1
    return msg;
}

ElevatorStatusMastertoCOP0 NKET_Protokoll::parseElevatorStatusCarData0(const uint8_t* data) 
{
    ElevatorStatusMastertoCOP0 msg{};
    msg.reserved0                      = data[0];
    msg.currentFloor                   = data[1];
    msg.ElevatorStatusDataMastertoCOP0 = data[2];
    msg.reserved3                      = data[3];
    msg.reserved4                      = data[4];
    msg.AttendantFlagsMastertoCOP0     = data[5];
    msg.LoadCarFlagsMastertoCOP0       = data[6];
    msg.runningSpeed                   = data[7];
    return msg;
}

ElevatorStatusMastertoCOP1 NKET_Protokoll::parseElevatorStatusCarData1(const uint8_t* data) 
{
    ElevatorStatusMastertoCOP1 msg{};
    msg.reserved0                    = data[0];
    msg.reserved1                    = data[1];
    msg.ElevatorDataMastertoCOP1     = data[2];
    msg.reserved3                    = data[3];
    msg.reserved4                    = data[4];
    msg.SoundFlagsMastertoCOP1       = data[5];
    msg.reserved6                    = data[6];
    msg.LightFlagsMastertoCOP1       = data[7];
    return msg;
}

ElevatorStatusMastertoCOP2 NKET_Protokoll::parseElevatorStatusCarData2(const uint8_t* data) 
{
    ElevatorStatusMastertoCOP2 msg{};
    msg.ElevatorDataMastertoCOP2 = data[0]; 
    return msg;
}

COPtoMasterDataspecialfunction_FS NKET_Protokoll::parseCarCallSpecialFunctionData_FS(const uint8_t* data) 
{
    COPtoMasterDataspecialfunction_FS msg{};
    msg.SpecialFunctionCOPtoMasterFS1 = data[0]; // Byte 0
    msg.SpecialFunctionCOPtoMasterFS2 = data[1]; // Byte 1
    return msg;
}

COPtoMasterDataspecialfunction_RS NKET_Protokoll::parseCarCallSpecialFunctionData_RS(const uint8_t* data) 
{
    COPtoMasterDataspecialfunction_RS msg{};
    msg.SpecialFunctionCOPtoMasterRS1 = data[0]; // Byte 0
    msg.SpecialFunctionCOPtoMasterRS2 = data[1]; // Byte 1
    return msg;
}

std::array<uint32_t, 13> NKET_Protokoll::getIncomingCANMessageIDs() const
{
    std::array<uint32_t, 13> ids;
    for (size_t i = 0; i < IncomingCANMessages.size(); ++i) 
    {
        ids[i] = static_cast<uint32_t>(IncomingCANMessages[i]);
    }
    return ids;
}
