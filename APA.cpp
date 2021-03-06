﻿// APA.cpp: define o ponto de entrada para o aplicativo.
//

#include "APA.h"

float g(vector<float> t)
{
	int menor = INT_MAX;
	int tmelhor = 0;
	for (int i = 0; i < t.size(); i++)
	{
		if (!(find(visitados.begin(), visitados.end(), i) != visitados.end()) && t[i] && t[i] < menor)
		{
			menor = t[i];
			tmelhor = i;
		}
	}
	visitados.push_back(tmelhor);
	return tmelhor;
}

int f(solucao s)
{
	int custo = 0;
	for (int j = 0; j < s.rota.size() - 1; j++)
		custo += i->adj[s.rota[j]][s.rota[j + 1]];
	return custo;
}

solucao opt_2(solucao s, int j, int k)
{
	s.custo -= i->adj[s.rota[j - 1]][s.rota[j]];
	s.custo -= i->adj[s.rota[k - 1]][s.rota[k]];
	iter_swap(s.rota.begin() + j, s.rota.begin() + k);
	s.custo += i->adj[s.rota[j - 1]][s.rota[j]];
	s.custo += i->adj[s.rota[k - 1]][s.rota[k]];
	return s;
}

solucao opt_2_best(solucao s)
{
	solucao ret = s;
	solucao si;
	size_t size = s.rota.size();
	float progresso = 0.0;
	float passo = 100.0 / (size - 2);
	for (int i = 1; i < size - 2; i++)
	{
		cout << "\rMovimentando na vizinhança 2op-t: " << progresso << "%";
		for (int k = i + 1; k < size - 1; k++)
		{
			si = opt_2(s, i, k);
			if (!(si.custo < ret.custo)) continue;
			ret = si;
		}
		progresso += passo;
	}
	cout << "\rMovimentando na vizinhança 2op-t: 100%     " << endl;
	return ret;
}

solucao opt_3(solucao s, int i, int k, int j)
{
	iter_swap(s.rota.begin() + i, s.rota.begin() + k);
	iter_swap(s.rota.begin() + k, s.rota.begin() + j);
	s.custo = f(s);
	return s;
}
//O(N³) péssimo
solucao opt_3_best(solucao s)
{
	solucao ret = s;
	solucao si;
	size_t size = s.rota.size();
	//std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	float melhora = 0;
	float progresso = 0.0;
	float passo = 100.0 / 5;
	while (melhora < 5)
	{
		cout << "\rMovimentando na vizinhança 3op-t: " << progresso << "%";
		for (int i = 1; i < size - 3; i++)
		{
			for (int k = i + 1; k < size - 2; k++)
			{
				if (k == i) break;
				for (int j = k + 1; j < size - 1; j++)
				{
					if (j == k) break;
					si = opt_3(s, i, k, j);
					if (!(si.custo < ret.custo)) continue;
					melhora = 0;
					ret = si;
				}
			}
		}
		++melhora;
		progresso += passo;
	}
	cout << "\rMovimentando na vizinhança 3op-t: 100%     " << endl;
	return ret;
}

solucao doubleBridge(solucao s) {
	const size_t N = s.rota.size();
	vector<int> novaRota;
	novaRota.reserve(N);
	uniform_int_distribution<size_t> randomOffset(1, N / 4);
	size_t A = randomOffset(rng);
	size_t B = A + randomOffset(rng);
	size_t C = B + randomOffset(rng);
	copy(s.rota.begin(), s.rota.begin() + A, back_inserter(novaRota));
	copy(s.rota.begin() + C, s.rota.end(), back_inserter(novaRota));
	copy(s.rota.begin() + B, s.rota.begin() + C, back_inserter(novaRota));
	copy(s.rota.begin() + A, s.rota.begin() + B, back_inserter(novaRota));
	solucao ret(novaRota);
	ret.custo = f(ret);
	return ret;
}

solucao doubleBridge_best(solucao s)
{
	solucao ret = s;
	solucao si;
	size_t size = s.rota.size();
	float progresso = (float)0.0;
	float passo = (float)100.0 / size;
	for (int i = 0; i < size; i++)
	{
		cout << "\rMovimentando na vizinhança double bridge: " << progresso << "%";
		si = doubleBridge(s);
		if (si.custo < ret.custo)
		{
			progresso = 0.0;
			ret = si;
		}
		progresso += passo;
	}
	cout << "\rMovimentando na vizinhança double bridge: 100%     " << endl;
	return ret;
}

solucao get_solucao()
{
	solucao s;
	vector<int> valores;
	int aux = rand() % i->dimensao;
	s.rota.push_back(aux);
	for (int j = 0; j < i->dimensao; j++)
	{
		if (j == aux) continue;
		valores.push_back(j);
	}
	int idx;
	int n = valores.size();
	for (int i = 0; i < n; i++)
	{
		idx = rand() % (n - i);
		s.rota.push_back(valores[idx]);
		valores.erase(valores.begin() + idx);
	}
	s.rota.push_back(aux);
	s.custo = f(s);
	return s;
}

void construcaoGulosa(float g(vector<float> t), solucao & s)
{
	int aux = rand() % i->dimensao;
	s.rota.push_back(aux);
	visitados.push_back(aux);
	vector<float> C = i->adj[aux]; //Inicialize o conjunto C de elementos candidatos;
	while (C.size() != 0)
	{
		int tmelhor = g(C);
		s.rota.push_back(tmelhor);
		s.custo += C[tmelhor];
		//Atualize o conjunto C de elementos candidatos;
		C = s.rota.size() < i->dimensao ? i->adj[tmelhor] : vector<float>();
	}
	s.custo += i->adj[s.rota.back()][aux];
	s.rota.push_back(aux);
	visitados.clear();
}

void VND(int f(solucao s), vector<solucao(*)(solucao)> N, size_t r, solucao & s)
{
	int k = 0, n = 0;
	for (k = 0; k < r; k++)
	{
		solucao si = N[k](s);
		i->media_heuristica += si.custo; ++n;
		if (!(si.custo < s.custo)) continue;
		//cout << si.custo << " é melhor que " << s.custo << endl;
		s = si; k = 0;
	}
	i->media_heuristica = i->media_heuristica / n;
}

//Multi start
void MS(int f(solucao s), vector<solucao(*)(solucao)> N, int parada, solucao & s)
{
	solucao s0;
	int k = 0, n = 0;
	for (k = 0; k < parada; k++)
	{
		s0 = get_solucao();
		s0 = N[rand() % N.size()](s0);
		i->media_meta_heuristica += s0.custo; ++n;
		if (!(s0.custo < s.custo)) continue;
		//cout << s0.custo << " é melhor que " << s.custo << endl;
		s = s0; k = 0;
	}
	i->media_meta_heuristica = i->media_meta_heuristica / n;
}

int main(int argc, char** argv)
{
	_tsetlocale(LC_ALL, _T("portuguese"));
	srand(time(0));

	const char* desc = ".\\instancias_teste\\descricao.txt";
	vector<string> teste { ".\\instancias_teste\\bayg29.txt", ".\\instancias_teste\\bays29.txt", 
		".\\instancias_teste\\berlin52.txt", ".\\instancias_teste\\bier127.txt", 
		".\\instancias_teste\\brazil58.txt", ".\\instancias_teste\\ch130.txt", 
		".\\instancias_teste\\ch150.txt", ".\\instancias_teste\\swiss42.txt" };
	
	cout << "Lendo arquivos..." << endl;
	vector<solucao> solucoes; 
	vector<solucao> solucoes_meta;
	for (int j = 0; j < INSTANCIAS; j++)
	{
		leitor l(teste[j]);
		cout << "Construindo instância" << teste[j].substr(teste[j].find_last_of("/\\")) << "   \r";
		l.constroi(instancias[j]);
		solucao s;
		construcaoGulosa(g, s);
		solucoes.push_back(s);
		solucoes_meta.push_back(s);
		++i;
	}
	i = instancias.begin();
	cout << endl;
	ifstream arquivo;
	arquivo.open(desc);
	if (!arquivo.is_open()) return 1;
	string linha;
	vector<float> otimo;
	size_t pos;
	while (!arquivo.eof())
	{
		getline(arquivo, linha);
		if (pos = linha.find(i->nome) != string::npos) 
		{
			pos = linha.find("=");
			otimo.push_back(stof(linha.substr(pos+2)));
			++i;
		}
	}
	i = instancias.begin();
	vector<solucao(*)(solucao a)> N;
	N.push_back(opt_2_best);
	N.push_back(doubleBridge_best);
	//N.push_back(opt_3_best);

	cout << "Concluído" << endl;
	chrono::steady_clock::time_point tick, tack;
	for (int j = 0; j < INSTANCIAS; j++)
	{
		cout << "VND da instância " << instancias[j].nome << endl;
		tick = chrono::steady_clock::now();
		VND(f, N, N.size(), solucoes[j]);
		tack = chrono::steady_clock::now();
		solucoes[j].tempo = chrono::duration_cast<chrono::milliseconds>(tack - tick).count();
		//solucoes[j].print();
		
		cout << "Multi Start da instância " << instancias[j].nome << endl;
		tick = chrono::steady_clock::now();
		MS(f, N, EXECS, solucoes_meta[j]); //10 exec cada instancia
		tack = chrono::steady_clock::now();
		solucoes_meta[j].tempo = chrono::duration_cast<chrono::milliseconds>(tack - tick).count();
		//solucoes_meta[j].print();
		++i;
	}
	i = instancias.begin();
	string tab = "\t";
	cout << endl;
	cout << tab << "\t\tHeurística construtiva\t\t\tMeta-heurística" << endl;
	cout << tab << "\tótimo\tmédia\tmelhor\tmédia\tgap\tmédia\tmelhor\tmédia\tgap" << endl;
	cout << tab << "\t\tsolução\tsolução\ttempo\t\tsolução\tsolução\ttempo" << endl;
	for (int j = 0; j < INSTANCIAS; j++)
	{
		cout << instancias[j].nome;
		if (!(instancias[j].nome.size() >= 8))
			cout << tab;
		printf("\t%.0f\t%.1f\t%.0f\t%.0fms\t%.1f%%", otimo[j], i->media_heuristica, solucoes[j].custo, solucoes[j].tempo, ((solucoes[j].custo - otimo[j]) / otimo[j]) * 100.0);
		printf("\t%.1f\t%.0f\t%.0fms\t%.1f%%", i->media_meta_heuristica, solucoes_meta[j].custo, solucoes_meta[j].tempo, ((solucoes_meta[j].custo - otimo[j]) / otimo[j]) * 100.0);
		cout << endl;
		++i;
	}
	i = instancias.begin();
	for (solucao s : solucoes_meta)
		s.print();
	return 1;
}
