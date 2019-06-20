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

  vector< vector<string> > vectorSheet = leer_pagina(xlscualquiera, 0);
  imprimir(vectorSheet);


  return 0;
}
