#pragma once

#include <string>

class CMyString
{
public:
    CMyString();
    CMyString(const char* pString);
    CMyString(const char* pString, size_t length);
    CMyString(CMyString const& other);
    CMyString(CMyString&& other) noexcept;
    CMyString(std::string const& stlString);
    ~CMyString();

    CMyString& operator =(CMyString&& other) noexcept;
    CMyString& operator =(const CMyString& other);
    CMyString& operator +=(const CMyString& other);

    CMyString operator +(const CMyString& other) const;
    CMyString operator +(const std::string& other) const;
    CMyString operator +(const char* other) const;

    bool operator ==(const CMyString& other) const;
    bool operator !=(const CMyString& other) const;
    bool operator >(const CMyString& other) const;
    bool operator >=(const CMyString& other) const;
    bool operator <(const CMyString& other) const;
    bool operator <=(const CMyString& other) const;

    char operator [](size_t index) const;
    char& operator [](size_t index);

    size_t GetLength() const;
    const char* GetStringData() const;
    CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
    void Clear();
    size_t GetCapacity();

    friend std::ostream& operator <<(std::ostream& os, const CMyString& str);
    friend std::istream& operator >>(std::istream& is, CMyString& str);

private:
    char* m_str;
    size_t m_length;
    //capacity
};