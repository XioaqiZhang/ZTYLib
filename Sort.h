﻿//Sort.h
#ifndef SORT_H
#define SORT_H

#include "Object.h"
#include "Array.h"

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

    template< typename T>
    static void Merge(T src[], T helper[], int begin, int mid, int end, bool min2max)
    {
        int i = begin;
        int j = mid+1;
        int k = begin;

        while((i <= mid) && (j <= end))
        {
            if(min2max ? (src[i] < src[j]) : (src[i] > src[j]))
            {
                helper[k++] = src[i++];
            }
            else
            {
                helper[k++] = src[j++];
            }
        }

        while(i <= mid)
        {
            helper[k++] = src[i++];
        }

        while(j <= end)
        {
            helper[k++] = src[j++];
        }

        for(i=begin; i<=end; i++)
        {
            src[i] = helper[i];
        }
    }

    template< typename T>
    static void Merge(T src[], T helper[], int begin, int end, bool min2max)
    {
        if(begin < end)
        {
            int mid = (begin + end) / 2;

            //对左半部分进行归并排序
            Merge(src, helper, begin, mid, min2max);
            //对右半部分进行归并排序
            Merge(src, helper, mid+1, end, min2max);
            //将两部分排序好的数据归并
            Merge(src, helper, begin, mid, end, min2max);
        }
    }

    template< typename T>
    static int Partition(T array[], int begin, int end, bool min2max)
    {
        T pv = array[begin];

        while(begin < end)
        {
            while((begin < end) && (min2max ? (array[end] > pv) : (array[end] < pv)))
            {
                end--;
            }

            Swap(array[begin], array[end]);

            while((begin < end) && (min2max ? (array[begin] <= pv) : (array[begin] >= pv)))
            {
                begin++;
            }

            Swap(array[begin], array[end]);
        }

        array[begin] = pv;

        return begin;
    }

    template< typename T>
    static void Quick(T array[], int begin, int end, bool min2max)
    {
        if(begin < end)
        {
            int pivot = Partition(array, begin, end, min2max);

            Quick(array, begin, pivot-1, min2max);
            Quick(array, pivot+1, end, min2max);
        }

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

            if(i != min)
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

            if(k != i)
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

    template< typename T>
    static void Merge(T array[], int len, bool min2max = true)
    {
        T* helper = new T[len];

        if(helper != NULL)
        {
            Merge(array, helper, 0, len-1, min2max);
        }

        delete[] helper;
    }

    template< typename T>
    static void Quick(T array[], int len, bool min2max = true)
    {
        Quick(array, 0, len-1, min2max);
    }

    template< typename T>
    static void Select(Array<T>& array, bool min2max = true)
    {
        Select(array.array(), array.length(), min2max);
    }

    template< typename T>
    static void Insert(Array<T>& array, bool min2max = true)
    {
        Insert(array.array(), array.length(), min2max);
    }

    template< typename T>
    static void Bubble(Array<T>& array, bool min2max = true)
    {
        Bubble(array.array(), array.length(), min2max);
    }

    template< typename T>
    static void Shell(Array<T>& array, bool min2max = true)
    {
        Shell(array.array(), array.length(), min2max);
    }

    template< typename T>
    static void Merge(Array<T>& array, bool min2max = true)
    {
        Merge(array.array(), array.length(), min2max);
    }

    template< typename T>
    static void Quick(Array<T>& array, bool min2max = true)
    {
        Quick(array.array(), array.length(), min2max);
    }
};

}


#endif // SORT_H
