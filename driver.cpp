#include <iostream>
#include <vector>

#include "headers/encryptor.hpp"
#include "headers/decryptor.hpp"
#include "headers/hash.hpp"
#include "headers/misc.hpp"
#include "headers/pass_manager.hpp"
#include "headers/login_manager.hpp"


int main() {
    bool auth_flag = false;
    std::string username;

    PassManager passmanager(&auth_flag);
    LoginManager login;

    showSplash();
    while(!auth_flag) {
        login.displayMenu();
        auth_flag = login.getStatus();
        if(auth_flag) { username = login.getUsername(); }
    }

    while(auth_flag) {
        passmanager.displayMenu();
    }

    std::cout << "Logged out.\nExiting..." << std::endl;

    return 0;
}
