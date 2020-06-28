#include <iostream>
#include "DualCircleList.h"


using namespace std;
using namespace ZTYLib;



int main()
{
    DualCircleList<int> d1;

    for(int i=0; i<5; i++)
    {
        d1.insert(0, i);
        d1.insert(0, 5);
    }
    cout << "begin" << endl;

    d1.move(d1.length()-1);

    while(d1.find(5) != -1)
    {
        if(d1.current() == 5)
        {
            cout << d1.current() << endl;
            d1.remove(d1.find(d1.current()));
        }
        else
        {
            d1.pre();
        }
    }

    cout << "end" << endl;

//    for(d1.move(0); !d1.end(); d1.next())
//    {
//        cout << d1.current() << endl;
//    }

    for(int i=0; i<d1.length(); i++)
    {
        cout << d1.get(i) << endl;
    }
    return 0;
}
