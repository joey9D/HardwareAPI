#include "IOHandler.h"
#include "301/CO_ODinterface.h"
#include "OD.h"
#include "OD_Functions.h"
#include <cstdint>
#include "pins_config.h"



SINGLETON_DEFINE(IOHandler)


static uint16_t libCOL_inputCount = 0;
static const libCOL_input_t* libCOL_inputs = NULL;
static  libCOL_numbered_input_t* libCOL_numberedInputs = NULL;
static libCOL_inputAcknowledge_t libCOL_inputAcknowledge = NULL;
static bool useNumberedInputs = false;

static uint16_t libCOL_outputCount = 0;
static libCOL_numbered_output_t* libCOL_numberedOutputs = NULL;
static bool useNumberedOutputs = false;
IOHandler::libCOL_outputCallback_t IOHandler::libCOL_outputCallback = NULL;
extern OD_EEPROM_t OD_EEPROM; // Real OD_EEPROM with data

// Point our "eepromInstance" to the same OD_EEPROM object
OD_EEPROM_t *eepromInstance = &OD_EEPROM;

extern OD_RAM_t OD_RAM; // declared in some header
OD_RAM_t* ramInstance = &OD_RAM; // ramInstance is a pointer to OD_RAM	


IOHandler::IOHandler() {
    // Constructor implementation (if needed)
}

void IOHandler::initNumberedInputsFromOD(const uint16_t inputCountMax,  libCOL_numbered_input_t* const inputs, libCOL_inputAcknowledge_t acknowledge) {
    uint8_t i, k;
    bool finished = false;

    assert(!((inputCountMax == 0) ^ (inputs == NULL)));

    libCOL_numberedInputs = inputs;
    libCOL_inputAcknowledge = acknowledge;
    useNumberedInputs = true;

    i = 0;
    k = 0;
    while (!finished) {
        if (numberedCopyFromOD(k, &libCOL_numberedInputs[i], eepromInstance->x6100_inputGroup1[k])) {
            i++;
        }
        k++;
        if (k >= OD_CNT_ARR_6100 || i >= inputCountMax) {
            libCOL_inputCount = i;
            finished = true;
        }
    }
}

libCOL_numbered_input_t* IOHandler::getNumberedInputs() {
    return const_cast<libCOL_numbered_input_t*>(libCOL_numberedInputs);
}

uint16_t IOHandler::getInputCount() {
    return libCOL_inputCount;
}

void IOHandler::inputTriggerIndex(const uint16_t inputIndex) {
    assert((libCOL_inputCount >= 0) && (inputIndex < libCOL_inputCount));
    if (useNumberedInputs) {
        inputTrigger(&(libCOL_numberedInputs[inputIndex].input));
    } else {
        inputTrigger(libCOL_inputs + inputIndex);
    }
}

bool IOHandler::inputCompareIndex(const uint16_t inputIndex) {
    assert((libCOL_inputCount >= 0) && (inputIndex < libCOL_inputCount));
    if (useNumberedInputs) {
        return inputCompare(&(libCOL_numberedInputs[inputIndex].input));
    } else {
        return inputCompare(libCOL_inputs + inputIndex);
    }
}

bool IOHandler::inputCompare(const libCOL_input_t* input) {
    assert(input != NULL);
    return compareWithOD(ramInstance->x6010_virtualInputMapping, input);
}

void IOHandler::inputUpdateStatusIndex(const uint16_t inputIndex) {
    assert((libCOL_inputCount >= 0) && (inputIndex < libCOL_inputCount));
    if (useNumberedInputs) {
        copyStatusToOD(eepromInstance->x6100_inputGroup1[libCOL_numberedInputs[inputIndex].number], &(libCOL_numberedInputs[inputIndex].input));
    }
}

void IOHandler::inputTrigger(const libCOL_input_t* input) {
    assert(input != NULL);
    copyToOD(ramInstance->x6010_virtualInputMapping, input);
}

bool IOHandler::inputEnabledIndex(const uint16_t inputIndex) {
    if (useNumberedInputs) {
        return (eepromInstance->x6120_inputParameter1Group1[libCOL_numberedInputs[inputIndex].number] & 0x1);
    } else {
        return (eepromInstance->x6120_inputParameter1Group1[inputIndex] & 0x1);
    }
}


void IOHandler::CANopenInputAcknowledge(const libCOL_input_t* input) 
{
    (void)input;
}


/*Helper Functions*/

static uint8_t inputSize = 0;
static uint8_t outputSize = 0;
static uint16_t outputClampState = 0;
static uint16_t inputClampState = 0;
static uint16_t inputClampData = 0;
static libCOL_outputLift_t liftState;
static clamp_t clamps[NUMBER_OF_CLAMPS];
static virtual_input_t inputs[NUMBER_OF_CLAMPS];
static virtual_output_t outputs[NUMBER_OF_CLAMPS];

static clamp_input_pdo_t inputTransmissionQueue[40];// Array is defined as 40 but what is Optimal size?
static uint8_t inputTransmissionQueueReadIndex = 0;
static uint8_t inputTransmissionQueueWriteIndex = 0;
static bool inputTransmissionQueueOverflow = false;

#define USE_MANUAL_STATE_INDICATION

static bool ioSwitchOutputSet = false;
static bool ioSwitched = false;

static uint32_t outputRefreshLast = 0;
static uint32_t inputTransmissionLast = 0;
static uint32_t ioSwitchCheckLast = 0;

static uint32_t ioSwitchPulseInterval;
static uint32_t ioSwitchPauseInterval;
static uint32_t inputDebounceInterval;
static uint32_t inputTransmissionInterval;
static uint32_t outputRefreshInterval;
static uint32_t cycleInterval;


void IOHandler::loadInputs()
{
    libCOL_numbered_input_t* libColInputs;
    virtual_input_t* input;
    uint8_t inputNumber;

    /* Get virtual inputs */
    libColInputs = getNumberedInputs();
    inputSize = getInputCount();
    for (inputNumber = 0; inputNumber < inputSize; inputNumber++) {
        /* Setup local objects */
        input = &inputs[inputNumber];
        input->number = libColInputs[inputNumber].number;
        input->input = &(libColInputs[inputNumber].input);
    }
}
void IOHandler::loadAdjustments()
{
    /* Set Defaults */
    cycleInterval = 1000;
    liftState.raw = 0;
    

    /* Load Values */
    // inputTransmissionInterval = OD_inputAdjustment[ODA_inputAdjustment_PDOSendingEventTime];
    inputTransmissionInterval = 10;
    // inputDebounceInterval = OD_inputAdjustment[ODA_inputAdjustment_generalDebounceTime];
    inputDebounceInterval = 50;
    // outputRefreshInterval = OD_outputAdjustment[ODA_outputAdjustment_outputRefreshTime];
    outputRefreshInterval = 10;
    ioSwitchPulseInterval = 10;
    ioSwitchPauseInterval = 3;

    //TODO: The time needed to pull down the IO line is too long (> 1 ms) for input voltages above 10V
    if (ioSwitchPauseInterval > 0 && ioSwitchPauseInterval < CLAMP_INPUT_INIT_TIME_MS) {
        ioSwitchPauseInterval = CLAMP_INPUT_INIT_TIME_MS;
        // OD_outputAdjustment[ODA_outputAdjustment_outputPauseTime] = CLAMP_INPUT_INIT_TIME_MS;
    }

}
void IOHandler::getConfiguration() // Used in Stack
{
    loadAdjustments();
    loadInputs();
    loadOutputs();
    //ensureCompatibility();
    loadClamps();
}

void IOHandler::loadClamps() //Used in Stack
{
    clamp_t* clamp, *searchingClamp;
    uint8_t clampNumber, searchingNumber;
    bool clampIsInput;
    bool clampIsOutput;
    virtual_output_t* output;
    virtual_input_t* input;
    uint8_t inputIndex = 0;
    uint8_t outputIndex = 0;

    /* Setup Clamps */
    for (clampNumber = 0; clampNumber < NUMBER_OF_CLAMPS; clampNumber++) {
        clamp = &clamps[clampNumber];
        clamp->number = clampNumber;
        output = &outputs[outputIndex];
        clampIsOutput = false;
        input = &inputs[inputIndex];
        clampIsInput = false;

        /* Check if clamp has been configured as an input */
        if (inputIndex < inputSize && input->number == clampNumber) {
            /* Setup local object */
            clamp->input.virtualInputIndex = inputIndex;
            clamp->input.debounceLast = 0;
            clamp->input.initLast = 0;
            clamp->input.measuredActive = false;
            clamp->input.physicalActive = false;
            clamp->input.virtualActive = false;
            clamp->input.requested = false;
            clamp->input.negated = input->negated;
            clamp->input.cycled = pins_config::instance().getInputCycled(input->input->basicfunction, input->input->subFunction);
            clamp->input.isCall = pins_config::instance().getInputCall(input->input->basicfunction);
            clamp->input.savedCall = false;
            clamp->input.sendActiveNext = false;
            clampIsInput = true;
            inputIndex++;
        }

        /* Check if clamp has been configured as an output */
        if (outputIndex < outputSize && output->number == clampNumber) {
            /* Setup local object */
            clamp->output.virtualOutputIndex = outputIndex;
            clamp->output.subMask = (1 << (output->output->subFunction.raw - 1));
            clamp->output.type = pins_config::instance().getOutputType(output->output->basicfunction);
            clamp->output.virtualActive = false;
            clamp->output.physicalActive = false;
            clamp->output.negated = output->negated;
            clamp->output.isCall = pins_config::instance().getOutputCall(output->output->basicfunction); // Changed from Core code.
            clamp->output.pulseSuppressed = output->pulseSuppressed;
            clampIsOutput = true;
            outputIndex++;
        }

        if (clampIsInput && clampIsOutput) {
            if (ioSwitchPauseInterval == 0) {
                /* IOs only function as outputs */
                clamp->state = clamp_state_io_output;
            } else {
                clamp->state = clamp_state_io_input; //Start as input
            }
        } else if (clampIsInput) {
            clamp->state = clamp_state_input_only;
        } else if (clampIsOutput) {
            clamp->state = clamp_state_output_only;
        } else {
            clamp->state = clamp_state_inactive;
        }
    }

    /* All calls have an input and an output */
    for (clampNumber = 0; clampNumber < NUMBER_OF_CLAMPS; clampNumber++) {
        clamp = &clamps[clampNumber];
        if (clamp_get_defined_input(clamp->state) && clamp->input.isCall) {
            input = &inputs[clamp->input.virtualInputIndex];
            clamp->input.callVirtualOutputFound = false;
            for (searchingNumber = 0; searchingNumber < NUMBER_OF_CLAMPS; searchingNumber++) {
                searchingClamp = &clamps[searchingNumber];
                if (clamp_get_defined_output(clamp->state) && clamp->output.isCall) {
                    output = &outputs[clamp->output.virtualOutputIndex];
                    if (((uint8_t)(input->input->basicfunction) == (uint8_t)(output->output->basicfunction)) &&
                        ((uint8_t)(input->input->subFunction.raw) == (uint8_t)(output->output->subFunction.raw)) &&
                        ((uint8_t)(input->input->lift.raw) == (uint8_t)(output->output->lift.raw)) &&
                        ((uint8_t)(input->input->door.raw) == (uint8_t)(output->output->door.raw)) &&
                        ((uint8_t)(input->input->floor) == (uint8_t)(output->output->floor)))
                    {
                        clamp->input.callVirtualOutputFound = true;
                        clamp->input.callVirtualOutputIndex = clamp->output.virtualOutputIndex;
                        searchingClamp->output.callVirtualInputIndex = clamp->input.virtualInputIndex;
                        break;
                    }
                }
            }
        }
    }
   /* TODO: check this
    static uint8_t outputClampState = 0;
    static uint8_t inputClampState = 0;
    static uint8_t inputClampData = 0;*/
}

void IOHandler::loadOutputs() //Used in Stack
{
    libCOL_numbered_output_t* libColOutputs;
    virtual_output_t* output;
    uint8_t outputNumber;

    /* Get virtual outputs */
    libColOutputs = getNumberedOutputs();
    outputSize = getOutputCount();
    for (outputNumber = 0; outputNumber < outputSize; outputNumber++) {
        /* Setup local objects */
        output = &outputs[outputNumber];
        output->number = libColOutputs[outputNumber].number;
        output->output = &(libColOutputs[outputNumber].output);
        output->lastFunctionData.raw = 0;
        output->lastSubFunctionData = 0;
        output->nextSubFunctionData = pins_config::instance().getOutputSubFunctionData(output->output->basicfunction, output->output->functionData, 0, output->output->subFunction, output->output->lift);
        output->flashState.flashChangeLast = 0;
        output->flashState.enabled = false;
        output->flashState.interval = 0;
        output->flashState.state = false;
        output->defaultFlashState.flashChangeLast = 0;
        output->defaultFlashState.enabled = false;
        output->defaultFlashState.interval = 0;
        output->defaultFlashState.state = false;
        output->pulseState.pulseChangeLast = 0;
        output->pulseState.enabled = false;
        output->pulseState.interval = 0;
        output->pulseState.state = false;
        output->defaultPulseState.pulseChangeLast = 0;
        output->defaultPulseState.enabled = false;
        output->defaultPulseState.interval = 0;
        output->defaultPulseState.state = false;
        if (!pins_config::instance().getOutputSpecialFunctionData(output->output->basicfunction)) {
            if (output->output->functionData.generic.property == flashing) {
                uint16_t interval = getFlashInterval(output->output->functionData);
                output->defaultFlashState.enabled = true;
                output->defaultFlashState.interval = interval;
                output->flashState.enabled = true;
                output->flashState.interval = interval;
            }
        }
    }
}

void IOHandler::setupConfigCallbacks()
{
    // /* Setup Callbacks */
    // libCOL_inputAcknowledge = CANopenInputAcknowledge;
    // libCOL_outputCallback = CANopenOutputCallback;
} 

uint16_t IOHandler::getFlashInterval(libCOL_outputFunctionData_t functionData) // Used in Stack
{
    if (functionData.generic.parameter == flash_ms100) {
        return 100;
    } else if (functionData.generic.parameter == flash_ms133) {
        return 133;
    } else if (functionData.generic.parameter == flash_ms200) {
        return 200;
    } else if (functionData.generic.parameter == flash_ms500) {
        return 500;
    } else if (functionData.generic.parameter == flash_ms666) {
        return 666;
    } else if (functionData.generic.parameter == flash_ms1000) {
        return 1000;
    } else if (functionData.generic.parameter == flash_ms2000) {
        return 2000;
    } else if (functionData.generic.parameter == flash_ms4000) {
        return 4000;
    }
    return 0;
}

uint16_t IOHandler::getPulseInterval(libCOL_outputFunctionData_t functionData) // Used in Stack
{
    if (functionData.generic.parameter == pulse_ms500) {
        return 500;
    } else if (functionData.generic.parameter == pulse_ms1000) {
        return 100;
    } else if (functionData.generic.parameter == pulse_ms1500) {
        return 1500;
    } else if (functionData.generic.parameter == pulse_ms2000) {
        return 2000;
    } else if (functionData.generic.parameter == pulse_ms3000) {
        return 3000;
    } else if (functionData.generic.parameter == pulse_ms5000) {
        return 5000;
    } else if (functionData.generic.parameter == pulse_ms10000) {
        return 10000;
    } else if (functionData.generic.parameter == pulse_ms15000) {
        return 15000;
    }
    return 0;
}

void IOHandler::resetIO() // Used in Stack
{   _hardware = HardwareFactory::Create();
    virtual_output_t* output;
    uint8_t outputIndex;
    clamp_t* clamp;
    uint8_t clampNumber;
    uint8_t sendOnlyActiveInput;

    /* Reset for all physical IO clamps */
    for (clampNumber = 0; clampNumber < NUMBER_OF_CLAMPS; clampNumber++) {
        clamp = &clamps[clampNumber];
        if (clamp_get_defined_io(clamp->state)) {
            if (ioSwitchPauseInterval == 0) {
                /* IOs only function as outputs */
                clamp->state = clamp_state_io_output;
            } else {
                /* Start as input, because we have to send the current input state after a reset */
                clamp->state = clamp_state_io_input;
            }
        }
        if (clamp_get_active_input(clamp->state)) {
            _hardware->setpinDirection(clampNumber, false);
            
            /* Replace vTaskDelay with tick-based delay */
            //uint32_t startTick = _hardware->GetTick();
//            while ((_hardware->GetTick() - startTick) < CLAMP_INPUT_INIT_TIME_MS) {
//                // Optionally place a low-power wait or idle instruction here
//            }
            _hardware->Delay(3);

            //sendOnlyActiveInput = OD_inputAdjustment[ODA_inputAdjustment_inputSelect]; // Deafult is Zero
            sendOnlyActiveInput = 0;

            clamp->input.sendActiveNext = false;
            clamp->input.measuredActive = (_hardware->GPIOPinInput(clampNumber) != clamp->input.negated);
            clamp->input.physicalActive = clamp->input.measuredActive;
            if (sendOnlyActiveInput == 0 || clamp->input.physicalActive) {
                if (!inputTransmissionQueueOverflow) {
                    if (clamp->input.physicalActive || clamp->input.sendActiveNext) {
                        inputTransmissionQueue[inputTransmissionQueueWriteIndex].data.generic.genericState = libCOL_inputFunctionData_t{}.generic.libCOL_genericInputSet;
                    } else {
                        inputTransmissionQueue[inputTransmissionQueueWriteIndex].data.generic.genericState = libCOL_inputFunctionData_t{}.generic.libCOL_genericInputNotSet;
                    }
                    inputTransmissionQueue[inputTransmissionQueueWriteIndex].data.generic.genericResponse = clamp->input.requested;
                    inputTransmissionQueue[inputTransmissionQueueWriteIndex].clampNumber = clampNumber;
                    inputTransmissionQueueWriteIndex++;
                    if (inputTransmissionQueueWriteIndex >= 40) // Array is defined as 40 but what is Optimal size?
                    
                    {
                        inputTransmissionQueueWriteIndex = 0;
                    }
                    inputTransmissionQueueOverflow = (inputTransmissionQueueWriteIndex == inputTransmissionQueueReadIndex);
                }
            }
        }
        /* Set outputs to 0 */
        if (clamp_get_defined_output(clamp->state)) {
            clamp->output.physicalActive = false;
            output = &outputs[clamp->output.virtualOutputIndex];
            output->output->functionData.generic.status = 0;
#ifdef USE_MANUAL_STATE_INDICATION
            outputUpdateStatusIndexManual(clamp->output.virtualOutputIndex, false);
#endif
#ifndef USE_MANUAL_STATE_INDICATION
            outputUpdateStatusIndexManual(clamp->output.virtualOutputIndex);
#endif
            if (clamp_get_active_output(clamp->state)) {
                _hardware->setpinDirection(clampNumber, true);
                _hardware->GPIOPinOutput(clampNumber, ((clamp->output.physicalActive) != clamp->output.negated));
            }
        }
    }
    /* Reset virtual output objects */
    for (outputIndex = 0; outputIndex < outputSize; outputIndex++) {
        output = &outputs[outputIndex];
        output->lastFunctionData.raw = 0;
        output->lastSubFunctionData = 0;
        output->nextSubFunctionData = 0;
        output->flashState.enabled = output->defaultFlashState.enabled;
        output->flashState.interval = output->defaultFlashState.interval;
        output->flashState.flashChangeLast = 0;
        output->flashState.state = false;
        output->pulseState.enabled = output->defaultPulseState.enabled;
        output->pulseState.interval = output->defaultPulseState.interval;
        output->pulseState.pulseChangeLast = 0;
        output->pulseState.state = false;
    }
    ioSwitchCheckLast = 0;
#if RECORD_INPUT_TIMELINE
    inputEventTimelineLast = 0;
    inputEventTimelineReset = true;
#endif
}

void IOHandler::readInputs(uint32_t timerCount1ms) // Used in Stack
{   _hardware = HardwareFactory::Create();
    uint32_t timeSinceLastDebounce;
    clamp_t* clamp;
    uint8_t clampNumber;
    bool inputChanged;

    inputChanged = false;
    for (clampNumber = 0; clampNumber < NUMBER_OF_CLAMPS; clampNumber++) {
        clamp = &clamps[clampNumber];
        /* Check if clamp is currently an input */
        if (clamp_get_active_input(clamp->state)) {
            bool in;
            bool sendInput = false;

            /* Check that input had time to settle */
            if ((timerCount1ms - clamp->input.initLast) >= CLAMP_INPUT_INIT_TIME_MS) {
                /* Measure */
                in = (_hardware->GPIOPinInput(clampNumber) != clamp->input.negated);
				if(in == clamp->input.physicalActive)
				{/* reset timer if pin value is the same */
					clamp->input.debounceLast = timerCount1ms;
				}
                /* Check if input debounced */
                timeSinceLastDebounce = (timerCount1ms - clamp->input.debounceLast);
                if (timeSinceLastDebounce >= inputDebounceInterval) {
                    /* Check if input changed or input has been requested */
                    if (in != clamp->input.physicalActive) {
                        /* Note input */
                        clamp->input.physicalActive = in;
                        /* Prepare data for register 2010 */
                        inputChanged = true;
                        if (clamp->input.physicalActive) {
                            inputClampData |= (0x1 << clampNumber);
                        } else {
                            inputClampData &= ~(0x1 << clampNumber);
                        }
#if RECORD_INPUT_TIMELINE
                        /* Count input event */
                        inputEventCounter[clampNumber]++;
                        inputEventTimeline[inputEventTimelinePointer] |= 1 << clampNumber;
#endif
                        /* Check if input is enabled */
                        if (inputEnabledIndex(clamp->input.virtualInputIndex)) {
                            /* Start debounce */
                            clamp->input.debounceLast = timerCount1ms;
                            /* Send input */
                            sendInput = true; //TODO: 6140 Limitation/Sending
                        }
                    }
                }
                /* Check if cyclic broadcast and time to send */
                if (clamp->input.cycled) {
                    if ((timerCount1ms - clamp->input.cycleLast) > cycleInterval) {
                        /* Start cyclic broadcast timer */
                        clamp->input.cycleLast = timerCount1ms;
                        /* Send input */
                        sendInput = true;
                    }
                }
                /* Check if we need to transmit PDO */
                if ((clamp->input.requested || sendInput) && inputEnabledIndex(clamp->input.virtualInputIndex)) {
                    /* Check if outgoing message queue still has free space */
                    if (!inputTransmissionQueueOverflow) {
                        /* Prepare outgoing message */
                        if (clamp->input.physicalActive || clamp->input.sendActiveNext) {
                            inputTransmissionQueue[inputTransmissionQueueWriteIndex].data.generic.genericState = libCOL_inputFunctionData_t{}.generic.libCOL_genericInputSet;
                        } else {
                            inputTransmissionQueue[inputTransmissionQueueWriteIndex].data.generic.genericState = libCOL_inputFunctionData_t{}.generic.libCOL_genericInputNotSet;
                        }
                        inputTransmissionQueue[inputTransmissionQueueWriteIndex].data.generic.genericResponse = clamp->input.requested;
                        inputTransmissionQueue[inputTransmissionQueueWriteIndex].clampNumber = clampNumber;
                        inputTransmissionQueueWriteIndex++;
                        if (inputTransmissionQueueWriteIndex >= 40) // Array is defined as 40 but what is Optimal size?{
                            inputTransmissionQueueWriteIndex = 0;
                        }
                        inputTransmissionQueueOverflow = (inputTransmissionQueueWriteIndex == inputTransmissionQueueReadIndex);
                        clamp->input.requested  = false;
                        clamp->input.sendActiveNext = false;
                    }
                }
                /* Prepare data for register 2010 */
                if (in != clamp->input.measuredActive) {
                    inputChanged = true;
                    clamp->input.measuredActive = in;
                    if (clamp->input.measuredActive) {
                        inputClampState |= (0x1 << clampNumber);
                    } else {
                        inputClampState &= ~(0x1 << clampNumber);
                    }
                }
            }
        }
    
    /* Update register 0x2010 */
    /* Update register 0x2010 */
    if (inputChanged)
    {
        ramInstance->x2010_inputClamp[0] = inputClampState;
        ramInstance->x2010_inputClamp[1] = inputClampData;
    }
}


void IOHandler::checkIOSwitch(uint32_t timerCount1ms) // Used in Stack
{   _hardware = HardwareFactory::Create();
    uint32_t timeDelta;
    clamp_t* clamp;
    uint8_t clampNumber;

    /* Reset IOSwitch flag */
    ioSwitched = false;
    /* Time since last check */
    timeDelta = timerCount1ms - ioSwitchCheckLast;
    /* Check if IO pulse is enabled and if the interval for an IO switch has timed out */
    if ((ioSwitchPauseInterval > 0) &&
        ((ioSwitchOutputSet && timeDelta >= ioSwitchPulseInterval) ||
        (!ioSwitchOutputSet && timeDelta >= ioSwitchPauseInterval)))
    {
        /* Switch IOs*/
        ioSwitchOutputSet = !ioSwitchOutputSet;
        for (clampNumber = 0; clampNumber < NUMBER_OF_CLAMPS; clampNumber++) {
            clamp = &clamps[clampNumber];
            /* Check if Clamp is IO */
            if (clamp_get_defined_io(clamp->state)) {
                if (ioSwitchOutputSet) {
                    /* IOs were Inputs, change to Outputs */
                    clamp->state = clamp_state_io_output;
                } else if (!clamp->output.pulseSuppressed) {
                    /* IOs were Outputs, change to Inputs */
                    clamp->state = clamp_state_io_input;
                    /* Set physical input direction
                     * RSC: This will prevent the clamp to operate as a call which is an input & output as well.
                     *  */
                    _hardware->setpinDirection(clampNumber, false);
                    /* Set timer to wait for the inputs to settle */
                    clamp->input.initLast = timerCount1ms;
                }
            }
        }
        /* Setup counter for next switch */
        ioSwitchCheckLast = timerCount1ms;
        /* Notify Input and Output function to switch pin directions */
        ioSwitched = true;
    }
}


void IOHandler::checkOutputRefresh(uint32_t timerCount1ms) // Used in Stack
{
    uint32_t timeDelta;
    virtual_output_t* output;
    clamp_t* clamp;
    uint8_t outputIndex;
    uint8_t clampNumber;
    bool outputSet;
    bool outputChanged;
    bool outputFlashChanged;
    bool outputPulseStarted;
    bool outputPulseEnded;
    bool adoptChanges;
    _hardware = HardwareFactory::Create();
    /* Check if outputs need to be refreshed */
    timeDelta = timerCount1ms - outputRefreshLast;
    outputSet = false;
    if (timeDelta >= outputRefreshInterval) {
        /* Check state of virtual outputs */
        for (outputIndex = 0; outputIndex < outputSize; outputIndex++) {
            output = &outputs[outputIndex];
            /* Check if function data changed:
             * Single output uses function data,
             * multiple output uses subfunction data */
            outputChanged = ((output->output->functionData.raw != output->lastFunctionData.raw) || (output->nextSubFunctionData != output->lastSubFunctionData));
            /* Check if flash interval timed out if enabled */
            outputFlashChanged = (output->output->functionData.generic.status && output->flashState.enabled && ((timerCount1ms - output->flashState.flashChangeLast) >= output->flashState.interval));
            /* Check if pulse started */
            outputPulseStarted = (outputChanged && output->output->functionData.generic.status && output->pulseState.enabled);
            /* Check if pulse interval timed out if enabled */
            outputPulseEnded = (output->output->functionData.generic.status && output->pulseState.enabled && output->pulseState.state && ((timerCount1ms - output->pulseState.pulseChangeLast) >= output->pulseState.interval));
            /* *
             * Check if an output change occured,
             * the flash state changed,
             * IO Clamps have switched to output or
             * an output change was delayed by the move timer
             * */
            if (outputChanged || outputFlashChanged || outputPulseStarted || outputPulseEnded || (ioSwitched && ioSwitchOutputSet)) {
                /* Check flash */
                if (outputFlashChanged) {
                    output->flashState.state = !output->flashState.state;
                    output->flashState.flashChangeLast = timerCount1ms;
                }
                if (outputPulseStarted) {
                    output->pulseState.state = true;
                    output->pulseState.pulseChangeLast = timerCount1ms;
                }
                if (outputPulseEnded) {
                    output->pulseState.state = false;
                }
                /* Update corresponding clamps */
                for (clampNumber = 0; clampNumber < NUMBER_OF_CLAMPS; clampNumber++) {
                    clamp = &clamps[clampNumber];
                    /* Check if clamp is defined as an output */
                    if (clamp_get_defined_output(clamp->state)) {
                        /* Check if clamp corresponds to virtual output */
                        if (clamp->output.virtualOutputIndex == outputIndex) {
                            /* Adopt changes in local clamp object */
                            if (outputChanged) {
                                clamp->output.virtualActive = pins_config::instance().getOutputClampState(output->output->functionData, output->output->basicfunction, output->nextSubFunctionData, clamp->output.subMask, clamp->output.type, output->output->subFunction);
                                clamp->output.physicalActive = clamp->output.virtualActive;
#ifdef USE_MANUAL_STATE_INDICATION
                                outputUpdateStatusIndexManual(outputIndex, clamp->output.virtualActive);
#endif
                            }
                            /* Switch to output */
                            if ((ioSwitched && ioSwitchOutputSet) && clamp_get_defined_io(clamp->state)) {
                                /* set physical output direction */
                                _hardware->setpinDirection(clampNumber, true);;
                            }
                            /* Set corresponding physical pin */
                            if (clamp_get_active_output(clamp->state)) {
                                /* Set physical pins */
                                //TODO: should we show the negated in outputClampState?
                                if (output->flashState.enabled) {
                                    //TODO: should we show the flashing in outputClampState?
                                    _hardware->GPIOPinOutput(clampNumber, ((clamp->output.physicalActive && output->flashState.state) != clamp->output.negated));
                                } else if (output->pulseState.enabled) {
                                    _hardware->GPIOPinOutput(clampNumber, ((clamp->output.physicalActive && output->pulseState.state) != clamp->output.negated));
                                } else {
                                    _hardware->GPIOPinOutput(clampNumber, ((clamp->output.physicalActive) != clamp->output.negated));
                                }
                                outputSet = true;
                                if (clamp->output.physicalActive) {
                                    outputClampState |= (0x1 << clampNumber);
                                } else {
                                    outputClampState &= ~(0x1 << clampNumber);
                                }
                            }
                        }
                    }
                }
                output->lastSubFunctionData = output->nextSubFunctionData;
                output->lastFunctionData = output->output->functionData;
            }
        }
        /* Setup counter for next refresh */
        outputRefreshLast = timerCount1ms;
    } else if (ioSwitched && ioSwitchOutputSet) {
        for (clampNumber = 0; clampNumber < NUMBER_OF_CLAMPS; clampNumber++) {
            clamp = &clamps[clampNumber];
            if (clamp_get_defined_io(clamp->state)) {
                output = &outputs[clamp->output.virtualOutputIndex];
                /* set physical outputs */
                _hardware->setpinDirection(clampNumber, true);
                if (output->flashState.enabled) {
                    //TODO: should we show the flashing in outputClampState?
                    _hardware->GPIOPinOutput(clampNumber, ((clamp->output.physicalActive && output->flashState.state) != clamp->output.negated));
                } else if (output->pulseState.enabled) {
                    _hardware->GPIOPinOutput(clampNumber, ((clamp->output.physicalActive && output->pulseState.state) != clamp->output.negated));
                } else {
                    _hardware->GPIOPinOutput(clampNumber, ((clamp->output.physicalActive) != clamp->output.negated));
                }
                outputSet = true;
                if (clamp->output.physicalActive) {
                    outputClampState |= (0x1 << clampNumber);
                } else {
                    outputClampState &= ~(0x1 << clampNumber);
                }
            }
        }
    }
    /* Update register 2020 */
    if (outputSet) {
        ramInstance->x2011_outputClamp[0] = outputClampState;
    }
}

void IOHandler::checkInputTransmission(uint32_t timerCount1ms) //Used in Stack
{
    bool inputTransmissionReady;
    clamp_input_pdo_t pdo;
    clamp_t* clamp;
    libCOL_input_t* input;

    inputTransmissionReady = (timerCount1ms - inputTransmissionLast) >= inputTransmissionInterval;
    if (inputTransmissionReady && (inputTransmissionQueueOverflow || inputTransmissionQueueReadIndex != inputTransmissionQueueWriteIndex)) {
        pdo = inputTransmissionQueue[inputTransmissionQueueReadIndex];
        inputTransmissionQueueReadIndex++;
        if (inputTransmissionQueueReadIndex >= 40) // Array is defined as 40 but what is Optimal size?{
            inputTransmissionQueueReadIndex = 0;
        }
        inputTransmissionQueueOverflow = false;
        assert(pdo.clampNumber < NUMBER_OF_CLAMPS);
        clamp = &clamps[pdo.clampNumber];
        assert(clamp_get_defined_input(clamp->state));
        assert(clamp->input.virtualInputIndex < inputSize);
        input = inputs[clamp->input.virtualInputIndex].input;
        input->functionData = pdo.data;
        inputUpdateStatusIndex(clamp->input.virtualInputIndex); //put the input function data into the 0x6100 object
        if (inputCompareIndex(clamp->input.virtualInputIndex)) {
            _canOpenNodeParameter.canOpenStack->TPDO[0].sendRequest = 1;
        } else {
            inputTriggerIndex(clamp->input.virtualInputIndex);
        }
        //CO->TPDO[0
        clamp->input.virtualActive = (pdo.data.generic.genericState == libCOL_inputFunctionData_t{}.generic.libCOL_genericInputSet);
        inputTransmissionLast = timerCount1ms;
    }


/*OD Output Functions*/
void IOHandler::initNumberedOutputsFromOD(const uint16_t outputCountMax,  libCOL_numbered_output_t* const outputs, libCOL_outputCallback_t callback) {
    //uint8_t flags[1] = { CO_ODFL_RPDO_WRITTEN };
    uint16_t i, k;
    bool finished = false;

    assert(!((outputCountMax == 0) ^ (outputs == NULL)));

    libCOL_numberedOutputs = outputs;
    libCOL_outputCallback = callback;
    useNumberedOutputs = true;

    i = 0;
    k = 0;
    while (!finished) {
        if (numberedCopyFromOD(k, &libCOL_numberedOutputs[i], eepromInstance->x6100_inputGroup1[k])) {
            i++;
        }
        k++;
        if (k >= OD_CNT_ARR_6200|| i >= outputCountMax) {
            libCOL_outputCount = i;
            finished = true;
        }
    }

    OD_entry_t *odEntry = OD_find(OD, 0x6011);
    assert(odEntry != NULL);

    static OD_extension_t odExt;
    odExt.object = NULL;
    odExt.read = NULL;
    odExt.write = outputPDOCallback;

    OD_extension_init(odEntry, &odExt);
}

libCOL_numbered_output_t* IOHandler::getNumberedOutputs() {
    return const_cast<libCOL_numbered_output_t*>(libCOL_numberedOutputs);
}

uint16_t IOHandler::getOutputCount() {
    return libCOL_outputCount;
}

void IOHandler::outputUpdateStatusIndexManual(const uint16_t outputIndex, bool indication) {
    assert((libCOL_outputCount > 0) && (outputIndex < libCOL_outputCount));
    if (useNumberedOutputs) {
        setStatusInOD(eepromInstance->x6200_outputGroup1[libCOL_numberedOutputs[outputIndex].number], &(libCOL_numberedOutputs[outputIndex].output), indication);
    }
}

ODR_t IOHandler::outputPDOCallback(OD_stream_t *stream, const void *buf, OD_size_t count, OD_size_t *countWritten) {
    libCOL_output_t output;
    const virtualIOMapping_data* mapped = (const virtualIOMapping_data*)stream->object;

    if ((stream->subIndex == 0) || (mapped == NULL) || (libCOL_outputCallback == NULL)) {
        return ODR_DEV_INCOMPAT;
    }

    output.basicfunction = (libCOL_outputBasicFunction_t)mapped->basicFunction;
    output.subFunction.raw = mapped->subFunction;
    output.lift.raw = mapped->lift;
    output.floor = mapped->floor;
    output.door.raw = mapped->door;
    output.functionData.raw = mapped->functionData;

    libCOL_outputCallback(&output);

    if (countWritten != NULL) {
        *countWritten = count;
    }

    return ODR_OK;
}

bool IOHandler::outputEnabledIndex(const uint16_t outputIndex) {
    return (eepromInstance->x6220_outputParameter1Group1[outputIndex] & 0x1);

}

void IOHandler::libCOL_process() {
//   static uint32_t previousTimerCountMs = 0;
//   uint16_t timerDiffMs;
//   bool sync;
//   CO_NMT_reset_cmd_t reset;
//
//   if (timerCount1ms < previousTimerCountMs) {
//       timerDiffMs = 1;
//   } else {
//       timerDiffMs = timerCount1ms - previousTimerCountMs;
//   }
//   previousTimerCountMs = timerCount1ms;
//
//   // Process CANopen stack
//   reset = CO_process(_canOpenNodeParameter.canOpenStack, false, canopenNodeSTM32->timerCall_in_us, NULL);
//   sync = CO_process_SYNC(_canOpenNodeParameter.canOpenStack, canopenNodeSTM32->timerCall_in_us, NULL);
//   CO_process_RPDO(_canOpenNodeParameter.canOpenStack, sync, canopenNodeSTM32->timerCall_in_us, NULL);
//   CO_process_TPDO(_canOpenNodeParameter.canOpenStack, sync, canopenNodeSTM32->timerCall_in_us, NULL);

//    // if (libCOL_nmtResetCallback == NULL)
//    //     return;
//
//    // switch (reset) {
//    // case CO_RESET_COMM:
//    //     libCOL_nmtResetCallback(libCOL_resetCommunication);
//    //     break;
//    // case CO_RESET_APP:
//    //     libCOL_nmtResetCallback(libCOL_resetApplication);
//    //     break;
//    // default:
//    //     break;
//    // }
}

static uint32_t lastProcess = 0xFFFFFFFF;
void IOHandler::ProcessIO()

{  uint32_t timerCount1ms {canopenNodeSTM32->timerCall_in_us};

    if (timerCount1ms == lastProcess) {
        return;
    }
    lastProcess = timerCount1ms;
#if RECORD_INPUT_TIMELINE
    advanceInputEventsTimeline(timerCount1ms);
#endif
    readInputs(timerCount1ms);
    canopen_app_interrupt();
    checkIOSwitch(timerCount1ms);
    canopen_app_interrupt();
    checkOutputRefresh(timerCount1ms);
    canopen_app_interrupt();
    checkInputTransmission(timerCount1ms);
    canopen_app_interrupt();
}




    


void IOHandler::CANopenOutputCallback(const libCOL_output_t* output) 
{
    uint8_t outputIndex;
    virtual_output_t* localOutput;
    clamp_t* clamp;
    uint8_t clampNumber;
    uint8_t baseFunc;

    /* Check if it's a special call controller command or a regular output */
    if (output->basicfunction == libCOL_outputBasicFunction_t::libCOL_of_callControllerCommand) {
        if (output->subFunction.callControllerCommand == libCOL_outputSubFunction_t::libCOL_requestAll ||
            output->subFunction.callControllerCommand == libCOL_outputSubFunction_t::libCOL_requestHallCalls ||
            output->subFunction.callControllerCommand == libCOL_outputSubFunction_t::libCOL_requestSpecialInputs ||
            output->subFunction.callControllerCommand == libCOL_outputSubFunction_t::libCOL_requestCallsAck ||
			output->subFunction.callControllerCommand == libCOL_outputSubFunction_t::libCOL_requestAllInputsExceptCalls)
        {
            /* Requesting broadcast from a range of inputs */
            for (clampNumber = 0; clampNumber < NUMBER_OF_CLAMPS; clampNumber++) {
                clamp = &clamps[clampNumber];
                /* Check if clamp is defined as an input */
                if (clamp_get_defined_input(clamp->state)) {
                    baseFunc = inputs[clamp->input.virtualInputIndex].input->basicfunction;
                    if (output->subFunction.callControllerCommand == libCOL_outputSubFunction_t::libCOL_requestAll) {
                        /* Requesting all inputs */
                        clamp->input.requested = true;
                    } else if (output->subFunction.callControllerCommand == libCOL_outputSubFunction_t::libCOL_requestHallCalls) {
                        /* Requesting active hall calls */
                        if (baseFunc == libCOL_if_hallStandard || baseFunc == libCOL_if_hallLowPriority || baseFunc == libCOL_if_hallHighPriority) {
                            if (clamp->input.callVirtualOutputFound && pins_config::instance().getOutputClampState(outputs[clamp->input.callVirtualOutputIndex].output->functionData, outputs[clamp->input.callVirtualOutputIndex].output->basicfunction, outputs[clamp->input.callVirtualOutputIndex].nextSubFunctionData, clamp->output.subMask, clamp->output.type, outputs[clamp->input.callVirtualOutputIndex].output->subFunction)) {
                                clamp->input.requested = true;
                                clamp->input.sendActiveNext = true; //We need to resend call
                            }
                        }
                    } else if (output->subFunction.callControllerCommand == libCOL_outputSubFunction_t::libCOL_requestSpecialInputs) {
                        /* Requesting special inputs */
                        if (baseFunc == libCOL_if_specialFunction || baseFunc == libCOL_if_fireDetector) {
                            clamp->input.requested = true;
                        }
                    } else if (output->subFunction.callControllerCommand == libCOL_outputSubFunction_t::libCOL_requestCallsAck) {
                        /* Requesting active calls */
                        //TODO: Check is this is correct
                        if (clamp->input.isCall && clamp->input.measuredActive) {
                            clamp->input.requested = true;
                        } else if (baseFunc == libCOL_if_specialFunction || baseFunc == libCOL_if_fireDetector) {
                            clamp->input.requested = true;
                        } else if (clamp->input.savedCall) {
                            //TODO: Do this maybe: clamp->input.savedCall = false;
                            clamp->input.requested = true;
                            clamp->input.sendActiveNext = true; //We need to resend call
                        }

                    } else if (output->subFunction.callControllerCommand == libCOL_outputSubFunction_t::libCOL_requestAllInputsExceptCalls) {
                            /* Requesting All Inputs Except Calls */
                    	if (clamp->input.isCall  == false) {
                        	clamp->input.requested = true;
                    	}

                    }
                }
            }

        }
    } else {
        /* Check if the output maps to one of our configured outputs */
        for (outputIndex = 0; outputIndex <  outputSize; outputIndex++) {
            localOutput = &outputs[outputIndex];
            if (pins_config::instance().getOutputFunctionMatch(localOutput->output->basicfunction, output->basicfunction) &&
                pins_config::instance().getOutputLiftMatch(localOutput->output->basicfunction, localOutput->output->lift, output->lift, output->subFunction) &&
                pins_config::instance().getOutputFloorMatch(localOutput->output->basicfunction, localOutput->output->floor, output->floor, output->subFunction) &&
                pins_config::instance().getOutputDoorMatch(localOutput->output->basicfunction, localOutput->output->door, output->door, output->floor, output->subFunction) &&
                pins_config::instance().getOutputSubFunctionMatch(localOutput->output->basicfunction, output->subFunction, localOutput->output->subFunction))
            {
                /* Check if the output has been enabled in the configuration */
                if (IOHandler::instance().outputEnabledIndex(outputIndex)) {
                    /* Check if it's a flashing output */
                    if (output->functionData.generic.property == flashing) {
                        uint16_t interval = getFlashInterval(output->functionData);
                        if (!localOutput->flashState.enabled) {
                            localOutput->flashState.flashChangeLast = 0;
                            localOutput->flashState.state = false;
                        }
                        localOutput->flashState.interval = interval;
                        localOutput->flashState.enabled = true;
                    } else if (output->functionData.generic.property == pulsed) {
                        uint16_t interval = getPulseInterval(output->functionData);
                        if (!localOutput->pulseState.enabled) {
                            localOutput->pulseState.pulseChangeLast = 0;
                            localOutput->pulseState.state = false;
                        }
                        localOutput->pulseState.interval = interval;
                        localOutput->pulseState.enabled = true;
                    } else if (output->functionData.generic.property == continuously) {
                        localOutput->flashState.enabled = false;
                        localOutput->flashState.flashChangeLast = 0;
                        localOutput->pulseState.enabled = false;
                        localOutput->pulseState.pulseChangeLast = 0;
                    } else if (output->functionData.generic.property == noAction) {
                        //Revert to our configuration
                        if (localOutput->defaultFlashState.enabled) {
                            if (!localOutput->flashState.enabled) {
                                localOutput->flashState.flashChangeLast = 0;
                                localOutput->flashState.state = false;
                            }
                            localOutput->flashState.interval = localOutput->defaultFlashState.interval;
                            localOutput->flashState.enabled = true;
                        } else if (localOutput->defaultPulseState.enabled) {
                            if (!localOutput->pulseState.enabled) {
                                localOutput->pulseState.pulseChangeLast = 0;
                                localOutput->pulseState.state = false;
                            }
                            localOutput->pulseState.interval = localOutput->defaultPulseState.interval;
                            localOutput->pulseState.enabled = true;
                        } else {
                            localOutput->flashState.enabled = false;
                            localOutput->flashState.flashChangeLast = 0;
                        }
                    }

                    /* Adopt mapped data */
                    if (output->basicfunction == libCOL_of_specialIndication &&
                            output->subFunction.specialIndication == libCOL_outputSubFunction_t::libCOL_specialIndication_clear) {
                        //clear special indication
                        localOutput->output->functionData.generic.status = 0;
                        localOutput->nextSubFunctionData = 0;
#ifndef USE_MANUAL_STATE_INDICATION
                        libCOL_outputUpdateStatusIndex(outputIndex);
#endif
                    } else {
                        if (output->functionData.raw & 0x01) {
                            localOutput->output->functionData.raw |= 0x01;
                        } else {
                            localOutput->output->functionData.raw &= ~0x01;
                        }
#ifndef USE_MANUAL_STATE_INDICATION
                        libCOL_outputUpdateStatusIndex(outputIndex);
#endif
                        //localOutput->output->functionData = output->functionData;
                        localOutput->nextSubFunctionData = pins_config::instance().getOutputSubFunctionData(localOutput->output->basicfunction, output->functionData, localOutput->nextSubFunctionData, output->subFunction, output->lift);
                    }
                    //TODO: write into 2020
                }
                //Do this for all configured outputs
            }
        }
    }
}




/*Input Function Definitions*/



// MAIN FUNCTIONS DEFINITIONS

static libCOL_numbered_input_t virtualInputs[NUMBER_OF_CLAMPS] = {
    /* empty input */
    {
        {
            {}, /* basicfunction */
            { 0 }, /* subfunction */
            { libCOL_lift1 },
            0, /* floor */
            { libCOL_door1 },
            { 0 }, /* inputFunction */
        },
        0
    }
};
static libCOL_numbered_output_t virtualOutputs[NUMBER_OF_CLAMPS] = {
    /* empty output */
    {
        {
            { },
            { 0 }, /* subfunction */
            { libCOL_lift1 },
            0, /* floor */
            { libCOL_door1 },
            { 0 }, /* outputFunction */
        },
        0
    }
};


void IOHandler::initializeIO() {
initNumberedInputsFromOD(NUMBER_OF_CLAMPS, virtualInputs, CANopenInputAcknowledge);
initNumberedOutputsFromOD(NUMBER_OF_CLAMPS, virtualOutputs, CANopenOutputCallback);
//_hardware->GreenLed();
// //Load data from object dictionary into local application objects
getConfiguration();

// //Setup callbacks for configuration changes
//setupConfigCallbacks();
// //Get input states and set outputs to default 0
resetIO();


}

// void IOHandler::initLEDs()
// {   _hardware = HardwareFactory::Create();
//     bool state = (_canOpenNodeParameter.outStatusLEDGreen != 0); // Convert to bool

//     if (_oldState != state) // Only update if the state changes
//     {
//         _oldState = state; // Update stored state

//         _hardware->GreenLed(state);  // Set LED based on new state
//     }

// }

// void IOHandler::initLEDs() {
//     _hardware = HardwareFactory::Create();
//     bool state =false;
//     if (_canOpenNodeParameter.outStatusLEDGreen != 0) // Convert to bool
//         {state = true;}
//     if (_oldState != state) { // Only update if the state changes
//         _oldState = state; // Update stored state
//         _hardware->GPIO_Write(LD2_GPIO_Port, LD2_Pin, state ? GPIO_HIGH : GPIO_LOW); // Set LED based on new state
//     }
    
// }

void IOHandler::initLEDs() {
    _hardware = HardwareFactory::Create();
    bool state = CANopenNode::instance().isLEDGreenOn(); // Directly get LED state

    if (_oldState != state) {
        _oldState = state;
        _hardware->GPIO_Write(LD2_GPIO_Port, LD2_Pin, state ? GPIO_HIGH : GPIO_LOW);
    }
}




//static uint16_t libCOL_inputCount = 0;
//static const libCOL_input_t* libCOL_inputs = NULL;
//static const libCOL_numbered_input_t* libCOL_numberedInputs = NULL;
//static libCOL_inputAcknowledge_t libCOL_inputAcknowledge = NULL;
//static bool useNumberedInputs = false;
//
//
//void libCOL_numberedInputInitFromOD( // Used in Stack
//	const uint16_t inputCountMax,
//	const libCOL_numbered_input_t* inputs,
//	libCOL_inputAcknowledge_t acknowledge)
//{
//uint16_t i, k;
//bool finished = false;
//
///* either both are 0 or none of them is */
//assert(!((inputCountMax == 0) ^ (inputs == NULL)));
//
//libCOL_numberedInputs = inputs;
//libCOL_inputAcknowledge = acknowledge;
//useNumberedInputs = true;
//
//i = 0;
//k = 0;
//while (!finished) {
//	if (numberedCopyFromOD(k, &libCOL_numberedInputs[i], &OD_ENTRY_H6100_inputGroup1[k])) // Copy from OD to numbered input structure
//	{
//		i++;
//	}
//	k++;
//	if (k >= OD_CNT_ARR_6100 || i >= inputCountMax) {
//		libCOL_inputCount = i;
//		finished = true;
//	}
//}
//}
//
//libCOL_numbered_input_t* libCOL_getNumberedInputs() // Used in Stack
//{
//    return libCOL_numberedInputs;
//}
//
//
//uint16_t libCOL_getInputCount() // Used in Stack
//{
//    return libCOL_inputCount;
//}
//
//
//void libCOL_inputTriggerIndex(const uint16_t inputIndex) // Used in Stack
//{
//    assert((libCOL_inputCount > 0) && (inputIndex < libCOL_inputCount));
//    if (useNumberedInputs) {
//        libCOL_inputTrigger(&(libCOL_numberedInputs[inputIndex].input));
//    } else {
//        libCOL_inputTrigger(libCOL_inputs + inputIndex);
//    }
//}
//
//bool libCOL_inputCompareIndex(const uint16_t inputIndex) // Used in Stack
//{
//    assert((libCOL_inputCount > 0) && (inputIndex < libCOL_inputCount));
//    if (useNumberedInputs) {
//        return libCOL_inputCompare(&(libCOL_numberedInputs[inputIndex].input));
//    } else {
//        return libCOL_inputCompare(libCOL_inputs + inputIndex);
//    }
//}
//
//bool libCOL_inputCompare(const libCOL_input_t* input) // nOT USED in Stack
//{
//    assert(input != NULL);
//    return compareWithOD(&OD_virtualInputMapping, input);
//}
//
//void libCOL_inputUpdateStatusIndex(const uint16_t inputIndex) // Used in Stack
//{
//    assert((libCOL_inputCount > 0) && (inputIndex < libCOL_inputCount));
//    if (useNumberedInputs) {
//        copyStatusToOD(&OD_inputGroup1[libCOL_numberedInputs[inputIndex].number], &(libCOL_numberedInputs[inputIndex].input));
//    }
//}
//
//void libCOL_inputTrigger(const libCOL_input_t* input) // Used in Stack
//{
//    assert(input != NULL);
//    copyToOD(&OD_virtualInputMapping, input);
//}
//
//bool libCOL_inputEnabledIndex(const uint16_t inputIndex) // Used in Stack
//{
//    if (useNumberedInputs) {
//        return (OD_inputParameter1Group1[libCOL_numberedInputs[inputIndex].number] & 0x1);
//    } else {
//        return (OD_inputParameter1Group1[inputIndex] & 0x1);
//    }
//}
//
//
///*Output Function Definitions*/
//
//static libCOL_outputCallback_t libCOL_outputCallback = NULL;
//static uint16_t libCOL_outputCount = 0;
//static const libCOL_output_t* libCOL_outputs = NULL;
//static const libCOL_numbered_output_t* libCOL_numberedOutputs = NULL;
//static bool useNumberedOutputs = false;
//
//void libCOL_numberedOutputInitFromOD( // Used in Stack
//	const uint16_t outputCountMax,
//	const libCOL_numbered_output_t* outputs,
//	libCOL_outputCallback_t callback/*,
//   const uint8_t maxFloors,
//	const bool vocalUserMessagesEnabled[VOCALUSERMESSAGES_MAX]*/)
//{
//uint8_t flags[1] = { CO_ODFL_RPDO_WRITTEN };
//uint16_t i, k;
//bool finished = false;
//
///* either both are 0 or none of them is */
//assert(!((outputCountMax == 0) ^ (outputs == NULL)));
//
//libCOL_numberedOutputs = outputs;
//libCOL_outputCallback = callback;
//useNumberedOutputs = true;
//
//i = 0;
//k = 0;
//while (!finished) {
//	if (numberedCopyFromOD(k, &libCOL_numberedOutputs[i], &OD_outputGroup1[k])) {
//		i++;
//	}
//	k++;
//	if (k >= ODL_outputGroup1_arrayLength || i >= outputCountMax) {
//		libCOL_outputCount = i;
//		finished = true;
//	}
//}
//
//// CO_LOCK_OD();
//// CO_OD_configure(
//// 		CO->SDO[0],
//// 		0x6011,
//// 		libCOL_outputPDOCallback,
//// 		NULL,
//// 		NULL,
//// 		0);
//// CO_UNLOCK_OD();
//// Initialize the OD extension
//
//// Find the OD entry
//OD_entry_t *odEntry = OD_find(OD, 0x6011); // find Index 0x6011
//assert(odEntry != NULL);
//
//static OD_extension_t odExt; // Ensure odExt remains in scope
//odExt.object = NULL; // Set to your object if needed
//odExt.read = NULL; // Set to your custom read function if needed
//odExt.write = libCOL_outputPDOCallback; // Set to your custom write function // flags are NULL
//
//// Attach the extension
//OD_extension_init(odEntry, &odExt);
//
//}
//
//libCOL_numbered_output_t* libCOL_getNumberedOutputs() // Used in Stack
//{
//    return libCOL_numberedOutputs;
//}
//
//uint16_t libCOL_getOutputCount() // Used in Stack
//{
//    return libCOL_outputCount;
//}
//
//void libCOL_outputUpdateStatusIndexManual(const uint16_t outputIndex, bool indication) // Used in Stack
//{
//    assert((libCOL_outputCount > 0) && (outputIndex < libCOL_outputCount));
//    if (useNumberedOutputs) {
//        setStatusInOD(&OD_outputGroup1[libCOL_numberedOutputs[outputIndex].number], &(libCOL_numberedOutputs[outputIndex].output), indication);
//    }
//}
//
//// static CO_SDO_abortCode_t libCOL_outputPDOCallback(CO_ODF_arg_t* arg) // Used in Stack
//// {
////     libCOL_output_t output;
////     const libCOL_virtualOutputMapping_t* mapped = (const libCOL_virtualOutputMapping_t*)arg->data;
//
////     if (
////             ((size_t)arg->dataLength != sizeof(libCOL_virtualOutputMapping_t))
////             || (libCOL_outputCallback == NULL))
////         return CO_SDO_AB_NONE;
//
////     output.function = (libCOL_outputFunction_t)mapped->basicFunction;
////     output.subFunction.raw = mapped->subFunction;
////     output.lift.raw = mapped->lift;
////     output.floor = mapped->floor;
////     output.door.raw = mapped->door;
////     output.functionData.raw = mapped->functionData;
////     libCOL_outputCallback(&output);
////     return CO_SDO_AB_NONE;
//// }
//
//static ODR_t libCOL_outputPDOCallback(OD_stream_t *stream, const void *buf, OD_size_t count, OD_size_t *countWritten) {
//    libCOL_output_t output;
//    const libCOL_virtualOutputMapping_t* mapped = (const libCOL_virtualOutputMapping_t*)stream->object;
//
//    // Validate the data length and callback function
//    if ((stream->subIndex == 0) || (mapped == NULL) || (libCOL_outputCallback == NULL)) {
//        return ODR_DEV_INCOMPAT; // Device incompatibility
//    }
//
//    // Populate the output structure based on the mapped data
//    output.function = (libCOL_outputFunction_t)mapped->basicFunction;
//    output.subFunction.raw = mapped->subFunction;
//    output.lift.raw = mapped->lift;
//    output.floor = mapped->floor;
//    output.door.raw = mapped->door;
//    output.functionData.raw = mapped->functionData;
//
//    // Invoke the callback function with the populated output
//    libCOL_outputCallback(&output);
//
//    // Indicate that all bytes have been processed
//    if (countWritten != NULL) {
//        *countWritten = count;
//    }
//
//    return ODR_OK;
//}
//
//bool libCOL_outputEnabledIndex(const uint16_t outputIndex) // Used in Stack
//{
//    return (OD_outputParameter1Group1[outputIndex] & 0x1);
//}
//
