#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreeNode.h"
#include "LinkList.h"

namespace ZTYLib
{
template <typename T>
class GTreeNode : public TreeNode<T>
{
public:
        LinkList<GTreeNode<T>*> child;
};

}


#endif // GTREENODE_H
