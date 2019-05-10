#include "solucao.h"

void solucao::print()
{
	for (auto c : this->rota)
		cout << c << " ";
	cout << endl;
	cout << "custo: " << this->custo << endl;
}