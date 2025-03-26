#ifndef OD_FUNCTIONS_H
#define OD_FUNCTIONS_H

#include "CiA417_LiftTypes.h"
#include <type_traits>
#include <cassert>

/*********************************************************************************************************
   *      Definition of an input acknowledgement callback
     *
     *      This callback function gets called whenever an input acknowledgement
     *      event is detected. It can be used to update the corresponding GPIO
     *      and/or software states.
     */


typedef void (*libCOL_inputAcknowledge_t)(const libCOL_input_t* input);


/*********************************************************************************************************

Input Output Common Functions for Object Dictionary

**********************************************************************************************************/

// Type trait to check if T is an input type
template<typename T>
struct is_input : std::false_type {};

// Specialization for libCOL_input_t
template<>
struct is_input<libCOL_input_t> : std::true_type {};

// Type trait to check if T is an output type
template<typename T>
struct is_output : std::false_type {};

// Specialization for libCOL_output_t
template<>
struct is_output<libCOL_output_t> : std::true_type {};

// Template function to copy structured data to OD
template<typename T>
static void copyToOD(uint8_t* out, const T* in);

// Template function to copy structured data from OD
template<typename T>
static void copyFromOD(T* out, const uint8_t* in);

// Template function for numbered copy from OD
template<typename T>
static bool numberedCopyFromOD(uint8_t number, T* out, const uint8_t* in);

// Template function to copy status to OD
template<typename T>
static void copyStatusToOD(uint8_t* out, const T* in);


// Template function definition to copy structured data to OD
template<typename T>
static void copyToOD(uint8_t* out, const T* in) {
    static_assert(is_input<T>::value || is_output<T>::value, "Type must be either libCOL_input_t or libCOL_output_t");
    assert(in != nullptr && out != nullptr);

    // libCOL_virtualInputMapping_t* mapped = reinterpret_cast<libCOL_virtualInputMapping_t*>(out);
    // mapped->basicFunction = static_cast<uint8_t>(in->function);
    // mapped->subFunction = in->subFunction.raw;
    // mapped->lift = in->lift.raw;
    // mapped->floor = in->floor;
    // mapped->door = in->door.raw;
    // mapped->functionData = in->functionData.raw;
    // Convert `out` to a byte array (octet string)
    uint8_t* data = reinterpret_cast<uint8_t*>(out);

    // Ensure we have 6 bytes to write
    constexpr size_t expectedSize = sizeof(virtualIOMapping_data_t);
    if (data == nullptr) {
        return;
    }

    // Prepare the data structure
    virtualIOMapping_data_t mapped;
    mapped.basicFunction = static_cast<uint8_t>(in->basicfunction);
    mapped.subFunction = in->subFunction.raw;
    mapped.lift = in->lift.raw;
    mapped.floor = in->floor;
    mapped.door = in->door.raw;
    mapped.functionData = in->functionData.raw;

    // Copy the mapped structure to OD as an octet string
    memcpy(data, &mapped, expectedSize);  // <-- Safe byte copy
}

// Template function definition to copy structured data from OD
template<typename T>
static void copyFromOD(T* out, const uint8_t* in) {
    static_assert(is_input<T>::value || is_output<T>::value, "Type must be either libCOL_input_t or libCOL_output_t");
    assert(in != nullptr && out != nullptr);

    const virtualIOMapping_data_t* mapped = reinterpret_cast<const virtualIOMapping_data_t*>(in);
    out->function = static_cast<decltype(out->function)>(mapped->basicFunction);
    out->subFunction.raw = mapped->subFunction;
    out->lift.raw = mapped->lift;
    out->floor = mapped->floor;
    out->door.raw = mapped->door;
    out->functionData.raw = mapped->functionData;
}

// Template function definition for numbered copy from OD
template<typename T>
static bool numberedCopyFromOD(uint8_t number, T* out, const uint8_t* in) {
    static_assert(std::is_same<typename std::remove_cv<T>::type, libCOL_numbered_input_t>::value ||
        std::is_same<typename std::remove_cv<T>::type, libCOL_numbered_output_t>::value,
        "Type must be either libCOL_numbered_input_t or libCOL_numbered_output_t");
    assert(in != nullptr && out != nullptr);

    // virtualIOMapping_data_t* mapped = reinterpret_cast<virtualIOMapping_data_t*>(in);
    // if (mapped->basicFunction == 0) {
    //     return false;
    // }


    //Convert `in` to a byte array (octet string)
    const uint8_t* data = reinterpret_cast<const uint8_t*>(in);

    // Ensure we have 6 bytes to read
    constexpr size_t expectedSize = sizeof(virtualIOMapping_data_t);
    if (data == nullptr) {
        return false;
    }

    // Manually copy data into the structure
    virtualIOMapping_data_t mapped;
    memcpy(&mapped, data, expectedSize);  // <-- Safe byte copy

    // Check if mapping is valid
    if (mapped.basicFunction == 0) {
        return false;
    }


    // out->number = number;
    // out->input.function = static_cast<decltype(out->input.function)>(mapped->basicFunction);
    // out->input.subFunction.raw = mapped->subFunction;
    // out->input.lift.raw = mapped->lift;
    // out->input.floor = mapped->floor;
    // out->input.door.raw = mapped->door;
    // out->input.functionData.raw = mapped->functionData;
    out->number = number;
    if constexpr (std::is_same<typename std::remove_cv<T>::type, libCOL_numbered_input_t>::value) {
        out->input.basicfunction = static_cast<decltype(out->input.basicfunction)>(mapped.basicFunction);
        out->input.subFunction.raw = mapped.subFunction;
        out->input.lift.raw = mapped.lift;
        out->input.floor = mapped.floor;
        out->input.door.raw = mapped.door;
        out->input.functionData.raw = mapped.functionData;
    } else if constexpr (std::is_same<typename std::remove_cv<T>::type, libCOL_numbered_output_t>::value) {
        out->output.basicfunction = static_cast<decltype(out->output.basicfunction)>(mapped.basicFunction);
        out->output.subFunction.raw = mapped.subFunction;
        out->output.lift.raw = mapped.lift;
        out->output.floor = mapped.floor;
        out->output.door.raw = mapped.door;
        out->output.functionData.raw = mapped.functionData;
    }
    // if constexpr (std::is_same<typename std::remove_cv<T>::type, libCOL_numbered_input_t>::value) {
    //     out->input.basicfunction = static_cast<decltype(out->input.basicfunction)>(in[number][1]);
    //     out->input.subFunction.raw = in[number][2];
    //     out->input.lift.raw = in[number][3];
    //     out->input.floor = in[number][4];
    //     out->input.door.raw = in[number][5];
    //     out->input.functionData.raw = in[number][6];
    // } else if constexpr (std::is_same<typename std::remove_cv<T>::type, libCOL_numbered_output_t>::value) {
    //     out->output.basicfunction = static_cast<decltype(out->output.basicfunction)>(in[number][1]);
    //     out->output.subFunction.raw = in[number][2];
    //     out->output.lift.raw = in[number][3];
    //     out->output.floor = in[number][4];
    //     out->output.door.raw = in[number][5]r;
    //     out->output.functionData.raw = in[number][6];
    // }
    return true;

}

// Template function definition to copy status to OD
template<typename T>
static void copyStatusToOD(uint8_t* out, const T* in) {
    static_assert(is_input<T>::value || is_output<T>::value, "Type must be either libCOL_input_t or libCOL_output_t");
    assert(in != nullptr && out != nullptr);

    // libCOL_virtualInputMapping_t* mapped = reinterpret_cast<libCOL_virtualInputMapping_t*>(out);
    // uint8_t temp = mapped->functionData;
    // temp &= 0xFE;
    // temp |= (in->functionData.raw & 0x01);
    // mapped->functionData = temp;
    // Convert `out` to a byte array (octet string)
    uint8_t* data = reinterpret_cast<uint8_t*>(out);

    // Ensure we have 6 bytes to write
    constexpr size_t expectedSize = sizeof(virtualIOMapping_data_t);
    if (data == nullptr) {
        return;
    }

    // Manually copy the existing data to a temporary structure
    virtualIOMapping_data_t mapped;
    memcpy(&mapped, data, expectedSize);

    // Modify only the least significant bit (LSB) of functionData
    uint8_t temp = mapped.functionData;
    temp &= 0xFE;  // Clear bit 0
    temp |= (in->functionData.raw & 0x01);  // Set bit 0 from input

    // Write modified value back to mapped structure
    mapped.functionData = temp;

    // Copy modified structure back to the OD
    memcpy(data, &mapped, expectedSize);  // <-- Safe byte copy

}

/*********************************************************************************************************

Output Functions for Object Dictionary

**********************************************************************************************************/
// Template function decleration to copy status to OD

template<typename T>
static void setStatusInOD(uint8_t* out, const libCOL_output_t* in, bool indication);


// Template function definition to copy status to OD
template<typename T>
static void setStatusInOD(  uint8_t* out, const T* in, bool indication)
{
    // libCOL_virtualOutputMapping_t* mapped = (libCOL_virtualOutputMapping_t*)out;
    // uint8_t temp = mapped->functionData;
    // temp &= 0xFE;
    // if (indication) {
    //     temp |= 1;
    // }
    // mapped->functionData = temp;
    static_assert(std::is_same<T, libCOL_input_t>::value || 
        std::is_same<T, libCOL_output_t>::value, 
        "Type must be either libCOL_input_t or libCOL_output_t");

assert(in != nullptr && out != nullptr);

// Convert `out` to a byte array (octet string)
uint8_t* data = reinterpret_cast<uint8_t*>(out);

// Ensure we have 6 bytes to modify
constexpr size_t expectedSize = sizeof(virtualIOMapping_data_t);
if (data == nullptr) {
return;
}

// Manually copy the existing data to a temporary structure
virtualIOMapping_data_t mapped;
memcpy(&mapped, data, expectedSize);

// Modify only the least significant bit (LSB) of functionData
uint8_t temp = mapped.functionData;
temp &= 0xFE;  // Clear bit 0
if (indication) {
temp |= 1;  // Set bit 0 if indication is true
}

// Write modified value back to mapped structure
mapped.functionData = temp;

// Copy modified structure back to the OD
memcpy(data, &mapped, expectedSize);
}
 




/*********************************************************************************************************

Input Functions for Object Dictionary

**********************************************************************************************************/

template<typename T>
static bool compareWithOD(uint8_t out, const libCOL_input_t* in);


template<typename T>
static bool compareWithOD(uint8_t* out, const T* in)
{
	virtualIOMapping_data_t* mapped = (virtualIOMapping_data_t*)out;
    if (mapped->basicFunction != (uint8_t)in->basicfunction) {
        return false;
    }
    if (mapped->subFunction != in->subFunction.raw) {
        return false;
    }
    if (mapped->lift != in->lift.raw) {
        return false;
    }
    if (mapped->floor != in->floor) {
        return false;
    }
    if (mapped->door != in->door.raw) {
        return false;
    }
    if (mapped->functionData != in->functionData.raw) {
        return false;
    }
    return true;
}

#endif // OD_FUNCTIONS_H


