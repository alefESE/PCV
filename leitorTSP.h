#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <string>
#include <regex>
#include "instanciaTSP.h"

using namespace std;

class leitorTSP
{
public:
	leitorTSP(string caminho);
	~leitorTSP();

	void constroi(instanciaTSP& i);

private:
	ifstream arquivo;

	vector<string> split(string str, regex re);
	string trim(const string& str);
};