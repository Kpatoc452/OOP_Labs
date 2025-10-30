#include"replace.hpp"

#include<string>

void Replace(std::string& str) {
    for(size_t i = 0; i < str.size(); ++i) {
        if (str[i] == 'a') {
            str[i] = 'b';
        } else if (str[i] == 'b') {
            str[i]  = 'a';
        }
    }
}