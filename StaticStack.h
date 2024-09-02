#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "Stack.h"
#include "Exception.h"

namespace ZTYLib
{

template <typename T, int N>
class StaticStack : public Stack<T>
{
protected:
    T m_space[N];  //栈存储空间
    int m_top;      //栈顶标识
    int m_size;     //当前栈的大小
public:
    StaticStack()
    {
        m_top = -1;
        m_size = 0;
    }
    int capacity() const
    {
        return N;
    }

    void push(const T& e)
    {
        if(m_size < N)
        {
            //这里不直接使用m_top++来做，是为了异常安全
            //e为泛指类型，如果出现异常，栈内部的状态不应该改变
            m_space[m_top+1] = e;
            m_top++;
            m_size++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current stack...");
        }
    }

    void pop()
    {
        if(m_size > 0)
        {
            m_size--;
            m_top--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack...");
        }
    }

    T top() const
    {
        if(m_size > 0)
        {
            return m_space[m_top];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack...");
        }
    }

    void clear()
    {
        m_top = -1;
        m_size = 0;
    }

    int size() const
    {
        return m_size;
    }


};

}

#endif // STATICSTACK_H
