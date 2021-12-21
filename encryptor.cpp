// Crypto++ Includes
#include <crypto++/cryptlib.h>
#include <crypto++/rijndael.h>
#include <crypto++/modes.h>
#include <crypto++/files.h>
#include <crypto++/osrng.h>
#include <crypto++/hex.h>
#include <crypto++/misc.h>
#include <cryptopp/eax.h>

#include "headers/encryptor.hpp"

#include <fstream>
#include <iostream>
#include <string>

using namespace CryptoPP;

void Encryptor::getFormatInput() {
    std::cout << "Enter key: " << std::endl;
    std::cin >> keystr;
    std::cout << "Enter text to be encrypted: " << std::endl;
    std::cin >> plaintext;
    keylength = keystr.size();

    // Keystr resizing
    if(keystr.size() < 16) {
        keystr.resize(16); // 128 bit key
    } else if(keystr.size() < 24) {
        keystr.resize(24); // 192 bit key
    } else if(keystr.size() < 32) {
        keystr.resize(32); // 256 bit key
    } else {
        // Code for handling too long a key
        std::cout << "Key is too long." << std::endl;
    }

    // Using key.size instead of keylength var since key has been resized
    key = new SecByteBlock(reinterpret_cast<const byte*>(&keystr[0]), keystr.size());
    iv = new SecByteBlock(AES::BLOCKSIZE*16);

    prng.GenerateBlock(*iv, iv->size());

    // Secure wipe keystr
    memset_z(&keystr[0], 0, keystr.size());
}

void Encryptor::encrypt() {
    try {
        EAX<AES>::Encryption e;
        e.SetKeyWithIV(*key, key->size(), *iv, iv->size());
        StringSource s(plaintext, true, new AuthenticatedEncryptionFilter(e, new StringSink(cipher)));
    } catch(const Exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    // Secure wipe plaintext
    memset_z(&plaintext[0], 0, plaintext.size());
}

// Will store username along with iv-cipher as csv
void Encryptor::store(std::string user, std::string location) {
    std::ofstream fout;

    fout.open("ciphers.txt");
    fout << user << "," << location << ",";
    HexEncoder encoder(new FileSink(fout));
    encoder.Put(*iv, iv->size());
    encoder.Put((const byte*)&cipher[0], cipher.size());
    fout << "\n";
    encoder.MessageEnd();

    fout.close();
}
