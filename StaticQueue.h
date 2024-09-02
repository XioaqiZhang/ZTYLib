#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include "Queue.h"
#include "Exception.h"

namespace ZTYLib
{

template <typename T, int N>
class StaticQueue : public Queue<T>
{
protected:
    T m_spcae[N];
    int m_front;
    int m_rear;
    int m_length;
public:
    StaticQueue()
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }

    int capacity() const
    {
        return N;
    }

    void add(const T& e)
    {
        if(m_length < N)
        {
            m_spcae[m_rear] = e;
            m_rear = (m_rear + 1)%N;
            m_length++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current Queue...");
        }
    }

    void remove()
    {
        if(m_length > 0)
        {
            m_front = (m_front + 1)%N;
            m_length--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current Queue...");
        }
    }

    T front() const
    {
        if(m_length > 0)
        {
            return m_spcae[m_front];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current Queue...");
        }
    }

    int length() const
    {
        return m_length;
    }

    void clear()
    {
        m_length = 0;
        m_front = 0;
        m_rear = 0;
    }

};

}

#endif // STATICQUEUE_H
