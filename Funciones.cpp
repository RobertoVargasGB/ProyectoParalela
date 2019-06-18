#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdio.h>

#include <Funciones.h>

//********************funciones de lectura ***************************
//funciones que leen xlsx y lo pasan a arreglos o matrices de objetos

vector<vector<string> > leer_pagina(xlnt::workbook wb, int index){
  xlnt::worksheet hojaActiva = wb.sheet_by_index(index);
  vector<vector<string> > matriz_pagina;
  for(auto fila : hojaActiva.rows(false)) {
    vector<string> filas;
    for (auto celda : fila)
      filas.push_back(celda.to_string());
      matriz_pagina.push_back(filas);
  }
  return matriz_pagina;
}

vector<Sala> leer_salas(char *argv[]){
  vector <Sala> lectura_salas;
  xlnt::workbook archivo_sala; //objeto donde se cargará el xlsx
  archivo_sala.load(argv[3]); //carga del xlsx

  //crea la matriz donde se guarda la lectura de la sala
  vector< vector<string> > matriz_sala = leer_pagina(archivo_sala, 0);

  for (int sala = 1; sala < matriz_sala.size(); sala++){

    string edificio = matriz_sala.at(sala).at(0);
    string numero_sala = matriz_sala.at(sala).at(1);
    string id_sala = edificio + "-" + numero_sala;
    Sala nueva_sala(id_sala,edificio,numero_sala);
    vectorInfoSala.push_back(nueva_sala);
  }
  return lectura_salas;
}
vector <Curso> leer_cursos(char *argv[]){



}
