#include <iostream>

#include "headers/pass_manager.hpp"
#include "headers/hash.hpp"

int PassManager::run() {
    // Login
    while(true) {
        if(loginMenu()) {
            while(true) {
                if(managerMenu()) {
                    std::cout << "Logged out." << std::endl;
                    break;
                } else {
                    return 0;
                }
            }
        } else {
            return 0;
        }
    }
}

int PassManager::login() {
    // Must return 1 if login successful
    std::string username, password, data;

    std::cout << "\n\tUsername: ";
    std::cin >> username;
    std::cout << "\n\tMaster Password: ";
    std::cin >> password;
    password = Hash::hash(&password);

    usr_file.open("users.txt");
    if(usr_file) {
        while(getline(usr_file, data, ',')) {
            if(data == username) {
                getline(usr_file, data, '\n');
                if(data == password) {
                    auth_username = username;
                    usr_file.close();
                    return 1;
                } else {
                    usr_file.close();
                    std::cout << "Incorrect password." << std::endl;
                    return 0;
                }
            } else {
                getline(usr_file, data, '\n');
            }
        }
        std::cout << "User not found. Try again." << std::endl;
        usr_file.close();
        return 0;
    } else {
        std::cout << "No users exist. Please create an account." << std::endl;
        return 0;
    }
}

int PassManager::loginMenu() {
    while(true) {
        std::cout << "\n1. Log in\n2. Create an account\n3. Help\n4. Quit" << std::endl;
        std::cin >> selection;
        switch(selection) {
            case 1:
                if(login()) {
                    std::cout << "\nLogin successful!" << std::endl;
                    // Logic for Password Manager menu
                    return 1;
                } else {
                    std::cout << "Login failed. Try again."
                }
                break;
            case 2:
                createAccount();
                break;
            case 3:
                showHelp();
                break;
            case 4:
                return 0;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
        }
    }
}
