#include "instancia.h"

instancia::instancia()
{
	nome = "";
	dimensao = 0;
	media_heuristica = 0.0;
	media_meta_heuristica = 0.0;
	adj = vector<vector<float>>();
}

instancia::~instancia()
{
	adj.clear();
}

void instancia::print()
{
	cout << nome << "\t" << dimensao << endl;
}

