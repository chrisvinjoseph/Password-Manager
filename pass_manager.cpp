#include <iostream>
#include <fstream>

#include <crypto++/misc.h>

#include "headers/decryptor.hpp"
#include "headers/encryptor.hpp"
#include "headers/pass_manager.hpp"
#include "headers/hash.hpp"
#include "headers/misc.hpp"

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

    usr_file.open("users.txt");
    if(usr_file) {
        std::cout << "\n\t- Login -" << std::endl;
        std::cout << "\nUsername: ";
        std::cin >> username;
        std::cout << "Master Password: ";
        std::cin >> password;
        password = Hash::hash(&password);
        while(getline(usr_file, data, ',')) {
            if(data == username) {
                getline(usr_file, data, '\n');
                if(data == password) {
                    auth_user_detail_list.auth_username = username;
                    usr_file.close();
                    return 1;
                } else {
                    usr_file.close();
                    std::cout << "\n\tIncorrect password." << std::endl;
                    std::cout << "\tLogin failed. Try again." << std::endl;
                    return 0;
                }
            } else {
                getline(usr_file, data, '\n');
            }
        }
        std::cout << "\n\tUser not found. Try again." << std::endl;
        usr_file.close();
        return 0;
    } else {
        std::cout << "\n\tNo users exist. Please create an account." << std::endl;
        return 0;
    }
}

int PassManager::loginMenu() {
    std::string username, pass, pass_conf;

    while(true) {
        std::cout << "\n\t- Login Menu -\n\n1. Log in\n2. Create an account\n3. Help\n4. Quit\nSelect an option: ";
        std::cin >> selection;
        switch(selection) {
            case 1:
                if(login()) {
                    std::cout << "\n\tLogin successful!" << std::endl;
                    return 1;
                }
                break;
            case 2:
                std::cout << "\n\t- Create account -" << std::endl;
                std::cout << "Enter a username: ";
                std::cin >> username;
                std::cout << "Enter a password: ";
                std::cin >> pass;
                std::cout << "Confirm password: ";
                std::cin >> pass_conf;
                if(pass == pass_conf) {
                    if(createAccount(&username, &pass)) {
                        std::cout << "\n\tAccount created!" << std::endl;
                    } else {
                        std::cout << "\n\tFailed to create account." << std::endl;
                    }
                }
                break;
            case 3:
                showHelpLogin();
                break;
            case 4:
                return 0;
            default:
                std::cout << "\n\tInvalid choice. Try again." << std::endl;
        }
    }
}

int PassManager::managerMenu() {
    // Returns 1 for log out or 0 for exit
    while(true) {
        std::cout << "\n\t- Password Manager -" << std::endl;
        std::cout << "\n1. Retrieve password\n2. Add password\n3. Log Out\n4. Exit\nSelect an option: ";
        std::cin >> selection;
        switch(selection) {
            case 1: {
                std::string password;
                bool pass_found;
                if(retrievePassword(&password)) {
                    pass_found = true;
                    while(pass_found) {
                        std::cout << "\n\tPassword found. \n\t- Please choose from the following -\n" << std::endl;
                        std::cout << "1. Display plain text password to terminal\n2. Copy password to clipboard\n3. Help\n4. Cancel\nSelect an option: " << std::endl;
                        std::cin >> selection;
                        switch(selection) {
                            case 1: {
                                std::cout << "\nPassword: " << password << std::endl;
                                CryptoPP::memset_z(&password[0], 0, password.size());
                                pass_found = false;
                                break;
                            }
                            case 2: {
                                // std::cout << "Copying password to clipboard..." << std::endl;
                                // if(copyToClipboard(&password)) {
                                //     std::cout << "Password successfully copied to clipboard." << std::endl;
                                //     memset_z(&password[0], 0, password.size());
                                //     pass_found = false;
                                // } else {
                                //     std::cout << "Password could not be copied to clipboard. For more information, try the 'Help' option." << std::endl;
                                // }

                                std::cout << "\n\tNO COPY FUNCTIONALITY YET" << std::endl;
                                CryptoPP::memset_z(&password[0], 0, password.size());
                                pass_found = false;
                                break;
                            }
                            case 3: {
                                showHelpPasswordFound();
                                break;
                            }
                            case 4: {
                                std::cout << "\n\tPassword retrieval cancelled.\n" << std::endl;
                                CryptoPP::memset_z(&password[0], 0, password.size());
                                pass_found = false;
                                break;
                            }
                            default: {
                                std::cout << "\n\tInvalid choice. Try again." << std::endl;
                            }
                        }
                    }
                } else {
                    std::cout << "\tA password could not be found for the credentials provided. Try again..." << std::endl;
                }
                break;
            }
            case 2: {
                if(addPassword()) {
                    std::cout << "\n\tPassword was added successfully!" << std::endl;
                } else {
                    std::cout << "\n\tPassword could not be added. Try again." << std::endl;
                }
                break;
            }
            case 3: {
                CryptoPP::memset_z(&auth_user_detail_list.auth_username[0], 0, auth_user_detail_list.auth_username.size());
                return 1;
            }
            case 4: {
                return 0;
            }
            default: {
                std::cout << "\n\tInvalid choice. Try again." << std::endl;
            }
        }
    }
}

int PassManager::retrievePassword(std::string* password) {
    std::string target_username, target_loc;
    Decryptor decryptor;

    if(decryptor.retrieveUser(&auth_user_detail_list.auth_username, &auth_user_detail_list.target_loc_username_list, &auth_user_detail_list.locations, &auth_user_detail_list.plaintextsizes, &auth_user_detail_list.IVs, &auth_user_detail_list.ciphers)) {
        std::cout << "\n\t- Retrieve Password -" << std::endl;
        std::cout << "\nUsername for target location: ";
        std::cin >> target_username;
        std::cout << "Target location: ";
        std::cin >> target_loc;

        for(int i = 0; i < (auth_user_detail_list.ciphers).size(); i++) {
            if((auth_user_detail_list.target_loc_username_list[i] == target_username) && (auth_user_detail_list.locations[i] == target_loc)) {
                *password = decryptor.decrypt(&auth_user_detail_list.plaintextsizes[i], &auth_user_detail_list.IVs[i], &auth_user_detail_list.ciphers[i]);
                return 1;
            }
        }
    } else {
        std::cout << "\n\tNo account file exists. Create an account first." << std::endl;
    }

    return 0;
}

int PassManager::addPassword() {
    std::string target_username, target_loc;
    Encryptor encryptor;

    std::cout << "\n\t- Add Password -" << std::endl;
    std::cout << "\nUsername for target location: ";
    std::cin >> target_username;
    std::cout << "Target location: ";
    std::cin >> target_loc;

    if(encryptor.getFormatInput()) {
        if(encryptor.encrypt()) {
            if(encryptor.store(auth_user_detail_list.auth_username, target_username, target_loc)) {
                return 1;
            } else {
                std::cout << "\n\tPassword could not be stored." << std::endl;
                return 0;
            }
        } else {
            std::cout << "\n\tEncryption failed." << std::endl;
            return 0;
        }
    } else {
        std::cout << "\n\tInvalid key length. Key must be at least 1 character and less than 32 characters." << std::endl;
        return 0;
    }
}

int PassManager::createAccount(std::string* username, std::string* password) {
    std::ofstream fout;
    *password = Hash::hash(password);

    fout.open("users.txt", std::ios_base::app);
    if(!fout) {
        std::cout << "\n\tCould not open users.txt." << std::endl;
        return 0;
    }

    fout << *username << "," << *password << "\n";

    return 1;
}

void PassManager::showHelpLogin() {
    std::cout << "HELP LOGIN" << std::endl;
}

void PassManager::showHelpPasswordFound() {
    std::cout << "HELP PASS FOUND" << std::endl;
}
