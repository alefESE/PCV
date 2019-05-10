#include "leitorTSP.h"

leitorTSP::leitorTSP(string caminho)
{
	arquivo.clear();
	arquivo.open(caminho);
}

leitorTSP::~leitorTSP()
{
	arquivo.close();
}

void leitorTSP::constroi(instanciaTSP& inst)
{
	if (!arquivo.is_open())
	{
		cout << "Não foi possível abrir o arquivo";
		exit(-1);
	}
	string linha;
	size_t pos;

	getline(arquivo, linha);
	if (pos = linha.find("NAME") != string::npos)
	{
		inst.nome = linha.substr(pos + 4);
		inst.nome.erase(remove_if(inst.nome.begin(), inst.nome.end(), isspace), inst.nome.end());
		//cout << inst.nome << endl;
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
		//cout << inst.dimensao << endl;
	}
	else
	{
		cout << "Formato incorreto" << endl;
		exit(-2);
	}
	getline(arquivo, linha);
	if (pos = linha.find("DISPLAY_DATA_SECTION") != string::npos)
	{
		inst.adj = vector<vector<float>>(inst.dimensao);
		regex re("[\\s]+");
		for (int i = 0; i < inst.dimensao; i++)
		{
			getline(arquivo, linha);
			linha = trim(linha);
			vector<string> sep = split(linha, re);
			vertex v;
			v.id = stoi(sep[0]);
			v.x = stof(sep[1]);
			v.y = stof(sep[2]);
			inst.vertices.push_back(v);
		}
	}
	else
	{
		cout << "Formato incorreto" << endl;
		exit(-3);
	}
	inst.constroi_adj();
}

vector<string> leitorTSP::split(string str, regex re) {
	vector<string> internal;

	sregex_token_iterator it(str.begin(), str.end(), re, -1);
	sregex_token_iterator end;

	while (it != end)
		internal.push_back(*it++);

	return internal;
}

string leitorTSP::trim(const string & str)
{
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first)
	{
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}