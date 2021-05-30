template <class T>
class PriorityQueue
{
private:
    struct node
    {
        T data;
        int prio;
        node* next;
        node* prev;
    };

public:
    PriorityQueue()
    {
        // pivot point for new entries, does not contain actual data
        m_pivot = new node{T(), (1 << 31), nullptr, nullptr};
        m_pivot->next = m_pivot;
        m_pivot->prev = m_pivot;
    }

    ~PriorityQueue()
    {
        for (node* iter = m_pivot->next; iter != m_pivot; iter = m_pivot->next)
        {
            iter->prev->next = iter->next;
            iter->next->prev = iter->prev;
            delete iter;
        }
        delete m_pivot;
    }

    bool empty()
    {
        return m_pivot->next == m_pivot;
    }

    void push(int prio, const T data)
    {
        node* new_node = new node{data, prio, nullptr, nullptr};
        for (node* iter = m_pivot->next; true; iter = iter->next)
        {
            // higher priority gets push on top
            if (prio > iter->prio || iter == m_pivot)
            {
                new_node->prev = iter->prev;
                new_node->next = iter;
                new_node->prev->next = new_node;
                new_node->next->prev = new_node;
                return;
            }
        }
    }

    T pop()
    {
        if (empty())
        {
            throw "PriorityQueue is empty";
        }
        node* iter = m_pivot->next;
        T tmp = iter->data;
        iter->prev->next = iter->next;
        iter->next->prev = iter->prev;
        delete iter;
        return tmp;
    }

private:
    node* m_pivot;
};
