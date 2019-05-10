#include "instanciaTSP.h"

instanciaTSP::instanciaTSP()
{
	nome = "";
	dimensao = 0;
	media_heuristica = 0.0;
	media_meta_heuristica = 0.0;
	adj = vector<vector<float>>();
}

instanciaTSP::~instanciaTSP()
{
	adj.clear();
}

void instanciaTSP::print()
{
	cout << nome << "\t" << dimensao << endl;
}

void instanciaTSP::constroi_adj()
{
	for (int i = 0; i < adj.size(); i++)
	{
		for (int j = 0; j < adj.size(); j++)
		{
			adj[i].push_back(0.0);
			if (i == j) adj[i][j] = 0;
			adj[i][j] = d(vertices[i], vertices[j]);
		}
	}
}

float instanciaTSP::d(vertex a, vertex b)
{
	const float x_diff = abs(a.x - b.x);
	const float y_diff = abs(a.y - b.y);
	return sqrt(x_diff * x_diff + y_diff * y_diff);
}