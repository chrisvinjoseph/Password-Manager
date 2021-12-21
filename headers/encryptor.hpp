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
        int keylength;
        std::string keystr, plaintext, cipher, recovered;
        CryptoPP::SecByteBlock* key;
        CryptoPP::SecByteBlock* iv;
        CryptoPP::AutoSeededRandomPool prng;

    public:
        void getFormatInput();
        void encrypt();
        void store();
};

#endif
