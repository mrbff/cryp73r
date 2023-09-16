#include "cryp73r.hpp"

int main(int ac, char **av)
{
    if (ac < 2)
        f_usage();
    
    std::string mode(av[1]);

    if (mode == "-k")
    {
        std::string keyFileName((ac < 3 || av[3] == NULL) ? "keyFile.key" : av[3]);
        f_keygen(keyFileName);
    }
    else if (ac < 3)
        f_usage();
    else if (mode == "-e")
        fun = f_encryptor;
    else if (mode == "-d")
        fun = f_decryptor;
    else
        f_usage();

    f_getKey(av[2]);

//    std::string target = (ac < 4) ? f_getcwd() : av[3];
//    std::cout << av[3] << std::endl;
    f_iterator(/*(ac < 4) ? f_getcwd() : */av[3]);

    return 0;
}