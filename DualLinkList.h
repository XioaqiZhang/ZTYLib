﻿#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

#include "List.h"
#include "Exception.h"

namespace ZTYLib
{
template <typename T>
class DualLinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* Next;
        Node* pre;
    };
//mutable Node m_header;
    mutable struct : public Object{
        char reserved[sizeof(T)];
        Node* Next;
        Node* pre;
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
    DualLinkList()
    {
        m_header.Next = NULL;
        m_header.pre = NULL;
        m_length = 0;
        m_step = 1;
        m_current = NULL;
    }

    virtual bool insert(const T& e)
    {
        return insert(m_length,e);
    }

    virtual bool insert(int i, const T& e)
    {
        bool ret = ((0 <= i) && (i <= m_length));
        if(ret)
        {
            Node* node = create();

            if(node != NULL)
            {
                Node* current = position(i);
                Node* next = current->Next;

                node->value = e;

                node->Next = next;
                current->Next = node;

                if(current != reinterpret_cast<Node*>(&m_header))
                {
                    node->pre = current;
                }
                else
                {
                    node->pre = NULL;
                }

                if(next != NULL)
                {
                    next->pre = node;
                }

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

    virtual bool remove(int i)
    {
        bool ret = ((0 <= i) && (i < m_length));

        if(ret)
        {
            Node* current = position(i);
            Node* toDel = current->Next;
            Node* next = toDel->Next;

            if(m_current == toDel)
            {
                m_current = next;
            }

            current->Next = next;

            if(next != NULL)
            {
                next->pre = current;
            }

            m_length--;

            destroy(toDel);
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBounds, "index is out of list bounds ...");
        }

        return ret;
    }

    virtual bool set(int i, const T& e)
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

    virtual T get(int i) const
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

    virtual bool get(int i, T& e) const
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

    virtual int find(const T& e) const
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
        while(m_length > 0)
        {
            remove(0);
        }
    }

    virtual bool move(int i, int step = 1)
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

    virtual bool end()
    {
        return (m_current == NULL);
    }

    virtual T current()
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

    virtual bool next()
    {
        int i=0;

        while((i < m_step) && (!end()))
        {
            m_current = m_current->Next;
            i++;
        }

        return (i == m_step);
    }

    virtual bool pre()
    {
        int i=0;

        while((i < m_step) && (!end()))
        {
            m_current = m_current->pre;
            i++;
        }

        return (i == m_step);

    }

    ~DualLinkList()
    {
        clear();
    }
};

}



#endif // DUALLINKLIST_H
