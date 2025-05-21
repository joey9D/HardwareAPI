# Toolchain-Datei für ARM Cross-Compile mit arm-none-eabi

# Setze die Zielplattform
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Toolchain-Programme finden
find_program(CMAKE_C_COMPILER arm-none-eabi-gcc REQUIRED)
find_program(CMAKE_CXX_COMPILER arm-none-eabi-g++ REQUIRED)
find_program(CMAKE_ASM_COMPILER arm-none-eabi-gcc REQUIRED)
find_program(CMAKE_LINKER arm-none-eabi-ld REQUIRED)
find_program(CMAKE_OBJCOPY arm-none-eabi-objcopy REQUIRED)
find_program(CMAKE_SIZE arm-none-eabi-size REQUIRED)

set(CMAKE_SYSROOT "/opt/homebrew/Cellar/arm-none-eabi-gcc/15.1.0/")

# -----------------------------------------
# OS independent
# -----------------------------------------
if(APPLE)
    include_directories(
        ${CMAKE_SYSROOT}/lib/gcc/arm-none-eabi/15.1.0/include
        ${CMAKE_SYSROOT}/lib/gcc/arm-none-eabi/15.1.0/include-fixed
    )
endif()
