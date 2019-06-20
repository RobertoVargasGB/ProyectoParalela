#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <xlnt/xlnt.hpp>
#include <typeinfo>

#include "Funciones.h"
#include "Objetos.h"


using namespace xlnt;
using namespace std;

//********************funciones de lectura e impresion ***************************

vector<vector<string>> leer_pagina(xlnt::workbook wb, int index){

  xlnt::worksheet pagina = wb.sheet_by_index(index);
  vector<vector<string> > matriz_pagina;
  for(auto fila : pagina.rows(false)) { //obtiene 1 fila completa
    vector<string> filas;
    for (auto celda : fila) //itera las celdas de la fila obtenida
      {
        filas.push_back(celda.to_string());
      }
      matriz_pagina.push_back(filas);

  }

  return matriz_pagina;
}

void imprimir(vector<vector<string>> vector){
  for (int i=0; i< vector.size(); i++){
      cout << "Esta fila dice: ";
    for (int j=0; j<vector.at(i).size(); j++){
      cout << vector.at(i).at(j) <<" ";
    }
    cout << " " << '\n';
  }
}

void imprimir_vector (vector <Sala> vector){
  for (int i=0; i<vector.size();i++){
    Sala sala=vector.at(i);
    string edificio= sala.edificio;
    string id=sala.id_sala;
    string numero=sala.numero_sala;
    cout << id << " " << edificio << " " <<numero<<endl;
  }

}


//********************funciones de llenado ***************************




vector <Curso> leer_cursos(char *argv[]){
  vector <Curso> lectura_cursos;
  xlnt::workbook archivo_curso;
  archivo_curso.load(argv[1]); //carga del xlxs

  //crea la matriz donde se guarda la lectura del archivo cursos
  vector <vector <string>> matriz_curso=leer_pagina(archivo_curso,0);

  for (int curso = 1; curso <matriz_curso.size(); curso++){
    string id_curso = matriz_curso.at(curso).at(0);
    string cantidad_bloques =matriz_curso.at(curso).at(5);
    Curso nuevo_curso;
    nuevo_curso.llenar_curso(id_curso,cantidad_bloques);
    lectura_cursos.push_back(nuevo_curso);
  }
}


vector <Sala> leer_salas(xlnt::workbook wb){
  vector <Sala> lectura_salas;
  // xlnt::workbook archivo_sala; //objeto donde se cargará el xlsx
  // archivo_sala.load(argv[3]); //carga del xlxs

  //crea la matriz donde se guarda la lectura del archivo salas
  vector< vector<string> > matriz_sala = leer_pagina(wb, 0);

  for (int sala = 1; sala < matriz_sala.size(); sala++){

    string edificio = matriz_sala.at(sala).at(0);
    string numero_sala = matriz_sala.at(sala).at(1);
    string id_sala = edificio + "-" + numero_sala;
    Sala nueva_sala;
    vector <vector<string>> disponibilidad;

    nueva_sala.llenar_sala(id_sala,edificio,numero_sala,disponibilidad);

    lectura_salas.push_back(nueva_sala);
  }
  return lectura_salas;
}



/*
vector <Profesor> leer_profes(char *argv[]){
  vector <Profesor> lectura_profes;
  xlnt::workbook archivo_profes;
  archivo_profes.load(argv[]);

  //crea la matriz donde se guarda la lectura del archivo Docentes
  vector <vector<string>> matriz_profes=leer_pagina(archivo_profes,0);
  int cantidad_hojas= archivo_profes.sheets_count(); //se cuenta la cantidad de hojas del archivo Docentes

  for (int profe=1; profe< matriz_profes.size(); profe++){
    string id_profesor=matriz_profe.at(profe).at(0);
    string nombres=matriz_profe.at(profe).at(1);
    string apellidos=matriz_profe.at(profe).at(2);

    vector<vector< string>> matriz_disponibilidad;
    vector<string> disponibilidad_dia;
    for (int dia=0; dia< cantidad_hojas;dia++){
      disponibilidad_dia.push_back()


    }
  }
}
*/
