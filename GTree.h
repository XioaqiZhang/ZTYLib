#ifndef GTREE_H
#define GTREE_H

#include "GTreeNode.h"
#include "Tree.h"
#include "Exception.h"
#include "LinkQueue.h"

namespace ZTYLib
{
// 树的操作使用递归实现
template <typename T>
class GTree : public Tree<T>
{
protected:
    LinkQueue<GTreeNode<T>*> m_queue;

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

    void free(GTreeNode<T>* node)
    {
        if(node != NULL)
        {
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                free(node->child.current());
            }

            if(node->flag())
            {
                delete node;
            }
        }
    }

    void remove(GTreeNode<T>* node, GTree<T>*& ret)
    {
        ret = new GTree<T>();

        if(ret == NULL)
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat new tree ...");
        }
        else
        {
            if(root() == node)
            {
                this->m_root = NULL;
            }
            else
            {
                //得到node的父节点的孩子链表
                LinkList<GTreeNode<T>*>& child = dynamic_cast<GTreeNode<T>*>(node->parent)->child;

                //将当前要删除的节点从父节点删除
                child.remove(child.find(node));

                node->parent = NULL;
            }

            ret->m_root = node;
        }

    }

    int count(GTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            ret = 1;

            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                ret += count(node->child.current());
            }
        }

        return ret;
    }

    int height(GTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                int h = height(node->child.current());

                if(ret < h)
                {
                    ret = h;
                }
            }

            ret += 1;
        }

        return ret;
    }

    int degree(GTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            ret = node->child.length();

            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                int d = degree(node->child.current());

                if(ret < d)
                {
                    ret = d;
                }
            }
        }

        return ret;
    }

public:
    GTree()
    {

    }
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

        GTreeNode<T>* node = GTreeNode<T>::NewNode();

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
        GTree<T>* ret = NULL;
        GTreeNode<T>* node = find(value);

        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParameterException, "Can not find the node via parameter value ...");
        }
        else
        {
            remove(node, ret);

            m_queue.clear();
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        GTree<T>* ret = NULL;
        node = find(node);

        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid ...");
        }
        else
        {
            remove(dynamic_cast<GTreeNode<T>*>(node), ret);

            m_queue.clear();
        }

        return ret;
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
        return degree(root());
    }

    int count() const
    {
        return count(root());
    }

    int height() const
    {
        return height(root());
    }

    void clear()
    {
        free(root());

        this->m_root = NULL;

        m_queue.clear();
    }

    bool begin()
    {
        bool ret= (root() != NULL);

        if(ret)
        {
            m_queue.clear();
            m_queue.add(root());
        }

        return ret;
    }

    bool end()
    {
        return (m_queue.length() == 0);
    }

    bool next()
    {
        bool ret = (m_queue.length() > 0);

        if(ret)
        {
            //node 指向队头元素
            GTreeNode<T>* node = m_queue.front();

            //将队头元素移除
            m_queue.remove();

            //将出队列的结点的孩子压入队列
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                m_queue.add(node->child.current());
            }
        }

        return ret;
    }

    T current()
    {
        //在遍历过程中
        if(!end())
        {
            return m_queue.front()->value;
        }
        else
        {
            //遍历未开始/结束
            THROW_EXCEPTION(InvalidOperationException, "No value in current position ...");
        }
    }

    ~GTree()
    {
        clear();
    }
};

}

#endif // GTREE_H
