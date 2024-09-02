#ifndef DUALSTATICLINKLIST_H
#define DUALSTATICLINKLIST_H

#include "DualLinkList.h"

namespace ZTYLib
{

template <typename T, int N>
class DualStaticLinkList : public DualLinkList<T>
{
protected:
    typedef typename DualLinkList<T>::Node Node;

    struct DSNode : public Node
    {
        void* operator new(unsigned int size, void* loc)
        {
            (void)size;
            // 将内存地址返回，用于调用存储数据对象的构造函数
            return loc;
        }
    };
    //创建一片静态存储区
    unsigned char m_space[sizeof(DSNode) * N];
    //创建一个标记数组
    int m_used[N];

    Node* create()
    {
        DSNode* ret = NULL;

        for(int i=0; i<N; i++)
        {
            if(!m_used[i])
            {
                // 在固定的内存中为新创建的对象分配空间
                ret = reinterpret_cast<DSNode*>(m_space) + i;
                // 在这片空间调用构造函数,new后面的括号表示在哪片空间调用
                // 后面的DSNode() 表示调用的是这个类的构造函数
                ret = new(ret)DSNode();
                m_used[i]= 1;
                break;
            }

        }
        return ret;
    }

    void destroy(Node* pn)
    {
        // 这里强制转换的目的是后面需要指针运算
        DSNode* space = reinterpret_cast<DSNode*>(m_space);
        DSNode* psn = dynamic_cast<DSNode*>(pn);

        for(int i=0; i<N; i++)
        {
            if(psn == (space + i))
            {
                m_used[i] = 0;
                psn->~DSNode();
                break;
            }
        }
    }

public:
    DualStaticLinkList()
    {
        for(int i=0; i<N; i++)
        {
            m_used[i] = 0;
        }
    }

    int capacity()
    {
        return N;
    }

    ~DualStaticLinkList()
    {
        this->clear();
    }
};

}


#endif // DUALSTATICLINKLIST_H
