#include <iostream>
#include <vector>

#include "headers/encryptor.hpp"
#include "headers/decryptor.hpp"
#include "headers/hash.hpp"
#include "headers/misc.hpp"

int main() {
    PassManager passmanager;
    LoginManager login;
    int selection;
    bool auth_flag = false;

    showSplash();
    while(!auth_flag) {
        login.displayMenu();
        auth_flag = login.authorized();
    }

    return 0;
}
