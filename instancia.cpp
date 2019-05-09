#include "instancia.h"

instancia::instancia()
{
	nome = "";
	dimensao = 0;
	adj = vector<vector<int>>();
}

instancia::~instancia()
{
	adj.clear();
}

void instancia::print()
{
	cout << nome << "\t" << dimensao << endl;
}

