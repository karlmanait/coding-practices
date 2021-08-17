#include <cstdint>

class PrimeSieve
{
public:
    PrimeSieve(uint64_t size)
    : m_start(2)
    , m_size(size)
    , m_list_primes(nullptr)
    {
        m_not_prime = new bool[size]();
        for (uint64_t i = m_start; i <= size; ++i)
        {
            if (!m_not_prime[i - m_start])
            {
                for (uint64_t j = m_start; i*j <= size; ++j)
                {
                    m_not_prime[i*j - m_start] = true;
                }
            }
        }
    }

    ~PrimeSieve()
    {
        delete [] m_not_prime;
        delete [] m_list_primes;
    }

    bool is_prime(uint64_t number)
    {
        if (number < m_start)
            return false;
        if (number > m_size)
            throw "Primeness was not pre-computed";
        return !m_not_prime[number - m_start];
    }

    uint64_t* list_primes()
    {
        if (!m_list_primes)
        {
            m_list_primes = new uint64_t[m_size]();
            uint64_t ctr = 0;
            for (uint64_t i = 0; i <= m_size; ++i)
            {
                if (is_prime(i))
                    m_list_primes[ctr++] = i;
            }
        }
        return m_list_primes;
    }

private:
    const uint64_t m_start;
    const uint64_t m_size;
    bool* m_not_prime;
    uint64_t* m_list_primes;
};

