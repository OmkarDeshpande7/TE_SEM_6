#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

struct literals{
	string index,lit,address;
}literal[20];


int main()
{
	string label, mnemonic, op1, op2;
	string index, symbol, address;
	fstream f1, f2, f3, f4, f5;
	int litcount = 0,litpool[10],i=0,currentpool=0;

	f1.open("intermediate-code.txt");
	if (f1.fail())
		return 0;

	f2.open("machine-code.txt",ios::out);
	if (f2.fail())
		return 0;
	
	f5.open("lit-pool.txt");
	if (f5.fail())
		return 0;
	
	
	f4.open("literaltable.txt");
	while (!f4.eof())
	{
		f4>>literal[i].index>>literal[i].lit>>literal[i++].address;	
		
	}
	f4.close();
	
	i=0;
	while(f5>>litcount)
		litpool[i++] = litcount;
	litcount=0;
	
	while (f1 >> label >> mnemonic >> op1 >> op2)
	{

			f2 << "\n" << label;
			f2 << "\t\t" << mnemonic.substr(4,2);
			if(!strcmp(mnemonic.c_str(),"(AD,05)")){
				for(int j=litcount;j<litpool[currentpool];j++)
					{
					f2<<"\n"<<literal[j].address<<"\t\t-\t\t-\t\t"<<literal[j].lit;
					}
					litcount=litpool[currentpool];
					currentpool++;
					continue;
			}
			if (op1 == "-")
				f2 << "\t\t" << op1;
			else
			{
				if (op1.substr(1, 1) == "R")
					f2 << "\t\t" << op1.substr(3, 2);
				else
					f2 << "\t\t" << op1.substr(4, 2);
			}
			if (op2 == "-")
				f2 << "\t\t" << op2;
			else if (op2.substr(1, 1) == "C")
			{
				
				f2 << "\t\t-";
			}
			else
			{
				if (op2.substr(1, 1) == "S")
				{
					f3.open("symboltable.txt");
					while (f3 >> index >> symbol >> address)
					{
						if (op2.substr(3, 1) == index)
							f2 << "\t\t" << address;
						else
							continue;
					}
					f3.close();
				}
				if (op2.substr(1, 1) == "L")
				{
					f4.open("literaltable.txt");
					while (f4 >> index >> symbol >> address)
					{
						if (op2.substr(3, 1) == index)
							f2 << "\t\t" << address;
						else
							continue;
					}
					f4.close();
				}
			}
	}
	f1.close();
	f2.close();
}
