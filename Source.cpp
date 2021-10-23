#include <TXLib.h>

#include "Number.h"
#include "NumberTest.h"

//----------------

int main ()
{
	NumberSumTest  ("10110100", "10010110", "01001010");
	NumberSumTest  ("00000101", "00110000", "00110101");
	NumberSumTest  ("10011110", "01010001", "11101111");
	printf ("\n");

	NumberSubTest  ("00000100", "00001110", "11110110");
	NumberSubTest  ("10000010", "10110101", "11001101");
	NumberSubTest  ("10010001", "00010100", "01111101");
	printf ("\n");

	NumberMultTest ("10111101", "11110110", "10110100");
	NumberMultTest ("10110101", "10000111", "10000101");
	NumberMultTest ("10110000", "10011011", "10010000");
	printf ("\n");

	NumberDivTest  ("01110001", "00101100", "00000010");
	NumberDivTest  ("11011000", "01110010", "00000001");
	NumberDivTest  ("11011010", "10100000", "00000001");
	printf ("\n");

	NumberRemTest  ("10101101", "10110010", "10101101");
	NumberRemTest  ("10100010", "01001000", "00010010");
	NumberRemTest  ("10110000", "00110111", "00001011");
	printf ("\n");
}

//----------------