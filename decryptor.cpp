// Crypto++ Includes
#include <crypto++/cryptlib.h>
#include <crypto++/rijndael.h>
#include <crypto++/modes.h>
#include <crypto++/files.h>
#include <crypto++/osrng.h>
#include <crypto++/hex.h>
#include <crypto++/misc.h>
#include <cryptopp/eax.h>

#include <iostream>
#include <fstream>
#include <vector>

#include "headers/decryptor.hpp"

// Works in symmetry to encryptor. retrieve -> decrypt -> return plaintext
using namespace CryptoPP;

// These parameters should be replaced by just a pointer to user struct from misc.hpp at some point
int Decryptor::retrieveUser(std::string* user, std::vector<std::string>* target_loc_username_list, std::vector<std::string>* locations, std::vector<size_t>* plaintextsizes, std::vector<std::string>* IVs, std::vector<std::string>* ciphers) {
    std::ifstream fin("ciphers.txt");
    std::string data;

    if(fin) {
        while(getline(fin, data, ',')) {
            if(data == *user) {
                getline(fin, data, ',');
                target_loc_username_list->push_back(data);
                getline(fin, data, ',');
                locations->push_back(data);
                getline(fin, data, ',');
                plaintextsizes->push_back((size_t)std::stoi(data));
                getline(fin, data, ',');
                IVs->push_back(data);
                getline(fin, data, '\n');
                ciphers->push_back(data);
            } else {
                // When usernames dont match, data var will be populated by
                // the rest of the line. This will then be overwritten.
                getline(fin, data, '\n');
            }
        }
    } else {
        memset_z(&data[0], 0, data.size());

        fin.close();
        return 0;
    }

    memset_z(&data[0], 0, data.size());

    fin.close();
    return 1;
}

std::string Decryptor::decrypt(std::size_t* plaintextsize, std::string* ivstr, std::string* cipherstr) {
    SecByteBlock* iv;
    SecByteBlock* key;

    std::string keystr, b64_decoded_cipher, b64_decoded_iv, aes_decoded_plaintext;

    StringSource ivss(*ivstr, true, new HexDecoder(new StringSink(b64_decoded_iv)));
    StringSource cipherss(*cipherstr, true, new HexDecoder(new StringSink(b64_decoded_cipher)));

    std::cout << "Enter your master key: ";
    std::cin >> keystr;

    if(keystr.size() < 16) {
        keystr.resize(16); // 128 bit key
    } else if(keystr.size() < 24) {
        keystr.resize(24); // 192 bit key
    } else if(keystr.size() < 32) {
        keystr.resize(32); // 256 bit key
    } else {
        // Code for handling too long a key
        std::cout << "Key is invalid." << std::endl;
    }

    key = new SecByteBlock(reinterpret_cast<const byte*>(&keystr[0]), keystr.size());
    iv = new SecByteBlock(reinterpret_cast<const byte*>(&b64_decoded_iv[0]), b64_decoded_iv.size());

    try
    {
        EAX<AES>::Decryption d;
        d.SetKeyWithIV(*key, key->size(), *iv, iv->size());

        ArraySource a((const byte*)&b64_decoded_cipher[0], b64_decoded_cipher.size(), true,
            new AuthenticatedEncryptionFilter(d,
                new StringSink(aes_decoded_plaintext)
            )
        );
    }
    catch(const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    memset_z(&keystr[0], 0, keystr.size());
    memset_z(&b64_decoded_cipher[0], 0, b64_decoded_cipher.size());
    memset_z(&b64_decoded_iv[0], 0, b64_decoded_iv.size());

    aes_decoded_plaintext.resize(*plaintextsize);

    return aes_decoded_plaintext;
}
