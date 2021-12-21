#ifndef DECRYPTOR_H
#define DECRYPTOR_H

#include <iostream>
#include <fstream>
#include <vector>

// Works in symmetry to encryptor. Load -> decrypt -> return plaintext

class Decryptor {
    public:
        void loadUsersCiphers(std::string* user, std::vector<std::string>* locations, std::vector<std::string>* ciphers);
};

#endif
