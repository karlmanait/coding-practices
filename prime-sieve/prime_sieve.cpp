class PrimeSieve
{
public:
    PrimeSieve(int size)
    : m_start(2)
    , m_size(size)
    , m_list_primes(nullptr)
    {
        m_not_prime = new bool[size]();
        for (int i = m_start; i <= size; ++i)
        {
            if (!m_not_prime[i - m_start])
            {
                for (int j = m_start; i*j <= size; ++j)
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

    bool is_prime(int number)
    {
        if (number < m_start)
            return false;
        if (number > m_size)
            throw "Primeness was not pre-computed";
        return !m_not_prime[number - m_start];
    }

    int* list_primes()
    {
        if (!m_list_primes)
        {
            m_list_primes = new int[m_size]();
            int ctr = 0;
            for (int i = 0; i <= m_size; ++i)
            {
                if (is_prime(i))
                    m_list_primes[ctr++] = i;
            }
        }
        return m_list_primes;
    }

private:
    const int m_start;
    const int m_size;
    bool* m_not_prime;
    int* m_list_primes;
};

