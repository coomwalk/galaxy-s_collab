#include "arithmetic.h"
using namespace std;
int main()
{
  string input;
  cout << "Input mathematical expression: ";
  cin >> input;
  arithmetic zxc(input);
  double zibrail =  zxc.try_calculate() ;
  cout << endl << zxc.input_string_out() << endl;
  cout<<zxc.postfix_string_out() << endl;
  cout << endl << "RESULT: " << zibrail << endl;
  return 0;
}
