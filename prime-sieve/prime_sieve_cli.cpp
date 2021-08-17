#include <iostream>
#include <cstdlib>
#include "prime_sieve.cpp"

int main(int argc, char** argv)
{
    if (argc >= 2)
    {
        uint64_t values[argc - 1];
        for (int i = 1; i < argc; ++i)
        {
            values[i - 1] = strtoull(argv[i], nullptr, 0);
        }

        uint64_t max = 0;
        for (int i = 0; i < argc - 1; ++i)
        {
            if (values[i] > max)
                max = values[i];
        }

        PrimeSieve sieve(max);
        for (int i = 0; i < argc - 1; ++i)
        {
            bool is_prime = sieve.is_prime(values[i]);
            std::cout << values[i] << " is" << (is_prime ? "" : " not") << " a prime number\n";
        }
    }
    return 0;
}
