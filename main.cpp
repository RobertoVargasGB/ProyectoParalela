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

  xlnt::workbook xls_salas,xls_profes,xls_cursos;
  xls_salas.load(argv[3]); //carga del xlsx
  xls_profes.load(argv[2]);
  xls_cursos.load(argv[1]);


  vector <Sala> Salas = leer_salas(xls_salas);

  vector <Curso> Cursos = leer_cursos(xls_cursos);

  vector <Profesor> Profe = leer_profes(xls_profes);




  xlnt::workbook Horario =crear_archivo_salida(Salas);
  //escribir_xlsx(Horario,"PROFE PRUEBA", 3, "CURSO PRUEBA",1,1);
  crear_horario(Profe,Salas,Cursos);
  imprimir_vector_salas(Salas);
  escribir_horario(Salas, Horario);

  return 0;
}
