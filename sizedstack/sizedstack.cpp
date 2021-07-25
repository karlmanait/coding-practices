template <class T>
class SizedStack
{
public:
    SizedStack(int size)
    : m_count(0)
    , m_size(size)
    {
        m_data = new T[size];
    }

    ~SizedStack()
    {
        delete [] m_data;
    }

    void push(const T data)
    {
        if (m_count == m_size)
        {
            throw "SizedStack is full";
        }
        m_data[m_count++] = data;
    }

    T pop()
    {
        if (!m_count)
        {
            throw "SizedStack is empty";
        }
        return m_data[--m_count];
    }

private:
    T* m_data;
    int m_count;
    int m_size;
};
