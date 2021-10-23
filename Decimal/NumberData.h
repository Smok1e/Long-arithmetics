#pragma once

#include <memory>
#include <cmath>

//----------------

class NumberData
{
public:
#ifndef NUMBER_DATA_SIZE
	const static size_t DataSize = 8;
#else
	const static size_t DataSize = NUMBER_DATA_SIZE;
#endif

	NumberData ();
	NumberData (const NumberData& copy);
	NumberData (const char* begin, const char* end);
	NumberData (const char* str);
	NumberData (int                number);
	NumberData (unsigned long long number);

	template <class storage_t>
	NumberData (const storage_t& storage);

	char*       begin ();
	const char* begin () const;

	char*       end ();
	const char* end () const;

	NumberData& operator = (const NumberData& that);

	friend bool operator == (const NumberData& lft, const NumberData& rgt);
	friend bool operator != (const NumberData& lft, const NumberData& rgt);

protected:
	char m_data[NumberData::DataSize];

};

//----------------

NumberData::NumberData () :
	m_data {}
{}

NumberData::NumberData (const NumberData& copy) :
	m_data {}
{
	std::memcpy (m_data, copy.m_data, NumberData::DataSize);
}

NumberData::NumberData (const char* begin, const char* end) :
	m_data {}
{
	size_t count = end-begin;
	for (size_t i = 0; i < count && i < NumberData::DataSize; i++)
		m_data[NumberData::DataSize-i-1] = *(end-i-1);	
}

NumberData::NumberData (const char* str) :
	m_data {}
{
	size_t len = strlen (str);
	for (size_t i = 0; i < NumberData::DataSize && i < len; i++)
	{	
		char value = str [len-i-1] - '0'; 
		if (value < 0 || value > 9)
		{
			static wchar_t wstr[NumberData::DataSize+1] = L"";
			for (size_t c = 0; c < NumberData::DataSize; c++) wstr[i] = static_cast <wchar_t> (str[c]);

			static wchar_t text[512] = L"";
			swprintf_s (
				text,
				L"Ты дурак, у тебя на вход констрктора NumberData от const char* передан символ '%c', что соответствует численному значению %d.\n"
			    L"Позиция символа в строке: %zu,\n"
				L"Принятая строка: '%s'.\n"
				L"Прогу завершаем принудительно?\n",
				wstr[len-i-1], value, len-i-1, wstr);

			int result = MessageBoxW (GetConsoleWindow (), text, L"Ошибочка вышла:", MB_ICONWARNING | MB_YESNO);
			if (result == IDYES) abort ();
		}

		m_data [i] = value;
	}	
}

NumberData::NumberData (int number) :
	m_data {}
{
	char str[MAX_PATH] = "";
	sprintf_s (str, "%d", number);

	size_t len = strlen (str);
	for (size_t i = 0; i < NumberData::DataSize && i < len; i++)
		m_data [i] = str[len-i-1] - '0'; 
}

NumberData::NumberData (unsigned long long number) :
	m_data {}
{
	char str[MAX_PATH] = "";
	sprintf_s (str, "%llu", number);

	size_t len = strlen (str);
	for (size_t i = 0; i < NumberData::DataSize && i < len; i++)
		m_data [i] = str[len-i-1] - '0'; 
}

template <class storage_t>
NumberData::NumberData (const storage_t& storage) :
	m_data {}
{
	const char* begin = storage.begin ();
	const char* end   = storage.end   ();

	size_t count = end-begin;
	for (size_t i = 0; i < count && i < NumberData::DataSize; i++)
		m_data[i] = *(begin+i);	
}

//----------------

char* NumberData::begin ()
{
	return m_data;
}

const char* NumberData::begin () const
{
	return const_cast <const char*> (m_data);
}

//----------------

char* NumberData::end ()
{
	return m_data + NumberData::DataSize;
}

const char* NumberData::end () const
{
	return const_cast <const char*> (m_data + NumberData::DataSize);
}

//----------------

NumberData& NumberData::operator = (const NumberData& that)
{
	if (&that == this)
		return *this;

	std::memcpy (m_data, that.m_data, NumberData::DataSize);
	return *this;	
}

//----------------

bool operator == (const NumberData& lft, const NumberData& rgt)
{
	const char* lbegin = lft.begin ();
	const char* rbegin = rgt.begin ();

	for (size_t i = 0; i < NumberData::DataSize; i++)
		if (lbegin[i] != rbegin[i]) return false;

	return true;	
}

bool operator != (const NumberData& lft, const NumberData& rgt)
{
	const char* lbegin = lft.begin ();
	const char* rbegin = rgt.begin ();

	for (size_t i = 0; i < NumberData::DataSize; i++)
		if (lbegin[i] != rbegin[i]) return true;

	return false;	
}

//----------------