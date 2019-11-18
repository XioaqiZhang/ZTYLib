#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Object.h"
namespace ZTYLib
{

#define THROW_EXCEPTION(e,m) (throw e(m, __FILE__, __LINE__))

class Exception : public Object
{
protected:
    char* m_message;
    char* m_location;
    void init(const char* message, const char* file, int line);

public:
    Exception(const char* message);
    Exception(const char* file, int line);
    Exception(const char* message, const char* file, int line);

    Exception(const Exception& e);
    Exception& operator=(const Exception& e);

    virtual const char* message() const;
    virtual const char* location() const;

    virtual ~Exception() = 0;
};

class ArithmeticException : public Exception
{
public:
    ArithmeticException() : Exception(0){}
    ArithmeticException(const char* file, int line) : Exception(file, line){}
    ArithmeticException(const char* message, const char* file, int line) : Exception(message, file, line){}
    ArithmeticException(const ArithmeticException& e) : Exception(e){}

    ArithmeticException& operator =(const ArithmeticException& e)
    {
        Exception::operator =(e);
        return *this;
    }

};

class NullPointerException : public Exception
{
public:
    NullPointerException() : Exception(0){}
    NullPointerException(const char* file, int line) : Exception(file, line){}
    NullPointerException(const char* message, const char* file, int line) : Exception(message, file, line){}
    NullPointerException(const NullPointerException& e) : Exception(e){}

    NullPointerException& operator =(const NullPointerException& e)
    {
        Exception::operator =(e);
        return *this;
    }

};

class IndexOutOfBounds : public Exception
{
public:
    IndexOutOfBounds() : Exception(0){}
    IndexOutOfBounds(const char* file, int line) : Exception(file, line){}
    IndexOutOfBounds(const char* message, const char* file, int line) : Exception(message, file, line){}
    IndexOutOfBounds(const IndexOutOfBounds& e) : Exception(e){}

    IndexOutOfBounds& operator =(const IndexOutOfBounds& e)
    {
        Exception::operator =(e);
        return *this;
    }

};

class NoEnoughMemoryException : public Exception
{
public:
    NoEnoughMemoryException() : Exception(0){}
    NoEnoughMemoryException(const char* file, int line) : Exception(file, line){}
    NoEnoughMemoryException(const char* message, const char* file, int line) : Exception(message, file, line){}
    NoEnoughMemoryException(const NoEnoughMemoryException& e) : Exception(e){}

    NoEnoughMemoryException& operator =(const NoEnoughMemoryException& e)
    {
        Exception::operator =(e);
        return *this;
    }

};

class InvalidParameterException : public Exception
{
public:
    InvalidParameterException() : Exception(0){}
    InvalidParameterException(const char* file, int line) : Exception(file, line){}
    InvalidParameterException(const char* message, const char* file, int line) : Exception(message, file, line){}
    InvalidParameterException(const InvalidParameterException& e) : Exception(e){}

    InvalidParameterException& operator =(const InvalidParameterException& e)
    {
        Exception::operator =(e);
        return *this;
    }

};

class InvalidOperationException : public Exception
{
public:
    InvalidOperationException() : Exception(0){}
    InvalidOperationException(const char* file, int line) : Exception(file, line){}
    InvalidOperationException(const char* message, const char* file, int line) : Exception(message, file, line){}
    InvalidOperationException(const InvalidOperationException& e) : Exception(e){}

    InvalidOperationException& operator =(const InvalidOperationException& e)
    {
        Exception::operator =(e);
        return *this;
    }

};
}


#endif // EXCEPTION_H
