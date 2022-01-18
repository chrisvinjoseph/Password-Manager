#include <iostream>
#include <vector>

#include "headers/encryptor.hpp"
#include "headers/decryptor.hpp"
#include "headers/hash.hpp"
#include "headers/misc.hpp"
#include "headers/pass_manager.hpp"

int main() {
    PassManager manager;
    manager.run();

    return 0;
}
