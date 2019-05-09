# CMakeList.txt: projeto de CMake para APA, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.8)

set(project_sources APA.cpp leitor.cpp instancia.cpp solucao.cpp)

# Adicione a origem ao executável deste projeto.
add_executable (APA ${project_sources})

# TODO: Adicione testes e instale destinos, se necessário.
