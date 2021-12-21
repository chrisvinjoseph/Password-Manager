#include <iostream>

#include "headers/encryptor.hpp"

int main() {
    Encryptor enc;
    enc.getFormatInput();
    enc.encrypt();
    enc.store();


    return 0;
}
