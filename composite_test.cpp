#include <iostream>
#include <vector>

class Led
{
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual ~Led() = default;
};

class SingleLed : public Led
{
private:
    std::string _name;

public:
    SingleLed(const std::string &name) : _name(name) {}

    void on() override
    {
        std::cout << _name << " is ON\n";
    }

    void off() override
    {
        std::cout << _name << " is OFF\n";
    }
};

class LedGroup : public Led
{
private:
    std::vector<Led *> leds;

public:
    void add(Led *led)
    {
        leds.push_back(led);
    }

    void on() override
    {
        for (auto led : leds)
        {
            led->on();
        }
    }

    void off() override
    {
        for (auto led : leds)
        {
            led->off();
        }
    }
};

int main()
{
    SingleLed red("Red");
    SingleLed green("Green");
    SingleLed blue("Blue");

    LedGroup group;
    group.add(&red);
    group.add(&green);
    group.add(&blue);

    std::cout << "Turning on group:\n";
    group.on();

    std::cout << "Turning off group:\n";
    group.off();

    return 0;
}
