# Add the directories for the project. 

set(CORE_LIB "core")
set(GPIO_LIB "gpio")

# Comment the directories that are not needed.
add_subdirectory(${CORE_LIB})
add_subdirectory(${GPIO_LIB})