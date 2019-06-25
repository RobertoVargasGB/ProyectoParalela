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

//********************funciones de lectura de pagina e impresion ***************************

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

void imprimir_vector_salas (vector <Sala> vector){
  for (int i=0; i<vector.size();i++){
    Sala sala=vector.at(i);
    sala.imprimir_sala();
  }
}

void imprimir_vector_cursos (vector <Curso> vector){
  for (int i=0; i<vector.size();i++){
    Curso curso=vector.at(i);
    curso.imprimir_curso();
  }
}

void imprimir_vector_profes (vector <Profesor> vector){
  for (int i=0; i<vector.size();i++){
    Profesor sala=vector.at(i);
    sala.imprimir_profe();
  }
}

/*
void imprimir_vector_profes(vector <Profesor> vector){
  for(int i=0; i<vector.size();i++){
    Profesor profe=vector.at(i).at(0);
    if(i==3){
      for(int j=0; j<vector.size();j++){
        profe=vector.at(i).at(j);
      }
    }
    profe.imprimir_profe();

  }
}
*/




//********************funciones de lectura y llenado ***************************

vector <Curso> leer_cursos(xlnt::workbook wb){
  vector <Curso> lectura_cursos;
  // xlnt::workbook archivo_curso;
  // archivo_curso.load(argv[1]); //carga del xlxs

  //crea la matriz donde se guarda la lectura del archivo curso// vector <Curso> Cursos = leer_cursos(xlscualquiera);
  // imprimir_vector_cursos(Cursos);s
  vector <vector <string>> matriz_curso=leer_pagina(wb,0);

  for (int curso = 1; curso <matriz_curso.size(); curso++){
    string id_curso = matriz_curso.at(curso).at(0);
    string nombre_curso= matriz_curso.at(curso).at(1);
    string cantidad_bloques =matriz_curso.at(curso).at(5);
    Curso nuevo_curso;
    nuevo_curso.llenar_curso(id_curso,nombre_curso,cantidad_bloques);
    lectura_cursos.push_back(nuevo_curso);
  }
  return lectura_cursos;
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




// vector <Profesor> leer_profes(xlnt::workbook wb){
//   vector <Profesor> lectura_profes;
//   vector <vector<string>> matriz_profes=leer_pagina(wb,0);
//
//   for(int profe=0; profe<matriz_profes.size();profe++){
//     vector<vector<string>> matriz_disponibilidad;
//     string id_profesor=matriz_profes.at(profe).at(0); //se guarda la id del profe
//     string nombres=matriz_profes.at(profe).at(1); //se guardan nombres del profe
//     string apellidos=matriz_profes.at(profe).at(2); //se guardan apellidos del profe
//
//     for (int dia=0;dia <6; dia++){ // se recorre el archivo por dia para obtener la info de disponibilidad
//       vector <vector<string>> matriz_profes=leer_pagina(wb,dia); //se cambia de pagina
//       vector <string> disponibilidad_dia; // se crea el vector disponibilidad y se renueva cada día
//       for(int i=3; i<matriz_profes.at(profe).size(); i++){ // se recorren solo los campos de disponibilidad
//         string aux=matriz_profes.at(profe).at(i); //variable auxiliar donde se guarda la info de disponibilidad
//         if(aux[0]=='N'){ //se evalua con que letra parte la palabra de aux
//             disponibilidad_dia.push_back("0"); //si parte con N se agrega un 0 en el vector disponibilidad
//           }
//         else{
//           disponibilidad_dia.push_back("1"); //si no parte con N se agrega un 1 en el vecto disponibilidad
//         }
//
//       }
//       matriz_disponibilidad.push_back(disponibilidad_dia);
//     }
//
//     Profesor nuevo_profe;
//     nuevo_profe.llenar_profesor(id_profesor,nombres,apellidos,matriz_disponibilidad);
//     lectura_profes.push_back(nuevo_profe);
//   }
//   return lectura_profes;
//
// }



vector <Profesor> leer_profes(xlnt::workbook wb){
  vector <Profesor> lectura_profes;

  for (int dia=0;dia <6; dia++){
    if (dia==0){//crea los profesores y los agrega a un vector de tipo profesor
      vector <vector<string>> matriz_profes=leer_pagina(wb,0);
      for(int profe=0; profe<matriz_profes.size();profe++){
        vector<vector<string>> matriz_disponibilidad;
        vector <string> disponibilidad_dia;
        string id_profesor=matriz_profes.at(profe).at(0); //se guarda la id del profe
        string nombres=matriz_profes.at(profe).at(1); //se guardan nombres del profe
        string apellidos=matriz_profes.at(profe).at(2); //se guardan apellidos del profe

        for(int i=3; i<matriz_profes.at(profe).size(); i++){ // se recorren solo los campos de disponibilidad
          string aux=matriz_profes.at(profe).at(i); //variable auxiliar donde se guarda la info de disponibilidad
          if(aux[0]=='N'){ //se evalua con que letra parte la palabra de aux
              disponibilidad_dia.push_back("0"); //si parte con N se agrega un 0 en el vector disponibilidad
            }
          else{
            disponibilidad_dia.push_back("1"); //si no parte con N se agrega un 1 en el vecto disponibilidad
          }

        }
        matriz_disponibilidad.push_back(disponibilidad_dia);
        Profesor nuevo_profe;
        nuevo_profe.llenar_profesor(id_profesor,nombres,apellidos,matriz_disponibilidad);
        lectura_profes.push_back(nuevo_profe);
      }
    }

    if (dia !=0){ //modifica la disponibilidad de los profesores ya creados anteriormente
      vector <vector<string>> matriz_profes=leer_pagina(wb,dia); //se cambia de pagina
      for(int profe=0; profe<matriz_profes.size();profe++){
        vector <string> disponibilidad_dia;

        for(int i=3; i<matriz_profes.at(profe).size(); i++){ // se recorren solo los campos de disponibilidad
          string aux=matriz_profes.at(profe).at(i); //variable auxiliar donde se guarda la info de disponibilidad
          if(aux[0]=='N'){ //se evalua con que letra parte la palabra de aux
              disponibilidad_dia.push_back("0"); //si parte con N se agrega un 0 en el vector disponibilidad
            }
          else{
            disponibilidad_dia.push_back("1"); //si no parte con N se agrega un 1 en el vecto disponibilidad
          }

        }

        Profesor profesor=lectura_profes.at(profe);
        profesor.agrega_disponibilidad(disponibilidad_dia);
        lectura_profes.at(profe)=profesor;


      }
    }
    }
    return lectura_profes;
}
