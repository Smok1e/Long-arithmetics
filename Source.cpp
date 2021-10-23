#include <TXLib.h>

#include "Decimal/Number.h"

//----------------

int main ()
{
	// кто прочитал тот сдохнет

	auto a = InitNumber ("12");
	auto b = InitNumber ("24");

	auto c = a * b;
	c.print ();
}

//----------------