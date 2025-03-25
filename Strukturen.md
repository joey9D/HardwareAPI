# Struktur.md  

Enthält einzelne Strukturen der jeweiligen Plattformen, zentral an einem Ort/Dokument um
allesauf einen Blick zu haben.

## Notwendige Treiber

- STM32 HAL für das jeweilige Board:    <https://github.com/STMicroelectronics>
- CMSIS Treiber für ARM:                <https://github.com/ARM-software/CMSIS_6>
- Arduino Treiber:                      <https://github.com/arduino/ArduinoCore-avr>

## Interfaces

### Wie soll/wird das richtige Board oder die richtige Klass/Funktion für das Board ausgewählt?  

Die einzelnen Funktionen müssen nicht neu geschrieben werden; es muss *nur* für das jeweilige Board  
die *richtige* Funktion gewählt werden.

bedingte Kompilierung

```c++
#define stm32
#ifdef stm32
read(){
  HAL_GPIO_ReadPin()
}
```

### GPIO  

Pin Nummerierung

### STM32  

**STM32 GPIO_InitTypeDef**  

```c++
typedef struct
{
  uint32_t Pin;       
  uint32_t Mode;      
  uint32_t Pull;      
  uint32_t Speed;     
  uint32_t Alternate;
} GPIO_InitTypeDef;
```

**PinState: High od. Low / 0 od. 1**  

```c++
typedef enum
{
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET
} GPIO_PinState;
```

#### ReadPin  

```c++
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
  GPIO_PinState bitstatus;
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->IDR & GPIO_Pin) != 0x00u) {
    bitstatus = GPIO_PIN_SET;
  } else {
    bitstatus = GPIO_PIN_RESET;
  }
  return bitstatus;
}
```

#### WritePin  

```c++
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) {
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_PIN_ACTION(PinState));

  if (PinState != GPIO_PIN_RESET) {
    GPIOx->BSRR = (uint32_t)GPIO_Pin;
  } else {
    GPIOx->BRR = (uint32_t)GPIO_Pin;
  }
}
```

#### TogglePin  

```c++
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
  uint32_t odr;
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  /* get current Output Data Register value */
  odr = GPIOx->ODR;
  /* Set selected pins that were at low level, and reset ones that were high */
  GPIOx->BSRR = ((odr & GPIO_Pin) << GPIO_NUMBER) | (~odr & GPIO_Pin);
}
```

#### Port Definition  

```c++
/**
  * @brief General Purpose I/O
  */
typedef struct
{
  __IO uint32_t MODER;       /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO uint32_t OTYPER;      /*!< GPIO port output type register,        Address offset: 0x04      */
  __IO uint32_t OSPEEDR;     /*!< GPIO port output speed register,       Address offset: 0x08      */
  __IO uint32_t PUPDR;       /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  __IO uint32_t IDR;         /*!< GPIO port input data register,         Address offset: 0x10      */
  __IO uint32_t ODR;         /*!< GPIO port output data register,        Address offset: 0x14      */
  __IO uint32_t BSRR;        /*!< GPIO port bit set/reset  register,     Address offset: 0x18      */
  __IO uint32_t LCKR;        /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  __IO uint32_t AFR[2];      /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
  __IO uint32_t BRR;         /*!< GPIO Bit Reset register,               Address offset: 0x28      */
} GPIO_TypeDef;
```

### Arduino  

#### Pfade  

C:\Users\jan.kristel\Dokumente\Arduino\libraries

C:\Users\jan.kristel\AppData\Local\Arduino15\packages\arduino\hardware\megaavr\1.8.8

---

Keine einheitliche Struktur. Nutzt Funktionen

```c++
pinMode(pin, mode)
digitalRead(pin)
digitalWrite(pin, value)
```

#### Code Regeln  

define Namen in *boards.txt* unter *.build.board= **board define name***

#### Initialisierung/Setup passiert vor dem Programm  

```c++
const int BUTTON_PIN = PC13;
const int LED_PIN    = PA5;

int ledState = LOW;     
int lastButtonState;    
int currentButtonState; 

void setup() {
  Serial.begin(115200);                // initialize serial
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);         

  currentButtonState = digitalRead(BUTTON_PIN);
}
```

#### pinMode()

```c++
void pinMode(uint8_t pin, PinMode mode) {
 uint8_t bit_mask = digitalPinToBitMask(pin);

 if ((bit_mask == NOT_A_PIN) || (mode > INPUT_PULLUP) || isDoubleBondedActive(pin)) return;

 PORT_t* port = digitalPinToPortStruct(pin);
 if(port == NULL) return;

 if(mode == OUTPUT) {
  port->DIRSET = bit_mask;      // Configure direction as output
 } else {           // mode == INPUT or INPUT_PULLUP
  uint8_t bit_pos = digitalPinToBitPosition(pin);
  /* Calculate where pin control register is */
  volatile uint8_t* pin_ctrl_reg = getPINnCTRLregister(port, bit_pos);
  /* Save state */
  uint8_t status = SREG;
  cli();
  port->DIRCLR = bit_mask;      // Configure direction as input
  
  /* Configure pull-up resistor */
  if(mode == INPUT_PULLUP){
   *pin_ctrl_reg |= PORT_PULLUPEN_bm;   // Enable pull-up 
  } else {          // mode == INPUT (no pullup) 
   *pin_ctrl_reg &= ~(PORT_PULLUPEN_bm);  // Disable pull-up
  }
  /* Restore state */
  SREG = status;
 }
}
```

#### Write/digitalWrite()

```c++
void digitalWrite(uint8_t pin, PinStatus val) {
 uint8_t bit_mask = digitalPinToBitMask(pin);

 if(bit_mask == NOT_A_PIN || isDoubleBondedActive(pin)) return;
 /* Turn off PWM if applicable */
 // If the pin that support PWM output, we need to turn it off
 // before doing a digital write.
 turnOffPWM(pin);
 PORT_t *port = digitalPinToPortStruct(pin);
 
 if(port->DIR & bit_mask) {
  /* Set output to value */
  if (val == LOW) { /* If LOW */
   port->OUTCLR = bit_mask;
  } else if (val == CHANGE) { /* If TOGGLE */
   port->OUTTGL = bit_mask;
         /* If HIGH OR  > TOGGLE  */
  } else {
   port->OUTSET = bit_mask;
  }
 /* Input direction */
 } else {
  uint8_t bit_pos = digitalPinToBitPosition(pin);
  volatile uint8_t* pin_ctrl_reg = getPINnCTRLregister(port, bit_pos);
  uint8_t status = SREG;
  cli();

  if(val == LOW) {
   /* Disable pullup */
   *pin_ctrl_reg &= ~PORT_PULLUPEN_bm;
  } else {
   /* Enable pull-up */
   *pin_ctrl_reg |= PORT_PULLUPEN_bm;
  }
  /* Restore system status */
  SREG = status;
 }
}
```

#### Read/digitalRead()

```c++
PinStatus digitalRead(uint8_t pin)
{
 /* Get bit mask and check valid pin */
 uint8_t bit_mask = digitalPinToBitMask(pin);
 if(bit_mask == NOT_A_PIN || isDoubleBondedActive(pin)) return LOW;

 // If the pin that support PWM output, we need to turn it off
 // before getting a digital reading.
 turnOffPWM(pin);

 /* Get port and check valid port */
 PORT_t *port = digitalPinToPortStruct(pin);

 /* Read pin value from PORTx.IN register */
 if(port->IN & bit_mask){
  return HIGH;
 } else {
  return LOW;
 }
 return LOW;
}
```

### ESP32

```c++
typedef struct {
    uint64_t pin_bit_mask;          /*!< GPIO pin: set with bit mask, each bit maps to a GPIO */
    gpio_mode_t mode;               /*!< GPIO mode: set input/output mode                     */
    gpio_pullup_t pull_up_en;       /*!< GPIO pull-up                                         */
    gpio_pulldown_t pull_down_en;   /*!< GPIO pull-down                                       */
    gpio_int_type_t intr_type;      /*!< GPIO interrupt type                                  */
#if SOC_GPIO_SUPPORT_PIN_HYS_FILTER
    gpio_hys_ctrl_mode_t hys_ctrl_mode;       /*!< GPIO hysteresis: hysteresis filter on slope input    */
#endif
} gpio_config_t;
```
