#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <crypto++/aes.h>
#include <crypto++/modes.h>
#include <crypto++/osrng.h>
#include <crypto++/hex.h>
#include <unistd.h>
#include <limits.h>

static inline void (*fun) (std::string filepath);

static inline CryptoPP::SecByteBlock key_0(CryptoPP::AES::DEFAULT_KEYLENGTH);

static inline CryptoPP::byte iv_0[CryptoPP::AES::BLOCKSIZE];

void f_usage();

void f_keygen(std::string &keyFileName);

void f_getKey(std::string keyPath);

std::string f_getcwd();

void  f_iterator(std::string targetPath);

void  f_encryptor(std::string filepath);

void  f_decryptor(std::string filepath);
