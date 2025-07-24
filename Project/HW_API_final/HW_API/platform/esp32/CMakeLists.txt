add_library(esp32_hw
    "esp32/esp32_hw.cpp"
)





target_include_directories(esp32_hw PUBLIC 
    "./"
    "./esp32c6_devkitc"    
)