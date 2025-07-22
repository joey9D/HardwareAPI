#include "main.hpp"

int main()
{
    std::cerr << "HW API Test Application" << std::endl;
    std::cout << "Starting HW API Test Application..." << std::endl;
    print_core_test();
    print_gpio_test();

    int done = 0;
    std::cout << "Enter a number to exit..." << std::endl;
    std::cin >> done;
    std::cout << done;
    
    return 0;
}
