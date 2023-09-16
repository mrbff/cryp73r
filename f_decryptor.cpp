#include "cryp73r.hpp"

void  f_decryptor(std::string filepath) {

    std::ifstream file_in(filepath);
    
    if (!file_in.is_open()) {
        std::cerr << "Failed to open " + filepath << std::endl;
        return ;
    }

    CryptoPP::SecByteBlock key(key_0);
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
    for (int i = 0; i < CryptoPP::AES::BLOCKSIZE; i++)
        iv[i] = iv_0[i];

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

    std::cout << filepath + " decrypted, hopefully.." << std::endl;

}