#ifndef PINS_CONFIG_H
#define PINS_CONFIG_H

#include <cstdint>
#include <cassert>
#include <type_traits>
#include "CiA417_LiftTypes.h"
#include "../basic/singleton.h"



#define NUMBER_OF_CLAMPS 2 // To be defined later
#define OD_inputAdjustment 2  // To be defined later


/*All Pin Structures Mentioned here*/
#define clamp_get_active(x)         (x != 0)
#define clamp_get_defined_input(x)  ((x & 0x1) != 0)
#define clamp_get_defined_output(x) ((x & 0x2) != 0)
#define clamp_get_active_input(x)   ((x & 0x4) != 0)
#define clamp_get_active_output(x)  ((x & 0x8) != 0)
#define clamp_get_defined_io(x)     ((x & 0x3) == 0x3)
#define clamp_switch_io(x)          (x = (x ^ 0xC))

#define get_gray(x)                 (x = (x ^ (x >> 1))) /* See: Graycode */

static uint8_t seven_segment_table[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F/*,0x77,0x7C,0x39,0x5E,0xF9,0x71*/};
static uint8_t seven_segment_pos[4] = {1,10,100,100};

#define CLAMP_INPUT_INIT_TIME_MS    3


typedef enum clamp_state_tag {
	clamp_state_inactive = 0x00, /**< inactive/unused */
	clamp_state_input_only = 0x05, /**< configured and active as an input */
	clamp_state_output_only = 0x0A, /**< configured and active as an output */
	clamp_state_io_input = 0x07, /**< configured as IO and active as an input */
	clamp_state_io_output = 0x0B /**< configured as IO and active as an output */
} clamp_state_t;

typedef struct clamp_input_pdo_tag { // Used in Stack *****************************
    /**
     * The number of the clamp.
     */
    uint8_t clampNumber {0};
    /**
     * The data of the input.
     */
    libCOL_inputFunctionData_t data;
} clamp_input_pdo_t;

typedef struct clamp_input_tag {
	/**
	 * The index of the assigned virtual input in our local array.
	 */
	uint8_t virtualInputIndex;
	/**
	 * The last time stamp of a debounce start.
	 */
	uint32_t debounceLast;
	/**
	 * The last time stamp of setting this clamp to an input.
	 */
	uint32_t initLast;
	/**
	 * The last time stamp of setting this clamp to an input.
	 */
	uint32_t cycleLast;
	/**
	 * The last measured logical state of the input.
	 */
	bool measuredActive;
	/**
	 * The last transmittable logical state of the input.
	 */
	bool physicalActive;
	/**
	 * Last transmitted logical state of the input.
	 */
	bool virtualActive;
	/**
	 * If input has been requested by a call command.
	 */
	bool requested;
	/**
	 * If input has been configured to be negated.
	 */
	bool negated;
	/**
	 * If input has been configured for cyclic broadcast.
	 */
	bool cycled;
	/**
	 * If input is a call.
	 */
	bool isCall;
	/**
	 * If call was active before a reset.
	 */
	bool savedCall;
	/**
	 * If next input transmission should be forced to high.
	 */
	bool sendActiveNext;
	/**
	 * Index of corresponding Virtual Output.
	 */
	uint8_t callVirtualOutputIndex;
	/**
	 * If a corresponding Virtual Output exists.
	 */
	bool callVirtualOutputFound;
} clamp_input_t;

typedef enum clamp_output_type_tag {
	clamp_output_type_binary = 0x00, /**< Physical outputs are assigned to single bits. */
	clamp_output_type_gray = 0x01, /**< Physical outputs are assigned to single bits and virtual output uses graycode. */
	clamp_output_type_1ofN = 0x02, /**< Physical outputs are assigned to a single possible output state */
	clamp_output_type_7segment = 0x03 /**< Physical outputs are assigned to a single possible output state */
} clamp_output_type_t;

typedef struct clamp_output_tag {
	/**
	 * The index of the assigned virtual output in our local array.
	 */
	uint8_t virtualOutputIndex;
	/**
	 * Bitmask, if the virtual output uses multiple physical outputs.
	 */
	uint8_t subMask;
	/**
	 * Data types/format.
	 */
	clamp_output_type_t type;
	/**
	 * Logical state it should be set to next.
	 */
	bool virtualActive;
	/**
	 * Logical state it is set to now.
	 */
	bool physicalActive;
	/**
	 * If output has been configured to be negated.
	 */
	bool negated;
	/**
	 * If output is a call.
	 */
	bool isCall;
	/**
	 * Index of corresponding Virtual Input.
	 */
	uint8_t callVirtualInputIndex;
	/***
	 * If pulse is suppressed
	 */
	bool pulseSuppressed;
} clamp_output_t;

typedef struct clamp_tag {
	/**
	 * Current IO state.
	 */
	clamp_state_t state;
	/**
	 * Input data.
	 */
	clamp_input_t input;
	/**
	 * Output data.
	 */
	clamp_output_t output;
	/**
	 * Number.
	 */
	uint8_t number;
} clamp_t;


class pins_config
{
	SINGLETON (pins_config)

public:
	
	bool getInputCycled(libCOL_inputBasicFunction_t baseFunc, libCOL_inputSubfunction_t subFunc);
	bool getInputCall(libCOL_inputBasicFunction_t baseFunc);
	bool measureClampInput(int clamp); // Imp for Pin Setting 



	bool getClampHighCurrent(int clamp);
	bool getSevenSegmentState(uint8_t subData, uint8_t subMask);
	int getClampPull(int clamp);


	int getClampOutputPin(int clamp);
	uint8_t getOutputSubFunctionData( libCOL_outputBasicFunction_t baseFunc, libCOL_outputFunctionData_t data, uint8_t subData, libCOL_outputSubFunction_t subFunc, libCOL_outputLift_t lift);
	bool getOutputSpecialFunctionData(libCOL_outputBasicFunction_t baseFunc);
	clamp_output_type_t getOutputType(libCOL_outputBasicFunction_t baseFunc);
	bool getOutputCall(libCOL_outputBasicFunction_t baseFunc);
	bool getOutputClampState(libCOL_outputFunctionData_t data, libCOL_outputBasicFunction_t baseFunc, uint8_t subData, uint8_t subMask, clamp_output_type_t type, libCOL_outputSubFunction_t subFunc);
	bool getOutputFunctionMatch(libCOL_outputBasicFunction_t localBaseFunc, libCOL_outputBasicFunction_t baseFunc);
	bool getOutputLiftMatch(libCOL_outputBasicFunction_t baseFunc, libCOL_outputLift_t localLift, libCOL_outputLift_t lift, libCOL_outputSubFunction_t subFunc);
	bool getOutputFloorMatch(libCOL_outputBasicFunction_t baseFunc, uint8_t localFloor, uint8_t floor, libCOL_outputSubFunction_t subFunc);
	bool getOutputDoorMatch(libCOL_outputBasicFunction_t baseFunc, libCOL_outputDoor_t localDoor, libCOL_outputDoor_t door, uint8_t floor, libCOL_outputSubFunction_t subFunc);
	bool getOutputSubFunctionMatch(libCOL_outputBasicFunction_t baseFunc, libCOL_outputSubFunction_t localSubFunc, libCOL_outputSubFunction_t subFunc);

	void setClampOutput(int clamp, bool state);





};



#endif // PINS_CONFIG_H


