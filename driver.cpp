#include <iostream>
#include <vector>


#include "headers/encryptor.hpp"
#include "headers/decryptor.hpp"

struct User {
    std::string username;
    std::vector<std::string> locations;
    std::vector<size_t> plaintextsizes;
    std::vector<std::string> IVs;
    std::vector<std::string> ciphers;
};

int main() {
    Encryptor enc;
    Decryptor dec;
    User test_user;
    std::string plaintext;

    test_user.username = "test_user";

    enc.getFormatInput();
    enc.encrypt();
    enc.store(test_user.username, "test_location");
    dec.retrieve(&test_user.username, &test_user.locations, &test_user.plaintextsizes, &test_user.IVs, &test_user.ciphers);

    for(int i = 0; i < test_user.locations.size(); i++) {
        std::cout << test_user.username << "  " << test_user.locations[i] << "  " << &test_user.plaintextsizes << "  " << test_user.IVs[i] << "  " << test_user.ciphers[i] << std::endl;
    }

    for(int i = 0; i < test_user.locations.size(); i++) {
        if(test_user.locations[i] == "test_location") {
            plaintext = dec.decrypt(&test_user.plaintextsizes[i], &test_user.IVs[i], &test_user.ciphers[i]);
            break;
        }
    }

    std::cout << plaintext << std::endl;

    return 0;
}
