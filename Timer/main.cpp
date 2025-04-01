#include <chrono>
#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <thread>
#include <windows.h>

// class Timer
// {
// private:
//     std::chrono::milliseconds _duration;

// public:
//     explicit Timer(std::chrono::milliseconds duration) : _duration(duration) {}

//     void start()
//     {
//         std::cout << "Duration: " << _duration.count() << " ms\n";
//         std::cout << "Timer gestartet, bitte warten...\n";
//         std::this_thread::sleep_for(_duration);
//         std::cout << "Zeit abgelaufen!\n";
//     }
// };

int main()
{
    // // Timer für 3 Sekunden erstellen
    // Timer timer(std::chrono::seconds(3));

    // // Timer starten
    // timer.start();
    SYSTEMTIME st, lt;

    GetSystemTime(&st);
    GetLocalTime(&lt);

    std::cout << "System time: " << st.wHour << ":" << st.wMinute << ":" << st.wSecond << '\n';
    std::cout << "System time: " << lt.wHour << ":" << lt.wMinute << ":" << lt.wSecond << '\n';
    // printf("The system time is: %d:%02d:%02d\n", st.wHour, st.wMinute, st.wSecond);
    // printf(" The local time is: %d:%02d:%02d\n", lt.wHour, lt.wMinute, lt.wSecond);
    return 0;
}
