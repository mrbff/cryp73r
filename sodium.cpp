#include <sodium.h>
#include <iostream>
#include <fstream>
#include <vector>

void encrypt_file(const std::string& input_filename, const std::string& output_filename, const unsigned char* key) {
    std::ifstream infile(input_filename, std::ios::binary);
    std::ofstream outfile(output_filename, std::ios::binary);

    if (!infile || !outfile) {
        std::cerr << "Cannot open file!" << std::endl;
        return;
    }

    std::vector<unsigned char> nonce(crypto_secretbox_NONCEBYTES);
    randombytes_buf(nonce.data(), nonce.size());

    outfile.write(reinterpret_cast<const char*>(nonce.data()), nonce.size());

    std::vector<unsigned char> buffer(4096);
    std::vector<unsigned char> encrypted_buffer(4096 + crypto_secretbox_MACBYTES);

    while (infile.read(reinterpret_cast<char*>(buffer.data()), buffer.size())) {
        std::streamsize count = infile.gcount();

        if (crypto_secretbox_easy(encrypted_buffer.data(), buffer.data(), count, nonce.data(), key) != 0) {
            std::cerr << "Encryption failed!" << std::endl;
            return;
        }

        outfile.write(reinterpret_cast<const char*>(encrypted_buffer.data()), count + crypto_secretbox_MACBYTES);
    }
}

void decrypt_file(const std::string& input_filename, const std::string& output_filename, const unsigned char* key) {
    std::ifstream infile(input_filename, std::ios::binary);
    std::ofstream outfile(output_filename, std::ios::binary);

    if (!infile || !outfile) {
        std::cerr << "Cannot open file!" << std::endl;
        return;
    }

    std::vector<unsigned char> nonce(crypto_secretbox_NONCEBYTES);
    infile.read(reinterpret_cast<char*>(nonce.data()), nonce.size());

    std::vector<unsigned char> encrypted_buffer(4096 + crypto_secretbox_MACBYTES);
    std::vector<unsigned char> decrypted_buffer(4096);

    while (infile.read(reinterpret_cast<char*>(encrypted_buffer.data()), encrypted_buffer.size())) {
        std::streamsize count = infile.gcount();

        if (crypto_secretbox_open_easy(decrypted_buffer.data(), encrypted_buffer.data(), count, nonce.data(), key) != 0) {
            std::cerr << "Decryption failed!" << std::endl;
            return;
        }

        outfile.write(reinterpret_cast<const char*>(decrypted_buffer.data()), count - crypto_secretbox_MACBYTES);
    }
}

int main() {
    if (sodium_init() < 0) {
        std::cerr << "Libsodium initialization failed" << std::endl;
        return 1;
    }

    unsigned char key[crypto_secretbox_KEYBYTES];
    randombytes_buf(key, sizeof key);

    encrypt_file("plain.txt", "encrypted.txt", key);
    decrypt_file("encrypted.txt", "decrypted.txt", key);

    return 0;
}
