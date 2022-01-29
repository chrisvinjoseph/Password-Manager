#include <iostream>
#include <fstream>

#include <crypto++/misc.h>

#include "headers/pass_manager.hpp"
#include "headers/hash.hpp"
#include "headers/misc.hpp"
#include "headers/decryptor.hpp"

// NOTE: User data should be retrieved via Decryptor::retrieveUser() upon logging in
// and subsequently purged upon log out. This will prevent stray data from other users or duplicate data
// from the same user.

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
                    auth_user_detail_list.auth_username = username;
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
                showHelpLogin();
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
                                memset_z(&password[0], 0, password.size());
                                pass_found = false;
                                break;
                            case 2:
                                std::cout << "Copying password to clipboard..." << std::endl;
                                if(copyToClipboard(&password)) {
                                    std::cout << "Password successfully copied to clipboard." << std::endl;
                                    memset_z(&password[0], 0, password.size());
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
                                memset_z(&password[0], 0, password.size());
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
                if(addPassword()) {
                    std::cout << "\n\nPassword was added successfully!" << std::endl;
                } else {
                    std::cout << "\nPassword could not be added. Try again." << std::endl;
                }
                break;
            case 3:
                memset_z(&auth_user_detail_list.auth_username[0], 0, auth_user_detail_list.auth_username.size());
                return 1;
            case 4:
                return 0;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
        }
    }
}

int PassManager::retrievePassword(std::string* password) {
    std::string target_username, target_loc;
    Decryptor decryptor;

    decryptor.retrieveUser(&auth_user_detail_list.auth_username, &auth_user_detail_list.target_loc_username_list, &auth_user_detail_list.locations, &auth_user_detail_list.plaintextsizes, &auth_user_detail_list.IVs, &auth_user_detail_list.ciphers);

    std::cout << "\n\nUsername for target location: ";
    std::cin >> target_username;
    std::cout << "\nTarget location: ";
    std::cin >> target_loc;

    for(int i = 0; i < (auth_user_detail_list.ciphers).size(); i++) {
        if((auth_user_detail_list.target_loc_username_list[i] == target_username) && (auth_user_detail_list.location[i] == target_loc)) {
            *password = decryptor.decrypt(&auth_user_detail_list.plaintextsizes[i], &auth_user_detail_list.IVs[i], &auth_user_detail_list.ciphers[i]);
            return 1;
        }
    }

    return 0;
}

int PassManager::addPassword() {
    std::string target_username, target_loc;
    Encryptor encryptor;

    std::cout << "\n\nUsername for target location: ";
    std::cin >> target_username;
    std::cout << "\nTarget location: ";
    std::cin >> target_loc;

    if(encryptor.getFormatInput()) {
        if(encryptor.encrypt()) {
            if(encryptor.store(auth_user_detail_list.auth_username, target_username, target_loc)) {
                return 1;
            } else {
                std::cout << "Password could not be stored." << std::endl;
                return 0;
            }
        } else {
            std::cout << "Encryption failed." << std::endl;
            return 0;
        }
    } else {
        std::cout << "\nInvalid key length. Key must be at least 1 character and less than 32 characters." << std::endl;
        return 0;
    }
}
