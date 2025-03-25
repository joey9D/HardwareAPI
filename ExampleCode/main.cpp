void main(){
    Board* stm32go = new STM32();
    GPIO(stm32go);

    Board* arduinoUno = new Arduino();
    GPIO(arduinoUno);

    stm32g0.arduinoFunction();
}