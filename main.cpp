#include <iostream>
#include "Sort.h"
#include "GTree.h"
#include <stddef.h>
#include "BTree.h"


using namespace std;
using namespace ZTYLib;


int main()
{

        GTree<char> t;
        GTreeNode<char>* node = NULL;

        GTreeNode<char> root;

        root.value = 'A';
        root.parent = NULL;


        t.insert(&root);

        node = t.find('A');
        t.insert('B', node);
        t.insert('C',node);
        t.insert('D',node);

        node = t.find('B');
        t.insert('E',node);
        t.insert('F',node);

        node = t.find('E');
        t.insert('K',node);
        t.insert('L',node);

        node = t.find('C');
        t.insert('G',node);

        node = t.find('D');
        t.insert('H',node);
        t.insert('I',node);
        t.insert('J',node);

        node = t.find('H');
        t.insert('M',node);

//        t.clear();

        cout << t.count() << endl;
        cout << t.height() << endl;
        cout << t.degree() << endl;

        for(t.begin(); !t.end(); t.next())
        {
            cout << t.current() << endl;
        }

    BTree<int> bt;

    BTreeNode<int> btn;

    return 0;
}
