#pragma once


#if defined(BOARD_STM32G0_DEV)
	#include "Boards/Development_Board.h"
    using ActiveBoardPins = BoardPins;

#else
    #error "No board selected. Define BOARD_STM32G0_DEV or BOARD_STM32G0_LCD."

#endif
