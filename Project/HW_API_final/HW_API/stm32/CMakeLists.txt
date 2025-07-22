add_library(stm32_hw 
    stm32c0/stm32c0_hw.cpp
)





target_include_directories(stm32_hw PUBLIC 
    "./"
    "./stm32c0"    
)