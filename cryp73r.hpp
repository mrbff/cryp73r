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
#include <dirent.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>

extern void (*fun) (std::string filepath);

extern CryptoPP::SecByteBlock key_0;

extern CryptoPP::byte iv_0[CryptoPP::AES::BLOCKSIZE];

void f_usage();

void f_keygen(std::string &keyFileName);

void f_getKey(std::string keyPath);

std::string f_getcwd();

void  f_iterator(std::string targetPath);

void  f_encryptor(std::string filepath);

void  f_decryptor(std::string filepath);
