#include "arithmetic.h"
#include "polinom.h"
#include "monom.h"
#include <iostream>
#include <string>

int main()
{

	Polynom p1("-10x0y0z1 + 12x10y10z11 + 50.5x10y10z10");
	Polynom p2("40.4x10y10z10 + 50.5x10y10z10 + 0x0y0z0 + 10x4y4z4 + 0x0y0z0 + 0x0y0z0");
	Monom m1(10, 10, 10, 10);
	

	//cin >> p1;
	cout << p2 * p1;
	return 0;
}
