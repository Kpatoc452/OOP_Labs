#include <iostream>
#include <ostream>
#include <string>
#include "decimal.hpp"
#include "exceptions.hpp"
#include "include/decimal.hpp"
#include "include/exceptions.hpp"

int main() {
    std::cout << "Enter number to see it" << std::endl;
    std::string input;
    std::cin >> input;
    try {
        Decimal::Decimal number(input);
        std::cout << number.String() << std::endl;
    } catch (exception::NaNException) {
        std::cout << "Invalid args" << std::endl;
    }
    return 0;
}