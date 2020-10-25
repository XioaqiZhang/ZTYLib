#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace ZTYLib
{

template <typename T>
class TreeNode : public Object
{
public:
    T value;
    TreeNode<T>* parent;
    TreeNode()
    {
        parent = NULL;
    }
    virtual ~TreeNode() = 0;
};

template <typename T>
TreeNode<T>::~TreeNode()
{

}

}

#endif // TREENODE_H
