# CMakeList.txt: projeto de CMake para APA, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.8)

set(APA_sources APA.cpp leitor.cpp instancia.cpp solucao.cpp)
set(TSP_sources TSP.cpp leitorTSP.cpp instanciaTSP.cpp solucao.cpp)

# Adicione a origem ao executável deste projeto.
add_executable (APA ${APA_sources})
add_executable (TSP ${TSP_sources})

# TODO: Adicione testes e instale destinos, se necessário.
