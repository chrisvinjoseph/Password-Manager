#include <iostream>

#include "headers/pass_manager.hpp"

PassManager::PassManager(std::bool* auth) {
    auth_flag = auth;
}

void PassManager::PassManager test() {
    std::cout << "PASS_MG TEST" << std::endl;
}
