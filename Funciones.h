#pragma once

#include "Objetos.h"
#include <xlnt/xlnt.hpp>

using namespace std;

//Crea matriz de una pagina.
vector<vector<string>> leer_pagina(xlnt::workbook wb, int index);

vector<Sala> leer_salas(xlnt::workbook wb);
vector<Curso> leer_cursos(xlnt::workbook wb);
vector<Profesor> leer_profes(xlnt::workbook wb);


void imprimir(vector<vector<string>> vector);
void imprimir_vector_salas(vector<Sala> vector);
void imprimir_vector_cursos(vector<Curso> vector);
void imprimir_vector_profes(vector<Profesor> vector);
