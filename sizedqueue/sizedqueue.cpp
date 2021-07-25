template <class T>
class SizedQueue
{
public:
    SizedQueue(int size)
    : m_head(0)
    , m_tail(0)
    , m_count(0)
    , m_size(size)
    {
        m_data = new T[size];
    }

    ~SizedQueue()
    {
        delete [] m_data;
    }

    void push(const T data)
    {
        if (m_count == m_size)
        {
            throw "SizedQueue is full";
        }
        m_count++;
        if (m_tail == m_size)
        {
            m_tail = 0;
        }
        m_data[m_tail++] = data;
    }

    T pop()
    {
        if (!m_count)
        {
            throw "SizedQueue is empty";
        }
        m_count--;
        if (m_head == m_size)
        {
            m_head = 0;
        }
        return m_data[m_head++];
    }

private:
    T* m_data;
    int m_head;
    int m_tail;
    int m_count;
    int m_size;
};
