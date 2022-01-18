#include <crypto++/cryptlib.h>
#include <crypto++/files.h>
#include <crypto++/hex.h>
#include <crypto++/misc.h>
#include <crypto++/sha.h>

#include "headers/hash.hpp"

using namespace CryptoPP;

// NEED TO ADD SALTING 
static std::string Hash::hash(std::string* input) {
    std::string digest, output;
    HexEncoder encoder(new StringSink(output));

    SHA512 hash;
    hash.Update((const byte*)input->data(), input->size());
    digest.resize(hash.DigestSize());
    hash.Final((byte*)&digest[0]);

    encoder.Put((const byte*)&digest[0], digest.size());
    encoder.MessageEnd();

    return output;
}
