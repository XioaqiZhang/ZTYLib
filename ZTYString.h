#ifndef ZTYSTRING_H
#define ZTYSTRING_H

#include "Object.h"

namespace ZTYLib
{
class String : public Object
{
protected:
    char* m_str;
    int m_length;

    void init(const char* s);
    bool equal(const char* l, const char* r, int len) const;
public:
    String();
    String(char c);
    String(const char* s);
    String(const String& s);
    int length() const;

    //用于进行与传统C语言字符串进行互操作转换的函数
    const char* str() const;
    bool startWith(const char* s) const;
    bool startWith(const String& s) const;
    bool endOf(const char* s) const;
    bool endOf(const String& s) const;

    char& operator [] (int i);
    char operator [] (int i) const;
    bool operator == (const String& s) const;
    bool operator == (const char* s) const;
    bool operator != (const String& s) const;
    bool operator != (const char* s) const;
    bool operator > (const String& s) const;
    bool operator > (const char* s) const;
    bool operator < (const String& s) const;
    bool operator < (const char* s) const;
    bool operator >= (const String& s) const;
    bool operator >= (const char* s) const;
    bool operator <= (const String& s) const;
    bool operator <= (const char* s) const;

    String operator + (const String& s) const;
    String operator + (const char* s) const;
    String operator += (const String& s);
    String operator += (const char* s);

    String operator = (const String& s);
    String operator = (const char* s);
    String operator = (const char);

    String& insert(int i, const char* s);
    String& insert(int i, const String& s);
    String& trim();

    ~String();
};
}


#endif // ZTYSTRING_H
