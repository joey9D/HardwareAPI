#include "main.h"

int main()
{
    std::uint32_t val_a = 5;
    std::uint32_t val_b = 10;

    std::uint32_t res = basic_add(val_a, val_b);
    std::cout << "Cmake res = " << res << std::endl;

    gpio_print();
    return 0;
}
