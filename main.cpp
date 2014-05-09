#pragma once
#include <iostream>
#include <Address.h>
#include <Analysis.h>
#include <exception>
#include <AvlTree.h>
#include <cstring>
#include <cstdlib>
using namespace std;

int main(int argc, char **argv)
{
	try
	{
		Analysis analis("records");
		cout << "Ok1" << endl;
		/*for (int i = 0; i < analis.requests().size(); i++)
		{
			cout << analis[i].addr << endl;
		}*/
		cout << "Ok2" << endl;
		Analysis::AddressAnalisys adAnalis(analis);
		adAnalis.calc_stack_dist();
	}
	catch (exception e)
	{
		cerr << e.what() << endl;
		cerr << "Program terminated." << endl;
		return 1;
	}
	
	/*const int NUM = 1000;
	for (int i = 0; i < NUM; i++)
	{
		char str[20];
		itoa(i, str, 10);
		Analysis analis(str);
		Analysis::TimeAnalisys t_analis(analis);
	}
	system("pause");*/
	return 0;
}