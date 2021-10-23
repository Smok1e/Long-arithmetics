#pragma once

//----------------

class NumberDataView
{
public:
	NumberDataView (char* begin, char* end);
	NumberDataView (NumberData& data);
	NumberDataView (NumberData& data, size_t begin, size_t end);

	char*       begin ();
	const char* begin () const;

	char*       end ();
	const char* end () const;

	size_t size () const;

	NumberDataView& operator = (const NumberDataView& that);

	friend bool operator == (const NumberDataView& lft, const NumberDataView& rgt);
	friend bool operator != (const NumberDataView& lft, const NumberDataView& rgt);

protected:
	char* m_begin;
	char* m_end;

};

//----------------

NumberDataView::NumberDataView (char* begin, char* end) :
	m_begin (begin),
	m_end   (end)
{}

NumberDataView::NumberDataView (NumberData& data) :
	m_begin (data.begin ()),
	m_end   (data.end   ())
{}

NumberDataView::NumberDataView (NumberData& data, size_t begin, size_t end) :
	m_begin (data.begin () + begin),
	m_end   (data.begin () + end  )
{}

//----------------

char* NumberDataView::begin ()
{
	return m_begin;
}

const char* NumberDataView::begin () const
{
	return const_cast <const char*> (m_begin);
}

//----------------

char* NumberDataView::end ()
{
	return m_end;
}

const char* NumberDataView::end () const
{
	return const_cast <const char*> (m_end);
}

//----------------

size_t NumberDataView::size () const
{
	return m_end - m_begin;
}

//----------------

NumberDataView& NumberDataView::operator = (const NumberDataView& that)
{
	if (&that == this)
		return *this;

	m_begin = that.m_begin;
	m_end   = that.m_end;

	return *this;
}

//----------------

bool operator == (const NumberDataView& lft, const NumberDataView& rgt)
{
	size_t lsize = lft.size ();
	size_t rsize = rgt.size ();

	const char* lbegin = lft.begin ();
	const char* rbegin = rgt.begin ();

	for (size_t i = 0; i < lsize || i < rsize; i++)
	{
		if      (i >= lsize && rbegin[i]) return false;
		else if (i >= rsize && lbegin[i]) return false;

		else if (lbegin[i] != rbegin[i]) return false;
	}

	return true;
}

bool operator != (const NumberDataView& lft, const NumberDataView& rgt)
{
	size_t lsize = lft.size ();
	size_t rsize = rgt.size ();

	const char* lbegin = lft.begin ();
	const char* rbegin = rgt.begin ();

	for (size_t i = 0; i < lsize || i < rsize; i++)
	{
		if      (i >= lsize && rbegin[i]) return true;
		else if (i >= rsize && lbegin[i]) return true;

		else if (lbegin[i] != rbegin[i]) return true;
	}

	return false;
}

//----------------