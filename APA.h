// APA.h: arquivo de inclusão para arquivos de inclusão padrão do sistema,
// ou arquivos de inclusão específicos a um projeto.

#pragma once

#include <iostream>
#include <tchar.h>
#include <ctime>
#include <random>
#include "leitor.h"
#include "instancia.h"
#include "solucao.h"

vector<int> visitados;
instancia i;
constexpr auto inicial = 0;
random_device rd;
default_random_engine rng(rd());

// TODO: Referencie os cabeçalhos adicionais de que seu programa precisa aqui.