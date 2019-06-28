#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <xlnt/xlnt.hpp>

#include "Objetos.h"
#include "Funciones.h"

using namespace std;
using namespace xlnt;

int main (int argc, char *argv[]){

  xlnt::workbook xlscualquiera;
  xlscualquiera.load(argv[3]); //carga del xlsx

  // vector< vector<string> > vectorSheet = leer_pagina(xlscualquiera, 0);
  // imprimir(vectorSheet);

  //vector <Sala> Salitas = leer_salas(xlscualquiera);
  //imprimir_vector_salas(Salitas);

  //vector <Curso> Cursos = leer_cursos(xlscualquiera);
  // imprimir_vector_cursos(Cursos);

  //vector <Profesor> Profe = leer_profes(xlscualquiera);
  // imprimir_vector_profes(Profe);
  int cols = 4;
  int rows = 4;
  escribir_xlsx(cols, rows);
  return 0;
}
