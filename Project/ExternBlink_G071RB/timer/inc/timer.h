#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

class Timer {
    private:
        uint32_t startTick;
        uint32_t elapsedTicks;
    public:
        Timer() : startTick(0), elapsedTicks(0) {}

        // Startet den Timer
        void start() {
            startTick = getSysTick();
        }

        // Gibt die vergangene Zeit in Millisekunden zurück
        uint32_t elapsedMillis() {
            uint32_t currentTick = getSysTick();
            if (currentTick >= startTick) {
                elapsedTicks = currentTick - startTick;
            } else {
                // Handle SysTick overflow (SysTick zählt zurückwärts)
                elapsedTicks = (SysTick_MAX - startTick) + currentTick + 1;
            }
            return ticksToMillis(elapsedTicks);
        }


        static constexpr uint32_t SysTick_MAX = 0xFFFFFF; // 24-bit SysTick Counter
        static constexpr uint32_t SysTick_CLK = 1000;     // SysTick-Takt in Hz (1 ms Takt)

        // Liest den aktuellen Wert des SysTick-Timers
        uint32_t getSysTick() {
            return SysTick->VAL; // Annahme: SysTick->VAL ist der aktuelle Zählerwert
        }

        // Konvertiert Ticks in Millisekunden
        uint32_t ticksToMillis(uint32_t ticks) {
            return ticks / (SysTick_CLK / 1000);
        }
};

#endif // TIMER_H