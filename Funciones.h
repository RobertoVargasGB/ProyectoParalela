
#ifndef _FUNCIONES_H_
#define _FUNCIONES_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <xlnt/xlnt.hpp>
#include <typeinfo>

#include "Objetos.h"
using namespace std;
using namespace xlnt;

//Crea matriz de una pagina.
vector<vector<string>> leer_pagina(xlnt::workbook wb, int index);

vector<Sala> leer_salas(xlnt::workbook wb);
vector<Curso> leer_cursos(xlnt::workbook wb);
vector<Profesor> leer_profes(xlnt::workbook wb);


void imprimir(vector<vector<string>> vector);
void imprimir_enteros(vector<vector<int>>vector);
void imprimir_vector_salas(vector<Sala> vector);
void imprimir_vector_cursos(vector<Curso> vector);
void imprimir_vector_profes(vector<Profesor> vector);

void escribir_xlsx(xlnt::workbook,string,int,string,int,int);
xlnt::workbook crear_archivo_salida(vector <Sala> salas);
void crear_horario(vector <Profesor> profes, vector <Sala> salas  , vector <Curso> cursos);
#endif
