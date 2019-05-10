// APA.h: arquivo de inclusão para arquivos de inclusão padrão do sistema,
// ou arquivos de inclusão específicos a um projeto.

#pragma once

#include <iostream>
#include <tchar.h>
#include <chrono>
#include <random>
#include "leitor.h"
#include "instancia.h"
#include "solucao.h"

#define INSTANCIAS 8
#define EXECS 10
vector<int> visitados;
vector<instancia> instancias(INSTANCIAS);
vector<instancia>::iterator i = instancias.begin();
random_device rd;
default_random_engine rng(rd());

// TODO: Referencie os cabeçalhos adicionais de que seu programa precisa aqui.