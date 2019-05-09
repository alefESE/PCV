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
	vector<vector<int>> adj; 
};