#include <iostream>

// Interface equivalent pure abstract class

class InterfaceHardware
{
public:
    virtual std::string getName() = 0;
};

// Class B which inherits InterfaceHardware
class Stm32 : public InterfaceHardware
{
public:
    std::string getName()
    {
        return "STM32";
    }
};

// Class C which inherits InterfaceHardware
class Microchip : public InterfaceHardware
{
public:
    std::string getName()
    {
        return "Microchip";
    }
};

class Output
{
public:
    Output(InterfaceHardware &val)
    {
        p_Out = &val;
    }

    void execOutput()
    {
        std::cout << p_Out->getName() << std::endl;
    }

private:
    InterfaceHardware *p_Out;
};

int main()
{
    Stm32 hardwareDefinition;
    // Microchip hardwareDefinition;
    Output l_hardware(hardwareDefinition);
    l_hardware.execOutput();

    return 0;
}
