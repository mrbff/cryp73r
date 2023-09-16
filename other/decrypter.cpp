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

    CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];

    std::ifstream keyFile((std::string)av[2], std::ios::binary);
    if (!keyFile.is_open()) {
        std::cerr << "Failed to open key file" << std::endl;
        return 1;
    }
    keyFile.read(reinterpret_cast<char*>(key.BytePtr()), key.size());
    keyFile.read(reinterpret_cast<char*>(iv), sizeof(iv));
    keyFile.close();


    std::string ciphertext((std::istreambuf_iterator<char>(file_in)), (std::istreambuf_iterator<char>()));
    file_in.close();
    std::string decryptedtext;

    CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);

    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
    stfDecryptor.Put(reinterpret_cast<const unsigned char*>(ciphertext.c_str()), ciphertext.size());
    stfDecryptor.MessageEnd();

    std::ofstream file_out(filepath);
    file_out << decryptedtext;
    file_out.close();

    std::cout << "File decrypted, hopefully.." << std::endl;

    return 0;
}
