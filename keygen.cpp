#include <iostream>
#include <string>
#include <fstream>
#include <crypto++/aes.h>
#include <crypto++/modes.h>
#include <crypto++/osrng.h>
#include <crypto++/hex.h>

int main(int ac, char **av) {
    CryptoPP::AutoSeededRandomPool rnd;

    CryptoPP::SecByteBlock key(0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
    rnd.GenerateBlock(key, key.size());

    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
    rnd.GenerateBlock(iv, sizeof(iv));

    std::ofstream keyFile("keyfile.key", std::ios::binary);
    if(keyFile.is_open()) {
        keyFile.write(reinterpret_cast<const char*>(key.BytePtr()), key.size());
        keyFile.write(reinterpret_cast<const char*>(iv), sizeof(iv));
        keyFile.close();
    } else {
        std::cerr << "Could not open key file for writing." << std::endl;
        return 1;
    }
    std::cerr << "Encryption key correctly generated." << std::endl;
    return 0;
}
