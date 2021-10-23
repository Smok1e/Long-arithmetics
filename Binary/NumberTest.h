#pragma once

//----------------

#ifdef def_number_unit_test
	#undef def_number_unit_test
#endif

#define def_number_unit_test(_name, _operator)															      \
void _name (const char* lft_str, const char* rgt_str, const char* expected_str)							      \
{																										      \
	auto lft = InitNumber (lft_str);																	      \
	auto rgt = InitNumber (rgt_str);																	      \
	auto exp = InitNumber (expected_str);																      \
	auto result = lft _operator rgt;																	      \
																										      \
	lft.print (); printf (" %s ", #_operator); rgt.print (); printf (" = "); result.print (); printf (" - "); \
																	                                          \
	if (result == exp)																					      \
	{																									      \
		$sG;																							      \
		printf ("OK!\n");																				      \
	}																									      \
	else																								      \
	{																									      \
		$sR;																							      \
		printf ("FAILED: "); exp.print (); printf (", got "); result.print (); printf ("\n");			      \
	}																									      \
}				

//----------------

def_number_unit_test (NumberSumTest,  +);
def_number_unit_test (NumberSubTest,  -);
def_number_unit_test (NumberMultTest, *);
def_number_unit_test (NumberDivTest,  /);
def_number_unit_test (NumberRemTest,  %);

//----------------