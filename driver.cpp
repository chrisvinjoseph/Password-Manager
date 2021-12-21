#include <iostream>

#include "headers/encryptor.hpp"

int main() {
    Encryptor enc;
    enc.getFormatInput();
    enc.encrypt();
    enc.store("test_user", "test_location");
    

    return 0;
}
