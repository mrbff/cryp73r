#include "cryp73r.hpp"

CryptoPP::SecByteBlock key_0(CryptoPP::AES::DEFAULT_KEYLENGTH);
CryptoPP::byte iv_0[CryptoPP::AES::BLOCKSIZE];

void f_usage()
{
    std::cout << "./cryp73r [-k generate random encryption key] 'keyFileName.key' [optional]" << std::endl;
    std::cout << "./cryp73r [-e  encryption mode][-d  decryption mode] './path/to/encryptionKey.key' './path/to/directoryOrFile' [optional, start from current dir by default]" << std::endl;
    exit(1);
}

void f_keygen(std::string &keyFileName)
{
    CryptoPP::AutoSeededRandomPool rnd;

    CryptoPP::SecByteBlock key(0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
    rnd.GenerateBlock(key, key.size());

    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
    rnd.GenerateBlock(iv, sizeof(iv));

    std::ofstream keyFile(keyFileName, std::ios::binary);
    if(keyFile.is_open()) {
        keyFile.write(reinterpret_cast<const char*>(key.BytePtr()), key.size());
        keyFile.write(reinterpret_cast<const char*>(iv), sizeof(iv));
        keyFile.close();
    } else {
        std::cerr << "Could not open key file for writing." << std::endl;
        exit(1);
    }
    std::cerr << "Encryption key correctly generated." << std::endl;
    exit(0);
}

void f_getKey(std::string keyPath)
{
    std::ifstream keyFile(keyPath, std::ios::binary);
    if (!keyFile.is_open()) {
        std::cerr << "Failed to open key file" << std::endl;
        exit(1);
    }
    keyFile.read(reinterpret_cast<char*>(key_0.BytePtr()), key_0.size());
    keyFile.read(reinterpret_cast<char*>(iv_0), sizeof(iv_0));
    keyFile.close();
}

std::string f_getcwd()
{
    char cwd[PATH_MAX];
    
   if (getcwd(cwd, sizeof(cwd)) == NULL) {
        std::cerr << "getcwd() error" << std::endl;
        exit(1);
    }

    std::string wd(cwd);
    return wd;
}