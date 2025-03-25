#ifndef GPIOBASE_H_
#define GPIOBASE_H_

class GPIOBase {
public:
    virtual ~GPIOBase() = default;

    // GPIO-Funktionen für Ein- und Ausgabe
    virtual void setOutput(bool state) = 0;
    virtual void toggle() = 0;
    virtual bool isPinOn() const = 0;
};

#endif /* GPIOBASE_H_ */
