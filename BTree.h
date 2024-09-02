#ifndef BTREE_H
#define BTREE_H

#include "BTreeNode.h"
#include "Tree.h"
#include "Exception.h"
#include "LinkQueue.h"

namespace ZTYLib
{
// 树的操作使用递归实现
template <typename T>
class BTree : public Tree<T>
{
public:
    bool insert(TreeNode<T>* node)
    {
        int ret = true;


        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        int ret = true;


        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        return NULL;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        return NULL;
    }

    BTreeNode<T>* find(const T& value) const
    {
        return NULL;
    }

    BTreeNode<T>* find(TreeNode<T>* node) const
    {
        return NULL;
    }

    BTreeNode<T>* root() const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
    }

    int degree() const
    {
        return 0;
    }

    int count() const
    {
        return 0;
    }

    int height() const
    {
        return 0;
    }

    void clear()
    {
        this->m_root = NULL;
    }

    ~BTree()
    {
        clear();
    }

};
}
#endif // BTREE_H
