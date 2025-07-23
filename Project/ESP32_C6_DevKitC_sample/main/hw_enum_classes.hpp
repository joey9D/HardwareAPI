enum class Mode
{
    Disabled = GPIO_MODE_DEF_DISABLE,                                                         
    /*!< GPIO mode : input only                           */
    Input = GPIO_MODE_DEF_INPUT,                                                             
    /*!< GPIO mode : output only mode                     */
    Output = GPIO_MODE_DEF_OUTPUT,                                                           
    /*!< GPIO mode : output only with open-drain mode     */
    Output_Open_Drain = ((GPIO_MODE_DEF_OUTPUT) | (GPIO_MODE_DEF_OD)),                               
    /*!< GPIO mode : output and input with open-drain mode*/
    Input_Output_Open_Drain = ((GPIO_MODE_DEF_INPUT) | (GPIO_MODE_DEF_OUTPUT) | (GPIO_MODE_DEF_OD)), 
    /*!< GPIO mode : output and input mode                */
    Input_Output = ((GPIO_MODE_DEF_INPUT) | (GPIO_MODE_DEF_OUTPUT)),     
    
};

enum class Pull
{
    None = GPIO_FLOATING, 
    Up = GPIO_PULLUP_ONLY,
    Down = GPIO_PULLDOWN_ONLY,
    UpDown = GPIO_PULLUP_PULLDOWN,
}

enum class Speed
{
    Low = GPIO_DRIVE_CAP_0,
    Medium = GPIO_DRIVE_CAP_1,
    High = ((GPIO_DRIVE_CAP_2) | (GPIO_DRIVE_CAP_DEFAULT)) ,
    Very_High = GPIO_DRIVE_CAP_3,
    Max = GPIO_DRIVE_CAP_MAX,
}

enum class Interrupt
{
    Disabled = GPIO_INTR_DISABLE,
    Rising = GPIO_INTR_POSEDGE,
    Falling = GPIO_INTR_NEGEDGE,
    RisingFalling = GPIO_INTR_ANYEDGE,
    Low_Level = GPIO_INTR_LOW_LEVEL,
    High_Level = GPIO_INTR_HIGH_LEVEL,
    Max = GPIO_INTR_MAX,
}