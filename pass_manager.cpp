#include <iostream>
#include <fstream>

#include "headers/pass_manager.hpp"
#include "headers/hash.hpp"
#include "headers/misc.hpp"

int PassManager::run() {
    Misc::introText();

    // Login
    while(true) {
        if(loginMenu()) {
            while(true) {
                if(managerMenu()) {
                    std::cout << "\nSuccessfully logged out." << std::endl;
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
        std::cout << "\n\n1. Log in\n2. Create an account\n3. Help\n4. Quit\nSelect an option: " << std::endl;
        std::cin >> selection;
        switch(selection) {
            case 1:
                if(login()) {
                    std::cout << "\nLogin successful!\n\n" << std::endl;
                    return 1;
                } else {
                    std::cout << "Login failed. Try again.\n\n"
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

int PassManager::managerMenu() {
    // Returns 1 for log out or 0 for exit
    while(true) {
        std::cout << "\n\n1. Retrieve password\n2. Add password\n3. Log Out\n4. Exit\nSelect an option: " << std::endl;
        std::cin >> selection;
        switch(selection) {
            case 1:
                std::string password;
                bool pass_found;
                if(retrievePassword(&password)) {
                    pass_found = true;
                    while(pass_found) {
                        std::cout << "Password found. \n\t- Please choose from the following -\n" << std::endl;
                        std::cout << "1. Display plain text password to terminal\n2. Copy password to clipboard\n3. Help\n4. Cancel\nSelect an option: " << std::endl;
                        std::cin >> selection;
                        switch(selection) {
                            case 1:
                                std::cout << "\nPassword: " << password << std::endl;
                                zeroStr(&password);
                                pass_found = false;
                                break;
                            case 2:
                                std::cout << "Copying password to clipboard..." << std::endl;
                                if(copyToClipboard(&password)) {
                                    std::cout << "Password successfully copied to clipboard." << std::endl;
                                    zeroStr(&password);
                                    pass_found = false;
                                } else {
                                    std::cout << "Password could not be copied to clipboard. For more information, try the 'Help' option." << std::endl;
                                }
                                break;
                            case 3:
                                showHelpPasswordFound();
                                break;
                            case 4:
                                std::cout << "Password retrieval cancelled.\n" << std::endl;
                                zeroStr(&password);
                                pass_found = false;
                                break;
                            default:
                                std::cout << "Invalid choice. Try again." << std::endl;
                        }
                    }
                } else {
                    std::cout << "A password could not be found for the credentials provided. Try again..." << std::endl;
                }
                break;
            case 2:
                // THIS FUNCTION IS A PLACEHOLDER.
                // Proper logic needs to be added to support the add password functionality.
                // addPassword() will return int based on password add success
                addPassword();
                break;
            case 3:
                zeroStr(&auth_username);
                return 1;
            case 4:
                return 0;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
        }
    }
}
