#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "LinkList.h"

namespace ZTYLib
{
template <typename T>
class CircleList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

    int mod(int i) const
    {
        return ((this->m_length ==0) ? 0 : (i%(this->m_length)));

    }
    Node* last() const
    {
        return this->position(this->m_length-1)->Next;

    }
    void last_to_first() const
    {
        last()->Next = this->m_header.Next;
    }
public:
    bool insert(const T& e)
    {
        return insert(this->m_length, e);
    }
    bool insert(int i, const T& e)
    {
        bool ret = true;

        //这里取余是为了循环归1，但是为什么要加1？
        //因为下面需要调用父类单链表的insert函数，加入长度为3，目标位置为4，
        //加1的情况则是在0位置插入，不加1则是在1的位置插入，
        //前者和最初的目的一样，后者则不一样了
        i = i % (this->m_length + 1);

        ret = LinkList<T>::insert(i,e);

        if(ret && (i == 0))
        {
            last_to_first();
        }

        return ret;
    }
    bool remove(int i)
    {
        bool ret = true;

        i = mod(i);

        if(i == 0)
        {
            Node* toDel = this->m_header.Next;

            if(toDel != NULL)
            {
                this->m_header.Next = toDel->Next;
                this->m_length--;

                if(this->m_length > 0)
                {
                    last_to_first();

                    if(this->m_current == toDel)
                    {
                        this->m_current = toDel->Next;
                    }
                }
                else
                {
                    this->m_header.Next = NULL;
                    this->m_current = NULL;
                }

                this->destroy(toDel);
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = LinkList<T>::remove(i);
        }
        return ret;
    }

    bool set(int i, const T& e)
    {
        return LinkList<T>::set(mod(i), e);
    }

    T get(int i) const
    {
        return LinkList<T>::get(mod(i));
    }

    bool get(int i, const T& e) const
    {
        return LinkList<T>::get(mod(i), e);
    }

    int find(const T& e) const
    {
        int ret = -1;

        Node* slider = this->m_header.Next;

        for(int i=0; i<this->m_length; i++)
        {
            if(slider->value == e)
            {
                ret = i;
                break;
            }
            slider = slider->Next;
        }

        return ret;
    }

    void clear()
    {
        while(this->m_length > 1)
        {
            remove(1);
        }

        if(this->m_length == 1)
        {
            Node* toDel = this->m_header.Next;

            this->m_header.Next = NULL;
            this->m_length = 0;
            this->m_current = NULL;

            this->destroy(toDel);
        }

    }

    bool move(int i, int step)
    {
        return LinkList<T>::move(mod(i), step);
    }

    bool end()
    {
        return ((this->m_length == 0) || (this->m_current == NULL));
    }


    ~CircleList()
    {
        clear();
    }

};
}

#endif // CIRCLELIST_H
