#ifndef LINKLIST_H
#define LINKLIST_H
#include "List.h"
#include "Exception.h"
#include <iostream>

using namespace std;

namespace ZTYLib
{
template <typename T>
class LinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* Next;
    };
//mutable Node m_header;
    mutable struct : public Object{
        char reserved[sizeof(T)];
        Node* Next;
    } m_header;

    int m_length;
    int m_step;
    Node* m_current;

    Node* position(int i) const
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);

        for(int p=0; p<i; p++)
        {
            ret = ret->Next;
        }

        return ret;
    }

    virtual Node* create()
    {
        return new Node();
    }
    virtual void destroy(Node* pn)
    {
        delete pn;
    }
public:
    LinkList()
    {
        m_header.Next = NULL;
        m_length = 0;
        m_step = 1;
        m_current = NULL;
    }
    bool insert(const T& e)
    {
        return insert(m_length,e);
    }
    bool insert(int i, const T& e)
    {
        bool ret = ((0 <= i) && (i <= m_length));
        if(ret)
        {
            Node* node = create();

            if(node != NULL)
            {
                Node* current = position(i);

                node->value = e;
                node->Next = current->Next;
                current->Next = node;
                m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"No memory to insert new element ...");
            }

        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBounds, "inedx is out of list bounds ...");
        }

        return ret;
    }
    bool remove(int i)
    {
        bool ret = ((0 <= i) && (i < m_length));

        if(ret)
        {
            Node* current = position(i);

            Node* toDel = current->Next;
            current->Next = toDel->Next;
            destroy(toDel);
            m_length--;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBounds, "index is out of list bounds ...");
        }

        return ret;
    }
    bool set(int i, const T& e)
    {
        bool ret = ((0 <= i) && (i < m_length));
        if(ret)
        {
            position(i)->Next->value = e;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBounds, "index is out of list bounds ...");
        }
        return ret;
    }

    T get(int i)
    {
        T ret;

        if(get(i,ret))
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBounds, "Invalid parameter i to get element ...");
        }

        return ret;
    }
    bool get(int i, T& e) const
    {
        bool ret = ((0 <= i) && (i < m_length));
        if(ret)
        {
            e = position(i)->Next->value;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBounds, "index is out of list bounds ...");
        }
        return ret;
    }
    int find(const T& e) const
    {
        int ret = -1;
        int i=0;
        Node* node = m_header.Next;

        while(node)
        {
            if(node->value == e)
            {
                ret = i;
                break;
            }
            else
            {
                node = node->Next;
                i++;
            }
        }

        return ret;
    }
    int length() const
    {
        return m_length;
    }
    void clear()
    {
        while(m_header.Next)
        {
            Node* toDel = m_header.Next;
            m_header.Next = toDel->Next;
            destroy(toDel);
        }
    }
    bool move(int i, int step = 1)
    {
        bool ret = ((0 <= i) && (i < m_length) && (0 < step));

        if(ret)
        {
            m_current = position(i)->Next;
            m_step = step;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBounds, "index is out of list bounds ...");
        }
        return ret;
    }
    bool end()
    {
        return (m_current == NULL);
    }
    T current()
    {
        if(!end())
        {
            return m_current->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
        }
    }
    bool next()
    {
        int i=0;

        while((i < m_step) && (!end()))
        {
            m_current = m_current->Next;
            i++;
        }

        return (i == m_step);
    }
    ~LinkList()
    {
        clear();
    }
};

}

#endif // LINKLIST_H
