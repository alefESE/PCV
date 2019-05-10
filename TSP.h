
#pragma once

#include <iostream>
#include <tchar.h>
#include <chrono>
#include <random>
#include "leitorTSP.h"
#include "instanciaTSP.h"
#include "solucao.h"

#define INSTANCIAS 3
#define EXECS 10
vector<int> visitados;
vector<instanciaTSP> instancias(INSTANCIAS);
vector<instanciaTSP>::iterator i = instancias.begin();
random_device rd;
default_random_engine rng(rd());

// TODO: Referencie os cabeçalhos adicionais de que seu programa precisa aqui.