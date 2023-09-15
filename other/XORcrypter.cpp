#include <iostream>
#include <fstream>
#include <string>

std::string xor_encrypt(const std::string &input, char key) {
    std::string output;
    output.resize(input.size());

    for (std::size_t i = 0; i < input.size(); i++) {
        output[i] = input[i] ^ key;
    }

    return output;
}

int main(int ac, char **av) {
    char key = 'A'; // Choose your encryption key
    std::string filepath = av[1];
    std::ifstream file_in(filepath);
    
    if (!file_in.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }
    
    std::string content((std::istreambuf_iterator<char>(file_in)), (std::istreambuf_iterator<char>()));
    file_in.close();
    
    std::string encrypted_content = xor_encrypt(content, key);
    
    std::ofstream file_out(filepath);
    if (!file_out.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }
    
    file_out << encrypted_content;
    file_out.close();
    
    std::cout << "File encrypted successfully!" << std::endl;
    return 0;
}