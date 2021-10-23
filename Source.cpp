#include <TXLib.h>

#include "Decimal/Number.h"

//----------------

int main ()
{
	auto a = InitNumber ("12");
	auto b = InitNumber ("24");

	auto c = b * a;
	c.print ();
}

//----------------