typedef unsigned char uint8_t;

class Bitset
{
public:
    Bitset(int size)
    {
        m_data = new uint8_t[(size + 7)/8];
    }

    ~Bitset()
    {
        delete [] m_data;
    }

    void set(int index, bool data)
    {
        int byte_index = index/8;
        int bit_index = index % 8;
        // set bit to 0, then OR it to 'data'
        m_data[byte_index] = ((m_data[byte_index] & ~(1 << bit_index)) | (data << bit_index));
    }

    bool operator[](int index)
    {
        int byte_index = index/8;
        int bit_index = index % 8;
        return m_data[byte_index] & (1 << bit_index);
    }

private:
    uint8_t* m_data;
};

