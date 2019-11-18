#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"

namespace ZTYLib
{
template <typename T>
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity; //顺序存储空间的大小
public:
    DynamicList(int capacity) //申请空间
    {
        this->m_array = new T[capacity];

        if(this->m_array != NULL)
        {
            this->m_length = 0;
            this->m_capacity = capacity;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No memory to create DynamicList Object...");
        }
    }
    int capacity() const
    {
        return m_capacity;
    }
    void resize(int capacity)// 重新设置顺序存储空间大小
    {
        if(capacity != m_capacity)
        {
            //重新申请一片连续的堆空间
            T* array = new T[capacity];

            if(array != NULL)
            {
                // 得到重置后的长度
                int length = (this->m_length < capacity ? this->m_length : capacity);

                for(int i=0; i<this->m_length; i++)
                {
                    // 将旧数据复制到新申请的堆空间中去
                    array[i] = this->m_array[i];
                }

                // 临时指针用于最后释放旧的被占用的堆空间
                T* temp = this->m_array;

                this->m_array = array;
                this->m_length = length;
                this->m_capacity = capacity;

                //释放旧的被占用的堆空间
                delete[] temp;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new capacity");
            }
        }
    }
    ~DynamicList()  //归还空间
    {
        delete[] this->m_array;
    }
};
}

#endif // DYNAMICLIST_H
