#ifndef SORT_H
#define SORT_H

#include "Object.h"
#include <iostream>

using namespace std;
namespace ZTYLib
{

class Sort : public Object
{
private:
    Sort();
    Sort(const Sort&);
    Sort& operator = (const Sort&);

    template <typename T>
    static void Swap(T& a, T& b)
    {
        T c = a;
        a = b;
        b = c;
    }
public:
    template<typename T>
    static void Select(T array[], int len, bool min2max = true)
    {
        for(int i=0; i<len; i++)
        {
            int min = i;

            for(int j=i+1; j<len; j++)
            {
                if(min2max ? (array[min] > array[j]) : (array[min] < array[j]))
                {
                    min = j;
                }
            }

            //这里老师写的是    min != i  ??
            if(array[i] != array[min])
            {
                Swap(array[i], array[min]);
            }
        }

    }

    template< typename T>
    static void Insert(T array[], int len, bool min2max = true)
    {
        for(int i=1; i<len; i++)
        {
            int k = i;
            T e = array[i];

            for(int j=i-1; (j>=0) && (min2max ? (array[j] > e) : (array[j] < e)); j--)
            {
                array[j+1] = array[j];
                k = j;
            }

            if(array[k] != e)
            {
                array[k] = e;
            }

        }
    }

    template< typename T>
    static void Bubble(T array[], int len, bool min2max = true)
    {
        for(int i=0; i<len-1; i++)
        {
            for(int j=0; j<len-i-1; j++)
            {
                if(min2max ? (array[j] > array[j+1]) : (array[j] < array[j+1]))
                {
                    Swap(array[j], array[j+1]);
                }
            }
        }

    }

    template< typename T>
    static void Shell(T array[], int len, bool min2max = true)
    {
        int d = len;

        do
        {
            d = d/3 + 1;

            for(int i=d; i<len; i+=d)
            {
                int k = i;
                T e = array[i];

                for(int j=i-d; (j>=0) && (min2max ? (array[j] > e) : (array[j] < e)); j-=d)
                {
                    array[j+d] = array[j];
                    k = j;
                }

                if(array[k] != e)
                {
                    array[k] = e;
                }

            }
        }while(d > 1);
    }
};

}


#endif // SORT_H
