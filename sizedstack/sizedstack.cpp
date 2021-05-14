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

    T pop()
    {
        if (!m_size)
        {
            return T();
        }
        return m_data[--m_size];
    }

private:
    T* m_data;
    int m_size;
};
