#pragma once
#include <iostream>
#include <Address.h>
#include <Analysis.h>
#include <exception>
#include <AvlTree.h>
#include <cstring>

using namespace std;

int main(int argc, char **argv)
{
	try
	{
		Analysis analis("100records");
		for (int i = 0; i < analis.requests().size(); i++)
		{
			cout << analis[i].addr << endl;
		}
		Analysis::AddressAnalisys adAnalis(analis);
		adAnalis.calc_stack_dist();
	}
	catch (exception e)
	{
		cerr << e.what() << endl;
		cerr << "Program terminated." << endl;
		return 1;
	}
	system("pause");
	return 0;
}