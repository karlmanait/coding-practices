#include <iostream>

template <class T>
class List
{
public:
    struct iterator
    {
        T data;
        iterator* next;
        iterator* prev;
    };

    List()
    : m_pivot(nullptr)
    {
        // Pivot point for new entries, does not contain actual data
        m_pivot = new iterator{T(), nullptr, nullptr};
        m_pivot->next = m_pivot;
        m_pivot->prev = m_pivot;
    }

    ~List()
    {
        while (m_pivot == m_pivot->next)
        {
            iterator* tmp = m_pivot->next;
            delete m_pivot;
            m_pivot = tmp;
        }
    }

    iterator* begin()
    {
        return m_pivot->next;
    }

    iterator* end()
    {
        return m_pivot;
    }

    void insert(const T data)
    {
        iterator* new_iterator = new iterator{data, nullptr, nullptr};
        new_iterator->prev = m_pivot->prev;
        new_iterator->next = m_pivot;
        new_iterator->prev->next = new_iterator;
        new_iterator->next->prev = new_iterator;
    }

    void remove(iterator* iter)
    {
        iter->prev->next = iter->next;
        iter->next->prev = iter->prev;
    }


private:
    iterator* m_pivot;
};
