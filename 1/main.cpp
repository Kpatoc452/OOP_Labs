#include "replace.hpp"

int main() {
    std::string input;

    std::getline(std::cin, input);

    Replace(input);

    std::cout << input << std::endl;

    return 0;
}