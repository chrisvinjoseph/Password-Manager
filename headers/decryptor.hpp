#ifndef DECRYPTOR_H
#define DECRYPTOR_H

#include <iostream>
#include <fstream>
#include <vector>

// Works in symmetry to encryptor. Load -> decrypt -> return plaintext

class Decryptor {
    public:
        void retrieveUser(std::string* user, std::vector<std::string>* target_loc_username_list, std::vector<std::string>* locations, std::vector<size_t>* plaintextsizes, std::vector<std::string>* IVs, std::vector<std::string>* ciphers);
        std::string decrypt(std::size_t* plaintextsize, std::string* ivstr, std::string* cipherstr);
};

#endif
