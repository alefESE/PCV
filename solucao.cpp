#include "solucao.h"

void solucao::print()
{
	for (int c : this->rota)
		cout << c << " ";
	cout << endl;
	cout << "custo: " << this->custo << endl;
}