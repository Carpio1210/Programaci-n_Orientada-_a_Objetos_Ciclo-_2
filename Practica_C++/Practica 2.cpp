#include <iostream>

//Calculator
int main() {
    while (true) {
        int option;
        std::cout << "What option do u want to use? 1. Sum.    2. Substraction    3. Multiplication.     4. Division     5. Exit" << std::endl;
        std::cin >> option;

        if (option == 5) {
            std::cout << "Thank u see u later" << std::endl;
            break;
        }

        int a,b;
        std::cout << "Gimme a number: " << std::endl;
        std::cin >> a;
        std::cout << "Gimme a second number: " << std::endl;
        std::cin >> b;

        if (option == 1)
            std::cout << "Sum: " << a + b << std::endl;
        else if (option == 2)
            std::cout << "Substraction: " << a - b << std::endl;
        else if (option == 3)
            std::cout << "Multiplication: " << a*b << std::endl;
        else if (option == 4)
            if (b == 0)
                std::cout << "Unvalidated division for 0" << std::endl;
            else
                std::cout << "Division: " << static_cast<double>(a)/b << std::endl;

    }
    return 0;
}