#pragma once

#include "Objetos.h"
#include <xlnt/xlnt.hpp>

using namespace std;

//Crea matriz de una pagina.
vector<vector<string>> leer_pagina(xlnt::workbook wb, int index);

vector<Sala> leer_salas(xlnt::workbook wb);
void imprimir(vector<vector<string>> vector);
void imprimir_vector(vector<Sala> vector);
