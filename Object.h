#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
namespace ZTYLib
{
class Object
{
public:
    // 后面的throw()是异常规格说明  表示该函数不会抛出任何异常
    void* operator new (unsigned int size) throw();
    void operator delete(void* p);
    void* operator new[] (unsigned int size) throw();
    void operator delete[] (void* p);
    bool operator == (const Object& obj);
    bool operator != (const Object& obj);
    virtual ~Object() = 0;
};

}
#endif // OBJECT_H
