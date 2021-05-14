#include <iostream>

template <class T>
class SizedQueue
{
public:
    SizedQueue(int size)
    : m_head(0)
    , m_tail(0)
    {
        m_data = new T[size];
    }

    ~SizedQueue()
    {
        delete [] m_data;
    }

    void push(const T data)
    {
        m_data[m_tail++] = data;
    }

    T pop()
    {
        if (m_tail <= m_head)
        {
            return T();
        }
        return m_data[m_head++];
    }

private:
    T* m_data;
    int m_head;
    int m_tail;
};
