// APA.cpp: define o ponto de entrada para o aplicativo.
//

#include "APA.h"

int g(vector<int> t)
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
		custo += i.adj[s.rota[j]][s.rota[j+static_cast<int64_t>(1)]];
	return custo;
}

void construcaoGulosa(int g(vector<int> t), solucao& s)
{
	int aux = inicial;
	s.rota.push_back(aux);
	visitados.push_back(aux);
	vector<int> C = i.adj[aux]; //Inicialize o conjunto C de elementos candidatos;
	while (C.size() != 0)
	{
		int tmelhor = g(C);
		s.rota.push_back(tmelhor);
		s.custo += C[tmelhor];
		aux = tmelhor;
		//Atualize o conjunto C de elementos candidatos;
		C = s.rota.size() < i.dimensao ? i.adj[tmelhor] : vector<int>();
	}
	s.custo += i.adj[s.rota.back()][inicial];
	s.rota.push_back(inicial);
}

void VND(int f(solucao s), vector<solucao(*)(solucao)> N, size_t r, solucao &s)
{
	clock_t tick, tack;
	for (int k = 0; k < r; k++)
	{
		tick = clock();
		solucao si = N[k](s);
		tack = clock();
		tack - tick;
		//cout << "solução de N[" << k << "]: " << si.custo << endl;
		if (si.custo < s.custo)
		{
			s = si;
			k = 0;
		}
	}
}

solucao opt_2(solucao s, int i, int k)
{
	iter_swap(s.rota.begin() + i, s.rota.begin() + k);
	s.custo = f(s);
	return s;
}

solucao opt_2_best(solucao s)
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
		cout << "\rMovimentando na vizinhança 2op-t: " << progresso << "%";
		for (int i = 1; i < size - 2; i++)
		{
			for (int k = i + 1; k < size - 1; k++)
			{
				if (k == i) break;
				si = opt_2(s, i, k);
				if (!(si.custo < ret.custo)) continue;
				melhora = 0;
				ret = si;
			}
		}
		++melhora;
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

int main(int argc, char** argv)
{
	_tsetlocale(LC_ALL, _T("portuguese"));

	const char* command = argv[1];

	if (argc < 2)
	{
#ifdef _DEBUG
		command = "C:\\Users\\alef_\\OneDrive\\Área de Trabalho\\instancias\\instancias_teste\\ch150.txt";
#else
		cout << "Modo de uso: APA <caminho_arquivo.txt>";
		return -1;
#endif
	}

	cout << "Carregando arquivos..." << endl;
	leitor leitor(command);
	cout << "Construindo intancias..." << endl;
	leitor.constroi(i);

	solucao s;
	construcaoGulosa(g, s);

	vector<solucao (*)(solucao a)> N;
	N.push_back(opt_2_best);
	N.push_back(doubleBridge_best);
	//N.push_back(opt_3_best);
	cout << "Solução antes da VND:" << endl;
	s.print();
	VND(f, N, N.size(), s);
	cout << "Solução após da VND:" << endl;
	s.print();
	cout << "Gap: " << (s.custo - 6528.0) / 6528.0 * 100.0 << endl;
	i.print();
	return 0;
}
