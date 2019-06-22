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





//********************funciones de lectura y llenado ***************************

vector <Curso> leer_cursos(xlnt::workbook wb){
  vector <Curso> lectura_cursos;
  // xlnt::workbook archivo_curso;
  // archivo_curso.load(argv[1]); //carga del xlxs

  //crea la matriz donde se guarda la lectura del archivo cursos
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




vector <Profesor> leer_profes(xlnt::workbook wb){
  vector <Profesor> lectura_profes;
  // xlnt::workbook archivo_profes;
  // archivo_profes.load(argv[]);
  int cantidad_hojas= wb.sheets_count(); //se cuenta la cantidad de hojas del archivo Docentes
  //crea la matriz donde se guarda la lectura del archivo Docentes
  vector <vector<string>> matriz_profes=leer_pagina(wb,0);
  vector<string> disponibilidad_dia;
  vector<vector< string>> matriz_disponibilidad;
  Profesor nuevo_profe;
  

  for (int profe=1; profe< matriz_profes.size(); profe++){ // se recorre la info obtenida por filas
    string id_profesor=matriz_profe.at(profe).at(0); // se guarda la id del profe
    string nombres=matriz_profe.at(profe).at(1); // se guardan nombres del profe
    string apellidos=matriz_profe.at(profe).at(2); // se guardan apellidos del profe
    for(int i=3;i<matriz_profe.size(); i++){
      string aux=matriz_profe.at(profe).at(i);
      if(aux[0]=='N'){
        disponibilidad_dia.push_back('0');
      }
      else{
        disponibilidad_dia.push_back('1');
      }
    nuevo_profe.llenar_profesor(id_profesor,nombres,apellidos);


    }


    }
  }
}
