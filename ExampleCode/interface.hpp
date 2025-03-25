#ifndef IGPIO_H_
#define IGPIO_H_

class IGPIO {
public:
    virtual ~IGPIO() = default;

    virtual void setOutput(bool state) = 0;
    virtual void toggle() = 0;
    virtual bool isPinOn() = 0;
};

#endif /* IGPIO_H_ */
