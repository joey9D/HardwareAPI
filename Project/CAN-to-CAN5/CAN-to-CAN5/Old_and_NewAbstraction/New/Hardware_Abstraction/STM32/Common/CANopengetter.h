#ifndef CANOPENGETTER_H_
#define CANOPENGETTER_H_

// #include "iCanOpenNode.h"




class CANopengetter


{
    private:
    // CanOpenNodeSTM32 canopen; ///< Pointer to the CANopenNode interface
    // CANopenNodeSTM32_t* canopenNodeSTM32_t; // Pointer to the CANopenNode Structure
    bool nodestate = false; ///< Node state, true if node is initialized and running

    public:
    CANopengetter() = default; ///< Default constructor
    // int  CANopenNode_Init() override;              ///< Initialize CANopenNode
    // uint8_t   CANopenNode_Process() override;           ///< Process CANopenNode tasks
    // uint32_t CANopenNode_Reset() override;            ///< Reset CANopenNode state
    // void CANopenNode_Interrupt() override ;         ///< Handle CANopenNode interrupt   
    // inline CO_RPDO_t* getRPDO() override {return canopenNodeSTM32_t->canOpenStack->RPDO;}
    // inline void getTPDOsend() override {canopenNodeSTM32_t->canOpenStack->TPDO[0].sendRequest = 1; } ///< Get TPDO pointer
    // inline CO_RPDO_t* getRPDOwithIndex(uint8_t index) override {return &canopenNodeSTM32_t->canOpenStack->RPDO[index]; } ///< Send TPDO message
    // inline uint8_t getLedgreenstate() override {return canopenNodeSTM32_t->outStatusLEDGreen; } ///< Get green LED state
    // inline uint8_t getLedredstate() override {return canopenNodeSTM32_t->outStatusLEDRed; } ///< Get red LED state
    // inline CO_SDOserver_t* getSDO() override {return canopenNodeSTM32_t->canOpenStack->SDOserver; } ///< Get SDO pointer
    // inline CO_NMT_t* getNMT() override {return canopenNodeSTM32_t->canOpenStack->NMT; } ///< Get NMT pointer
    // bool isnodeIdValid() override; ///< Check if node ID is valid
    // bool getNodestate(int state) override; ///< Get node state

    // void timingHandler();
};


#endif // CANOPENGETTER_H_


