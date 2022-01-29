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

int Encryptor::getFormatInput() {
    std::cout << "\nEnter your password: ";
    std::cin >> plaintext;
    std::cout << "\nEnter your master key: ";
    std::cin >> keystr;
    std::cout << std::endl;

    keylength = keystr.size();
    plaintextsize = plaintext.size();

    // Keystr validation and resizing
    if(keystr.size() == 0) {
        return 0;
    }

    if(keystr.size() < 16) {
        keystr.resize(16); // 128 bit key
    } else if(keystr.size() < 24) {
        keystr.resize(24); // 192 bit key
    } else if(keystr.size() < 32) {
        keystr.resize(32); // 256 bit key
    } else {
        // Code for handling too long a key
        return 0;
    }

    // Using key.size instead of keylength var since key has been resized
    key = new SecByteBlock(reinterpret_cast<const byte*>(&keystr[0]), keystr.size());
    iv = new SecByteBlock(AES::BLOCKSIZE*16);

    prng.GenerateBlock(*iv, iv->size());

    // Secure wipe keystr
    memset_z(&keystr[0], 0, keystr.size());

    return 1;
}

int Encryptor::encrypt() {
    try {
        EAX<AES>::Encryption e;
        e.SetKeyWithIV(*key, key->size(), *iv, iv->size());
        StringSource s(plaintext, true, new AuthenticatedEncryptionFilter(e, new StringSink(cipher)));
    } catch(const Exception& e) {
        return 0;
    }
    // Secure wipe plaintext
    memset_z(&plaintext[0], 0, plaintext.size());

    return 1;
}

// Will store username along with iv-cipher as csv
int Encryptor::store(std::string user, std::string target_loc_user, std::string location) {
    std::ofstream fout;

    fout.open("ciphers.txt", std::ios_base::app);
    if(!fout) {
        std::cout << "Could not open ciphers.txt." << std::endl;
        return 0;
    }

    fout << user << "," << target_loc_user << "," << location << "," << plaintextsize << ",";
    HexEncoder encoder(new FileSink(fout));
    encoder.Put(*iv, iv->size());
    fout << ",";
    encoder.Put((const byte*)&cipher[0], cipher.size());
    fout << "\n";
    encoder.MessageEnd();

    delete key;
    delete iv;
    plaintextsize = 0;

    fout.close();
    return 1;
}
