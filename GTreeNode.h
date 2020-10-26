#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreeNode.h"
#include "LinkList.h"

namespace ZTYLib
{
template <typename T>
class GTreeNode : public TreeNode<T>
{
protected:
    bool m_flag;

    void* operator new(unsigned int size) throw()
    {
        return Object::operator new(size);
    }

public:
    LinkList<GTreeNode<T>*> child;

    GTreeNode()
    {
        m_flag = false;
    }

    bool flag()
    {
        return m_flag;
    }

    static GTreeNode<T>* NewNode()
    {
        GTreeNode<T>* ret = new GTreeNode<T>();

        if(ret != NULL)
        {
            ret->m_flag = true;
        }

        return ret;
    }
};

}


#endif // GTREENODE_H
