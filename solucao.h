#pragma once

#include <vector>
#include <iostream>

using namespace std;

class solucao
{
public:
	vector<int> rota;
	float custo = 0.0;
	double tempo = 0.0;
	solucao(vector<int> &rota) : rota(rota) {}
	solucao() {}

	void print();
};