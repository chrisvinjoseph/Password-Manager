// Crypto++ Includes
// #include <crypto++/cryptlib.h>
// #include <crypto++/rijndael.h>
// #include <crypto++/modes.h>
// #include <crypto++/files.h>
// #include <crypto++/osrng.h>
// #include <crypto++/hex.h>
// #include <crypto++/misc.h>
// #include <cryptopp/eax.h>

#include <iostream>
#include <fstream>
#include <vector>

#include "headers/decryptor.hpp"

// Works in symmetry to encryptor. retrieve -> decrypt -> return plaintext

void Decryptor::retrieve(std::string* user, std::vector<std::string>* locations, std::vector<std::string>* ciphers) {
    std::ifstream fin("ciphers.txt");
    std::string data;

    if(fin) {
        while(getline(fin, data, ',')) {
            if(data == *user) {
                getline(fin, data, ',');
                locations->push_back(data);
                getline(fin, data, '\n');
                ciphers->push_back(data);
            } else {
                // When usernames dont match, data var will be populated by
                // the rest of the line. This will then be overwritten.
                getline(fin, data, '\n');
            }
        }
    } else {
        std::cout << "File not working." << std::endl;
    }

    fin.close();
}
