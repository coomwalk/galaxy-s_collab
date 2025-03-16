#include "arithmetic.h"
#include "polinom.h"
#include <iostream>
#include <string>
#include "all_table_header.h"

using namespace std;

int main()
{
	all_tables<string,Polynom> zxc;
	cout<<"      MENU     "<<endl;
	cout<<"1. ADD NEW POLINOM"<<endl;
	cout<<"2. CALCULATE ANYTHING"<<endl;
	cout<<"3. DELETE POLINOM"<<endl;
	cout<<"4. Find po key"<<endl;
	//cout<<"5. print table"<<endl; while not((
	cout<<"for exit program enter 0";

		int s;

		string name;
		string expression;
		string polinom_str;
		int choose_table;
		string name_of_new_pol;
		string key_for_find;
		do
		{
			cin>>s;
			switch (s)
			{
			case 1:
			{
				cout<<"input name of polynom(1 latin symvol)"<<endl;
				cin>>name;
				cout<<"input name polynom"<<endl;
				cin>>polinom_str;
				zxc.Insert(name,Polynom(polinom_str));

				break;
			}
			case 2:
			{
				cout<<"input expression: ";
				cin>>expression;
				cout<<"name of new polynom: ";
				cin>>name_of_new_pol;
				cout<<"choose your table"<<endl;
				cout<<"1. on vector"<<endl;
				cout<<"2. on AVL tree"<<endl;
				cout<<"3. on RB tree"<<endl;
				cin>>choose_table;
				cout<<zxc.calculate(expression,choose_table,name_of_new_pol)<<endl;

				break;
			}
			case 3:
			{
				cout<<"input name of polynom(1 latin symvol)"<<endl;
				cin>>name;
				zxc.Erase(name);

				break;
			}
			case 4:
			{
				cout<<"Input key: ";
				cin>>key_for_find;
				cout<<"choose your table"<<endl;
				cout<<"1. on vector"<<endl;
				cout<<"2. on AVL tree"<<endl;
				cout<<"3. on RB tree"<<endl;
				cin>>choose_table;
				cout<<zxc.Find(key_for_find, choose_table);
				break;
			}
			case 5:
				/* code */
				break;
		
			default:
			cout<<"It's fiasko"<<endl;
				break;
		}

		} while (s!=0);

	
	return 0;
}
