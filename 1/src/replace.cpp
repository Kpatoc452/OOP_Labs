#include"replace.hpp"

#include<string>

void Replace(std::string& str) {
    for(char& c : str) {
        if (c == 'a') {
            c = 'b';
        } else if (c == 'b') {
            c = 'a';
        }
    }
}