#pragma once

//----------------

#include <memory>
#include <cstdio>
#include <conio.h>

#include "NumberData.h"
#include "NumberDataView.h"

//----------------

template <class storage_t>
class Number
{
public:
	template <class data_t>
	Number (data_t& data);

	char*       begin ();
	const char* begin () const;

	char*       end ();
	const char* end () const;

	size_t             size         ()                         const;
	void               print        (bool skip_nulls = false)  const;
	void               debug_print  ()                         const;
	unsigned long long dec          ()                         const;
	char*              to_str       (char* buffer, size_t max) const;

	char&       operator[] (size_t index);
	const char& operator[] (size_t index) const;

	template <class rgt_storage_t>
	Number <storage_t>& operator = (const Number <rgt_storage_t>& that);

	template <class lft_storage_t, class rgt_storage_t>
	friend bool operator == (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt);

	template <class lft_storage_t, class rgt_storage_t>
	friend bool operator != (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt);

	template <class lft_storage_t, class rgt_storage_t>
	friend bool operator > (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt);

	template <class lft_storage_t, class rgt_storage_t>
	friend bool operator >= (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt);

	template <class lft_storage_t, class rgt_storage_t>
	friend bool operator < (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt);

	template <class lft_storage_t, class rgt_storage_t>
	friend bool operator <= (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt);

	template <class operand_storage_t>
	friend Number <NumberData> operator ~ (const Number <operand_storage_t>& number);

	template <class lft_storage_t, class rgt_storage_t>
	friend Number <NumberData> operator + (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt);

	template <class lft_storage_t, class rgt_storage_t>
	friend Number <NumberData> operator - (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt);

	template <class lft_storage_t, class rgt_storage_t>
	friend Number <NumberData> operator * (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt);

	template <class lft_storage_t, class rgt_storage_t>
	friend Number <NumberData> operator / (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt);

	template <class lft_storage_t, class rgt_storage_t>
	friend Number <NumberData> operator % (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt);	

	template <class lft_storage_t>
	friend Number <NumberData> operator << (const Number <lft_storage_t>& lft, int shift);

	template <class lft_storage_t>
	friend Number <NumberData> operator >> (const Number <lft_storage_t>& lft, int shift);

protected:
	storage_t m_storage;

};

//----------------

Number <NumberData> InitNumber (const char* str)
{
	NumberData data (str);
	return Number <NumberData> (data);
}

template <class storage_t>
Number <NumberData> InitNumber (const storage_t& storage)
{
	const char* src_begin = storage.begin ();
	const char* src_end   = storage.end   ();
	size_t src_size = src_end - src_begin;

	NumberData data;
	Number <NumberData> number (data);
	size_t size = number.size ();

	for (size_t i = 0; i < size && i < src_size; i++)
		number[size-i-1] = src_begin[src_size-i-1];

	return number;
}

Number <NumberData> InitNumber ()
{
	NumberData data;
	return Number <NumberData> (data);
}

//----------------

template <class storage_t>
Number <NumberDataView> InitNumberView (storage_t& storage, size_t begin, size_t end)
{
	if (end > (storage.end () - storage.begin ())) end = (storage.end () - storage.begin ());

	NumberDataView view (storage.begin () + begin, storage.begin () + end);
	return Number <NumberDataView> (view);
}

template <class storage_t>
Number <NumberDataView> InitNumberView (storage_t& storage)
{
	NumberDataView view (storage.begin (), storage.end ());
	return Number <NumberDataView> (view);
}

//----------------

template <class storage_t>
Number <NumberDataView> CutNulls (storage_t& storage)
{
	size_t size = storage.end () - storage.begin ();

	size_t begin = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (storage.begin ()[i])
		{
			begin = i;
			break;
		}
	}

	size_t end = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (storage.begin ()[size-i-1])
		{
			end = size-i;
			break;
		}
	}

	return InitNumberView (storage, begin, size);
}

//----------------

template <class storage_t>
size_t Normalize (storage_t& storage)
{
	const char* begin = storage.begin ();
	const char* end   = storage.end   ();
	size_t size = end - begin;

	size_t first = 0;
	for (first; first < size && !begin[first]; first++);

	Number <NumberDataView> view = InitNumberView (storage);
	view = view << first;

	return first;
}

//----------------

template <class storage_t>
template <class data_t>
Number <storage_t>::Number (data_t& data) :
	m_storage (data.begin (), data.end ())
{}

//----------------

template <class storage_t>
char* Number <storage_t>::begin ()
{
	return m_storage.begin ();
}

template <class storage_t>
const char* Number <storage_t>::begin () const
{
	return m_storage.begin ();
}

//----------------

template <class storage_t>
char* Number <storage_t>::end ()
{
	return m_storage.end ();
}

template <class storage_t>
const char* Number <storage_t>::end () const
{
	return m_storage.end ();
}

//----------------

template <class storage_t>
size_t Number <storage_t>::size () const
{
	return m_storage.end () - m_storage.begin ();
}

//----------------

template <class storage_t>
void Number <storage_t>::print (bool skip_nulls /*= false*/) const
{
	bool skipped = false;
	for (const char* data = begin (); data < end (); data++)
	{
		if (*data) skipped = true;

		if (skip_nulls && skipped || !skip_nulls)
			_putch ('0' + *data);
	}
}

//----------------

template <class storage_t>
void Number <storage_t>::debug_print () const
{
	const std::type_info& info = typeid (storage_t);

	printf ("Number debug info:\n");
	printf ("storage type: '%s'\n", info.name ());
	printf ("size:         %zu\n", size ());
	printf ("contains:     ["); print (); printf ("]\n");
	printf ("as decimal:   %llu\n", dec ());
	printf ("as character: '%c'\n", static_cast <wchar_t> (dec ()));
	printf ("as hex:       0x%02X\n", dec ());
}

//----------------

template <class storage_t>
unsigned long long Number <storage_t>::dec () const
{
	char* buffer = new char[size ()+1];
	to_str (buffer, size ());

	unsigned long long decimal = strtoull (buffer, nullptr, 2);

	delete[] (buffer);
	return decimal;
}

//----------------

template <class storage_t>
char* Number <storage_t>::to_str (char* buffer, size_t max) const
{
	const char* begin = m_storage.begin ();

	size_t size = this -> size ();
	for (size_t i = 0; i < size && i < max; i++)
		buffer[i] = '0' + begin[i];

	return buffer;
}

//----------------

template <class storage_t>
char& Number <storage_t>::operator[] (size_t index)
{
	assert (index < size ());
	return m_storage.begin () [index];
}

template <class storage_t>
const char& Number <storage_t>::operator[] (size_t index) const
{
	assert (index < size ());
	return m_storage.begin () [index];
}

//----------------

template <class storage_t>
template <class rgt_storage_t>
Number <storage_t>& Number <storage_t>::operator = (const Number <rgt_storage_t>& that)
{
	size_t lsize = size      ();
	size_t rsize = that.size ();

	for (size_t i = 0; i < lsize; i++)
		begin ()[lsize-i-1] = i < rsize? that.begin ()[rsize-i-1]: 0;

	return *this;
}

//----------------

template <class lft_storage_t, class rgt_storage_t>
bool operator == (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt)
{
	size_t lsize = lft.size ();
	size_t rsize = rgt.size ();

	const char* lbegin = lft.begin ();
	const char* rbegin = rgt.begin ();

	for (size_t i = 0; i < lsize || i < rsize; i++)
	{
		if      (i >= lsize && rbegin[rsize-i-1]) return false;
		else if (i >= rsize && lbegin[lsize-i-1]) return false;

		else if (lbegin[lsize-i-1] != rbegin[rsize-i-1]) return false;
	}

	return true;
}

template <class lft_storage_t, class rgt_storage_t>
bool operator != (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt)
{
	size_t lsize = lft.size ();
	size_t rsize = rgt.size ();

	const char* lbegin = lft.begin ();
	const char* rbegin = rgt.begin ();

	for (size_t i = 0; i < lsize || i < rsize; i++)
	{
		if      (i >= lsize && rbegin[rsize-i-1]) return true;
		else if (i >= rsize && lbegin[lsize-i-1]) return true;

		else if (lbegin[lsize-i-1] != rbegin[rsize-i-1]) return true;
	}

	return false;
}

//----------------

template <class lft_storage_t, class rgt_storage_t>
bool operator > (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt)
{
	size_t lsize = lft.size ();
	size_t rsize = rgt.size ();

	for (size_t i = 0; i < lsize || i < rsize; i++)
	{
		char lbit = (i < lsize)? lft[i]: 0;
		char rbit = (i < rsize)? rgt[i]: 0;

		if (lbit > rbit) return true;
		if (lbit < rbit) return false;
	}

	return false;
}

template <class lft_storage_t, class rgt_storage_t>
bool operator >= (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt)
{
	return lft > rgt || lft == rgt;
}

//----------------

template <class lft_storage_t, class rgt_storage_t>
bool operator < (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt)
{
	size_t lsize = lft.size ();
	size_t rsize = rgt.size ();

	for (size_t i = 0; i < lsize || i < rsize; i++)
	{
		char lbit = (i < lsize)? lft[i]: 0;
		char rbit = (i < rsize)? rgt[i]: 0;

		if (lbit < rbit) return true;
		if (lbit > rbit) return false;
	}

	return false;
}

template <class lft_storage_t, class rgt_storage_t>
bool operator <= (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt)
{
	return lft < rgt || lft == rgt;
}

//----------------

template <class operand_storage_t>
Number <NumberData> operator ~ (const Number <operand_storage_t>& number)
{
	size_t size = number.size ();

	NumberData result_data;
	Number <NumberData> result (result_data);

	for (size_t i = 0; i < NumberData::DataSize; i++)
		result[NumberData::DataSize-i-1] = !(i < size? number[size-i-1]: 0);

	return result;
}

//----------------

template <class lft_storage_t, class rgt_storage_t>
Number <NumberData> operator + (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt)
{
	size_t lsize = lft.size ();
	size_t rsize = rgt.size ();

	Number <NumberData> result = InitNumber ();

	char remainder = 0;
	for (size_t i = 0; i < lsize || i < rsize; i++)
	{
		char lbit = (i < lsize)? lft[lsize-i-1]: 0;
		char rbit = (i < rsize)? rgt[rsize-i-1]: 0;

		char sum = lbit + rbit + remainder;
		result[result.size ()-i - 1] = sum % 2;
		remainder = sum / 2;
	}

	return result;
}

//----------------

template <class lft_storage_t, class rgt_storage_t>
Number <NumberData> operator - (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt)
{
	return lft + ~rgt + InitNumber ("1");
}

//----------------

template <class lft_storage_t, class rgt_storage_t>
Number <NumberData> operator * (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt)
{
	NumberData result_data;
	Number <NumberData> result = result_data;

	size_t lsize = lft.size ();
	size_t rsize = rgt.size ();

	for (size_t i = 0; i < lsize && i < rsize; i++)
		result[NumberData::DataSize-i-1] = lft[lsize-i-1] & rgt[rsize-i-1];

	return result;
}

//----------------

template <class lft_storage_t, class rgt_storage_t>
Number <NumberData> operator / (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt)
{
	Number <NumberDataView> dividing = InitNumberView (lft);
	Number <NumberDataView> divider  = InitNumberView (rgt);
	Number <NumberData> result = InitNumber ();

	if (divider == InitNumber ("0")) throw std::overflow_error ("division by zero");
					  
	size_t N = Normalize (divider) + 1;

	while (N)
	{
		result = result << 1;

		auto diff = dividing - divider;
		if (dividing >= divider)
		{
			result[result.size () - 1] = 1;
			dividing = diff;
		}
	
		divider = divider >> 1;
	
		N--;
	}

	return result;
}

//----------------

template <class lft_storage_t, class rgt_storage_t>
Number <NumberData> operator % (const Number <lft_storage_t>& lft, const Number <rgt_storage_t>& rgt)
{
	Number <NumberDataView> dividing = InitNumberView (lft);
	Number <NumberDataView> divider  = InitNumberView (rgt);
	Number <NumberData> result = InitNumber ();

	if (divider == InitNumber ("0")) throw std::overflow_error ("division by zero");
					  
	size_t N = Normalize (divider) + 1;

	while (N)
	{
		result = result << 1;

		auto diff = dividing - divider;
		if (dividing >= divider)
		{
			result[result.size () - 1] = 1;
			dividing = diff;
		}
	
		divider = divider >> 1;
	
		N--;
	}

	return dividing;
}

//----------------

template <class lft_storage_t>
Number <NumberData> operator >> (const Number <lft_storage_t>& lft, int shift)
{

	NumberData result_data;
	Number <NumberData> result (result_data);

	size_t size = lft.size ();
	for (size_t i = 0; i < size || i < NumberData::DataSize; i++)
	{
		size_t inv = size-i-1;

		if (i < NumberData::DataSize)
			result[NumberData::DataSize-i-1] = (inv-shift >= 0 && inv-shift < size)? lft[inv-shift]: 0;
	}

	return result;
}

template <class lft_storage_t>
Number <NumberData> operator << (const Number <lft_storage_t>& lft, int shift)
{
	return operator >> (lft, -shift);
}

//----------------