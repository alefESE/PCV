#include "leitor.h"

leitor::leitor(string caminho)
{
	arquivo.open(caminho);
}

leitor::~leitor()
{
	arquivo.close();
}

void leitor::constroi(instancia &inst)
{
	string linha;
	size_t pos;

	if (!arquivo.is_open())
	{
		cout << "Não foi possível abrir o arquivo";
		exit(-1);
	}

	getline(arquivo, linha);
	if (pos = linha.find("NAME") != string::npos)
	{
		inst.nome = linha.substr(pos + 4);
		inst.nome.erase(remove_if(inst.nome.begin(), inst.nome.end(), isspace), inst.nome.end());
		//cout << inst->nome << endl;
	}
	else
	{
		cout << "Formato incorreto" << endl;
		exit(-2);
	}
	getline(arquivo, linha);
	if (pos = linha.find("DIMENSION") != string::npos)
	{
		inst.dimensao = stoi(linha.substr(pos + 9));
		//cout << inst->dimensao << endl;
	}
	else
	{
		cout << "Formato incorreto" << endl;
		exit(-2);
	}
	getline(arquivo, linha);
	if (pos = linha.find("EDGE_WEIGHT_SECTION") != string::npos)
	{
		inst.adj = vector<vector<int>>(inst.dimensao);
		regex re("[\\s,]+");
		for (int i = 0; i < inst.dimensao; i++)
		{
			getline(arquivo, linha);
			linha = trim(linha);

			vector<string> sep = split(linha, re);
			for (string s : sep)
			{
				inst.adj[i].push_back(stoi(s));
				//cout << inst.grafo[i].back().peso << endl;
			}
		}
	}
	else
	{
		cout << "Formato incorreto" << endl;
		exit(-3);
	}
}

vector<string> leitor::split(string str, regex re) {
	vector<string> internal;
	
	sregex_token_iterator it(str.begin(), str.end(), re, -1);
	sregex_token_iterator end;

	while (it != end) 
		internal.push_back(*it++);
	
	return internal;
}

string leitor::trim(const string& str)
{
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first)
	{
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}