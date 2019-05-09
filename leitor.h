#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <string>
#include <regex>
#include "instancia.h"

using namespace std;

class leitor
{
public:
	leitor(string caminho);
	~leitor();

	void constroi(instancia &i);

private:
	ifstream arquivo;

	vector<string> split(string str, regex re);
	string trim(const string& str);
};