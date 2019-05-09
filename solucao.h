#pragma once

#include <vector>
#include <iostream>

using namespace std;

class solucao
{
public:
	vector<int> rota;
	int custo = 0;
	solucao(vector<int> &rota) : rota(rota) {}
	solucao() {}

	void print();
};