#include <iostream>
#include <vector>

#include "headers/pass_manager.hpp"
#include "headers/misc.hpp"


// g++ driver.cpp encryptor.cpp decryptor.cpp hash.cpp misc.cpp pass_manager.cpp -lcrypto++

int main() {
    PassManager manager;
    manager.run();

    Misc::exitText();

    return 0;
}
