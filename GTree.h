#ifndef GTREE_H
#define GTREE_H

#include "GTreeNode.h"
#include "Tree.h"
#include "Exception.h"

namespace ZTYLib
{
// 树的操作使用递归实现
template <typename T>
class GTree : public Tree<T>
{
protected:
    GTreeNode<T>* find(GTreeNode<T>* node, const T& value) const
    {
        GTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            if(node->value == value)
            {
                return node;
            }
            else
            {
                //对当前节点下每一棵子树进行遍历
                for(node->child.move(0); !node->child.end() && (ret == NULL);node->child.next())
                {
                    //在以node->child.current()指针为根节点的树中，查找value成员
                    ret = find(node->child.current(), value);
                }
            }
        }
        return ret;
    }
    GTreeNode<T>* find(GTreeNode<T>* node, GTreeNode<T>* obj) const
    {
        GTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            if(node == obj)
            {
                return node;
            }
            else
            {
                //遍历当前树的所有子节点
                for(node->child.move(0); !node->child.end() && (ret == NULL); node->child.next())
                {
                    //在以node->child.current()为根节点的子树中，查找obj节点
                    ret = find(node->child.current(), obj);
                }
            }
        }

        return ret;
    }
public:
    bool insert(TreeNode<T>* node) //插入节点
    {
        bool ret = true;

        if(node != NULL)
        {
            if(this->root() == NULL)
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                //查找要插入的节点的父节点是否在目标的树中
                GTreeNode<T>* np = find(node->parent);

                if(np != NULL)
                {
                    // 将要插入的节点进行类型转换
                    GTreeNode<T>* n = dynamic_cast<GTreeNode<T>*>(node);

                    //如果上面查找到的父节点的孩子中没有要插入的节点node
                    //这里为什么是 <0 ? find函数返回的不是一个指针吗？为什么和0比较？
                    if(np->child.find(n) < 0)
                    {
                        //执行插入操作
                        np->child.insert(n);
                    }
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "Invalid parent tree node ...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node cannot be NULL ...");
        }

        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent) // 插入数据元素
    {
        bool ret = true;

        GTreeNode<T>* node = new GTreeNode<T>();

        if(node != NULL)
        {
            node->parent = parent;
            node->value = value;

            insert(node);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat a new tree node ...");
        }

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

    GTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    GTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(), dynamic_cast<GTreeNode<T>*>(node));
    }

    GTreeNode<T>* root() const
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
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

    ~GTree()
    {
        clear();
    }
};

}

#endif // GTREE_H
