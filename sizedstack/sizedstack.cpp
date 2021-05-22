#include <iostream>

template <class T>
class SizedStack
{
public:
    SizedStack(int size)
    : m_size(0)
    {
        m_data = new T[size];
    }

    ~SizedStack()
    {
        delete [] m_data;
    }

    void push(const T data)
    {
        m_data[m_size++] = data;
    }

    bool empty()
    {
        return !m_size;
    }

    T pop()
    {
        if (empty())
        {
            throw "SizedStack is empty";
        }
        return m_data[--m_size];
    }

private:
    T* m_data;
    int m_size;
};
