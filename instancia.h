#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class instancia
{
public:
	instancia();
	~instancia();

	void print();
	string nome;
	int dimensao;
	float media_heuristica;
	float media_meta_heuristica;
	vector<vector<float>> adj;
};