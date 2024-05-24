#include "CMyString.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

// конструктор по умолчанию
CMyString::CMyString()
	: m_length(0),
	m_str(nullptr)
{
}

CMyString::CMyString(const char* pString)
	: m_length(strlen(pString)),
	m_str(nullptr)
{
	if (m_length != 0)
	{
		m_str = new char[m_length + 1];
		for (size_t i = 0; i < m_length; i++)
		{
			m_str[i] = pString[i];
		}
		m_str[m_length] = '\0';
	}
}

// конструктор, инициализирующий строку данными из 
// символьного массива заданной длины
CMyString::CMyString(const char* pString, size_t length)
	: m_length(length),
	m_str(nullptr)
{
	if (length != 0)
	{
		m_str = new char[m_length + 1];
		for (size_t i = 0; i < m_length; i++)
		{
			m_str[i] = pString[i];
		}

		m_str[length] = '\0';
	}
}

// конструктор копирования
CMyString::CMyString(CMyString const& other)
	: m_length(other.GetLength()),
	m_str(nullptr)
{
	if (m_length != 0)
	{
		m_str = new char[m_length + 1];
		for (size_t i = 0; i < m_length; i++)
		{
			m_str[i] = other.m_str[i];
		}

		m_str[m_length] = '\0';
	}
}

// перемещающий конструктор
//  реализуется совместно с перемещающим оператором присваивания 
CMyString::CMyString(CMyString&& other) noexcept
	: m_length(other.m_length),
	m_str(other.m_str)
{
	other.m_str = nullptr;
}

CMyString::CMyString(CMyString&& other, size_t length) noexcept
	: m_length(length),
	m_str(other.m_str)
{
	other.m_str = nullptr;
}

CMyString& CMyString::operator =(CMyString&& other) noexcept
{
	if (&other != this)
	{
		delete[] m_str;
		m_str = new char[other.m_length];
		m_str = other.m_str;
		m_length = other.m_length;
		other.m_length = 0;
		other.m_str = 0;
	}
	return *this;
}

// конструктор, инициализирующий строку данными из 
// строки стандартной библиотеки C++
CMyString::CMyString(std::string const& stlString)
	: m_length(stlString.size()),
	m_str(nullptr)
{
	if (m_length != 0)
	{
		m_str = new char[m_length + 1];
		for (size_t i = 0; i < m_length; i++)
		{
			m_str[i] = stlString[i];
		}
		m_str[m_length] = '\0';
	}
}

// деструктор класса - освобождает память, занимаемую символами строки
CMyString::~CMyString()
{
	delete[] m_str;
}

// возвращает длину строки (без учета завершающего нулевого символа)
size_t CMyString::GetLength() const
{
	return m_length;
}

// возвращает указатель на массив символов строки.
// В конце массива обязательно должен быть завершающий нулевой символ
// даже если строка пустая 
const char* CMyString::GetStringData() const
{
	static const char emptyArr[] = "";
	return m_str ? m_str : emptyArr;
}

// возвращает подстроку с заданной позиции длиной не больше length символов

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start < 0)
	{
		throw std::out_of_range("start position must be >= 0");
	}

	if (m_length == 0 || start > m_length - 1)
	{
		return CMyString();
	}

	size_t len = 0;
	if (length != 0)
	{
		len = (SIZE_MAX - length + start < SIZE_MAX - m_length) ? (m_length - start) : length;
	}

	char* newStr = new char[len];

	for (size_t i = 0; i < len; i++)
	{
		newStr[i] = m_str[i + start];
	}

	CMyString subStr(newStr, len);

	delete[] newStr;

	return subStr;
}

// очистка строки (строка становится снова нулевой длины)
void CMyString::Clear()
{
	delete[] m_str;
	m_str = nullptr;
	m_length = 0;
}

// Возвращает вместимость строки
size_t CMyString::GetCapacity()
{
	return m_length;
}

std::ostream& operator<<(std::ostream& os, const CMyString& str)
{
	for (size_t i = 0; i < str.m_length; i++)
	{
		if (str.m_str[i] != '\0')
		{
			os << str.m_str[i];
		}
	}

	return os;
}

CMyString& CMyString::operator =(const CMyString& other)
{
	if (this == &other)
	{
		return *this;
	}

	if (m_str != nullptr)
	{
		delete[] m_str;
		m_str = nullptr;
	}

	m_length = other.m_length;
	if (m_length == 0)
	{
		return *this;
	}

	m_str = new char[m_length + 1];

	for (size_t i = 0; i < m_length; i++)
	{
		m_str[i] = other.m_str[i];
	}

	m_str[m_length] = '\0';

	return *this;
}

CMyString& CMyString::operator +=(const CMyString& other)
{
	if (other.m_str)
	{
		char* newChArr = new char[m_length + other.m_length + 1];
		for (size_t i = 0; i < m_length + other.m_length; i++)
		{
			if (i < m_length)
			{
				newChArr[i] = m_str[i];
			}
			else
			{
				newChArr[i] = other.m_str[i - m_length];
			}
		}

		m_length += other.m_length;
		newChArr[m_length] = '\0';
		delete[] m_str;
		m_str = newChArr;
	}
	return *this;
}

CMyString CMyString::operator +(const CMyString& other) const
{
	char* newStr = new char[m_length + other.m_length];

	for (size_t i = 0; i < m_length + other.m_length; i++)
	{
		if (i < m_length)
		{
			newStr[i] = m_str[i];
		}
		else
		{
			newStr[i] = other.m_str[i - m_length];
		}
	}

	CMyString result(newStr, m_length + other.m_length);
	delete[] newStr;
	return result;
}

CMyString CMyString::operator +(const std::string& other) const
{
	char* newStr = new char[m_length + other.size()];

	for (size_t i = 0; i < m_length + other.size(); i++)
	{
		if (i < m_length)
		{
			newStr[i] = m_str[i];
		}
		else
		{
			newStr[i] = other[i - m_length];
		}
	}

	CMyString result(newStr, m_length + other.size());
	delete[] newStr;
	return result;
}

CMyString CMyString::operator +(const char* other) const
{
	char* newStr = new char[m_length + strlen(other)];

	for (size_t i = 0; i < m_length + strlen(other); i++)
	{
		if (i < m_length)
		{
			newStr[i] = m_str[i];
		}
		else
		{
			newStr[i] = other[i - m_length];
		}
	}

	CMyString result(newStr, m_length + strlen(other));
	delete[] newStr;
	return result;
}

bool CMyString::operator ==(const CMyString& other) const
{
	if (m_length != other.m_length)
	{
		return false;
	}

	for (size_t i = 0; i < m_length; i++)
	{
		if (m_str[i] != other.m_str[i])
		{
			return false;
		}
	}
	return true;
}

bool CMyString::operator !=(const CMyString& other) const
{
	return !(*this == other);
}

char CMyString::operator [](size_t index) const
{
	if (index >= m_length)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_str[index];
}

char& CMyString::operator [](size_t index)
{
	if (index >= m_length)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_str[index];
}

bool CMyString::operator >(const CMyString& other) const
{	
	if (m_length == 0)
	{
		return false;
	}

	if (other.m_length == 0 && m_length != 0)
	{
		return true;
	}


	size_t len = 0;
	m_length < other.m_length ? len = m_length : len = other.m_length;

	for (size_t i = 0; i < len; i++)
	{
		if (m_str[i] != other.m_str[i])
		{
			return m_str[i] > other.m_str[i] ? true : false;     
		}
	}
	
	if (m_length == other.m_length)
	{
		return false;
	}

	return m_length == len ? true : false;
}

bool CMyString::operator >=(const CMyString& other) const
{
	if (m_length == 0 && other.m_length != 0)
	{
		return false;
	}

	if (other.m_length == 0 && m_length != 0)
	{
		return true;
	}

	size_t len = 0;
	m_length < other.m_length ? len = m_length : len = other.m_length;

	for (size_t i = 0; i < len; i++)
	{
		if (m_str[i] != other.m_str[i])
		{
			return m_str[i] > other.m_str[i] ? true : false;
		}
	}

	if (m_length == other.m_length)
	{
		return true;
	}

	return m_length == len ? true : false;
}

bool CMyString::operator <(const CMyString& other) const
{
	return !(*this >= other);
}

bool CMyString::operator <=(const CMyString& other) const
{
	return !(*this > other);
}

std::istream& operator>>(std::istream& is, CMyString& str)
{
	std::string temp;
	std::getline(is, temp);

	delete[] str.m_str;
	str.m_length = temp.length();
	str.m_str = new char[str.m_length + 1];
	strcpy_s(str.m_str, str.m_length + 1, temp.c_str());

	return is;
}