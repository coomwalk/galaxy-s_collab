#include "arithmetic.h"
#include "polinom.h"
#include <iostream>
#include <string>

int main()
{

	Polynom p1("-10x0y0z1 + 12x10y10z11 + 50.5x10y10z10");
	Polynom p2("40.4x10y10z10 + 50.5x10y10z10 + 0x0y0z0 + 10x4y4z4 + 0x0y0z0 + 0x0y0z0");
	string tmp = "(a+b)*3*c";//330x2y2z2
	arithmetic zxc(tmp);
	//ahahhahahahha it works!!!
	try
	{
		cout << zxc.try_calculate();
	}
	catch(char const* error_message)
	{
		std::cout<<error_message;
	}
	
	return 0;
}
