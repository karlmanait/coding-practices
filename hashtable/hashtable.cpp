#include <iostream>

typedef unsigned int uint32_t;

#define SIZE 16

template <class T>
class Hashtable
{
private:
    struct bucket
    {
        char* key;
        T value;
        bucket* next;
    };

public:
    Hashtable()
    : m_buckets()
    {
    }

    ~Hashtable()
    {
        for (int i = 0; i < SIZE; ++i)
        {
            while (m_buckets[i])
            {
                bucket* tmp = m_buckets[i]->next;
                delete m_buckets[i];
                m_buckets[i] = tmp;
            }
        }
    }

    uint32_t hashfunc(char* key)
    {
        uint32_t hashval = 0;
        uint32_t factor = 0b0101;
        for (char* c = key; *c; c++)
        {
            hashval += (*c)*factor;
            factor <<= 1;
        }
        return hashval;
    }

    bool str_eq(char* str1, char* str2)
    {
        while (*str1 && *str2)
        {
            if ((*str1) != (*str2))
            {
                return false;
            }
            str1++;
            str2++;
        }
        return (!(*str1) && !(*str2));
    }

    bucket* find(char* key)
    {
        uint32_t index = hashfunc(key) % SIZE;
        for (bucket* iter = m_buckets[index]; iter; iter = iter->next)
        {
            if (str_eq(key, iter->key))
            {
                return iter;
            }
        }
        return nullptr;
    }

    T operator[](char* key)
    {
        bucket* b = find(key);
        if (!b)
        {
            throw "Key not found";
        }
        return b->value;
    }

    void set(char* key, T value)
    {
        uint32_t index = hashfunc(key) % SIZE;
        bucket* b = find(key);
        if (!b)
        {
            bucket* new_bucket = new bucket{key, value, nullptr};
            if (m_buckets[index])
            {
                new_bucket->next = m_buckets[index];
            }
            m_buckets[index] = new_bucket;
        }
        else
        {
            b->value = value;
        }
    }

private:
    bucket* m_buckets[SIZE];
};
