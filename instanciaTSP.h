#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class vertex {
public:
	float x, y = 0;
	int id = 0;
	vertex() {}
};

class instanciaTSP
{
public:
	instanciaTSP();
	~instanciaTSP();

	void print();
	void constroi_adj();
	string nome;
	int dimensao;
	float media_heuristica;
	float media_meta_heuristica;
	vector<vertex> vertices;
	vector<vector<float>> adj;
private:
	float d(vertex a, vertex b);
};