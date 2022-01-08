#include <crypto++/cryptlib.h>
#include <crypto++/files.h>
#include <crypto++/hex.h>
#include <crypto++/misc.h>
#include <crypto++/sha.h>

#include "headers/hash.hpp"

using namespace CryptoPP;


std::string Hash::hash(std::string* input) {
    HexEncoder encoder(new FileSink(std::cout))
    std::string digest;

    return output;
}
