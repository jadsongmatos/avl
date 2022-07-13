cmake_minimum_required(VERSION 3.5)

project(avl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

add_executable(avl main.cpp MinhaArvoreAVL.h ArvoreDeBuscaBinaria.h MinhaArvoreDeBuscaBinaria.h ListaEncadeadaAbstrata.h MinhaListaEncadeada.h Elemento.h excecoes.h)
target_link_libraries(avl GTest::GTest GTest::Main)
