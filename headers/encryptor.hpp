#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

// Crypto++ Includes
#include <crypto++/cryptlib.h>
#include <crypto++/rijndael.h>
#include <crypto++/modes.h>
#include <crypto++/files.h>
#include <crypto++/osrng.h>
#include <crypto++/hex.h>
#include <crypto++/misc.h>
#include <cryptopp/eax.h>

class Encryptor {
    private:
        CryptoPP::SecByteBlock* key;
        CryptoPP::SecByteBlock* iv;
        int keylength;
        size_t plaintextsize;
        std::string keystr, plaintext, cipher;
        CryptoPP::AutoSeededRandomPool prng;

    public:
        int getFormatInput();
        int encrypt();
        int store(std::string, std::string, std::string);
};

#endif
