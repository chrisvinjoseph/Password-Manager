#include <iostream>
#include <vector>


#include "headers/encryptor.hpp"
#include "headers/decryptor.hpp"

struct User {
    std::string username;
    std::vector<std::string> locations;
    std::vector<std::string> ciphers;
};

int main() {
    Encryptor enc;
    Decryptor dec;
    User test_user;

    test_user.username = "test_user";

    enc.getFormatInput();
    enc.encrypt();
    enc.store(test_user.username, "test_location");
    dec.retrieve(&test_user.username, &test_user.locations, &test_user.ciphers);

    for(int i = 0; i < test_user.locations.size(); i++) {
        std::cout << test_user.username << "  " << test_user.locations[i] << "  " << test_user.ciphers[i] << std::endl;
    }

    return 0;
}
