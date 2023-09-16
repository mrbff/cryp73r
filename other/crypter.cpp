#include <iostream>
#include <string>
#include <fstream>
#include <crypto++/aes.h>
#include <crypto++/modes.h>
#include <crypto++/osrng.h>
#include <crypto++/hex.h>

int main(int ac, char* av[]) {
    
    std::string filepath = av[1];
    std::ifstream file_in(filepath);
    
    if (!file_in.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }
    
    if (ac < 3) {
        std::cerr << "No key path provided" << std::endl;
        return 2;
    }

    CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];

    std::ifstream keyFile((std::string)av[2], std::ios::binary);
    if (!keyFile.is_open()) {
        std::cerr << "Failed to open key file" << std::endl;
        return 3;
    }
    keyFile.read(reinterpret_cast<char*>(key.BytePtr()), key.size());
    keyFile.read(reinterpret_cast<char*>(iv), sizeof(iv));
    keyFile.close();

    std::string content((std::istreambuf_iterator<char>(file_in)), (std::istreambuf_iterator<char>()));
    file_in.close();
    std::string ciphertext;

    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);

    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
    stfEncryptor.Put(reinterpret_cast<const unsigned char*>(content.c_str()), content.length() + 1);
    stfEncryptor.MessageEnd();

    std::ofstream file_out(filepath);
    file_out << ciphertext;
    file_out.close();

    std::cout << "File encrypted successfully!" << std::endl;

    return 0;
}
