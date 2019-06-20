#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <Objetos.h>
#include xlnt;
using namespace std;

//************clase profesor************

//constructor
Profesor::Profesor(){
  this -> id_profesor = 0;
  this -> nombres = 0;
  this -> apellidos = 0;
  this -> disponibilidad_profesor = 0;
}
//funciones
Profesor::inicializar_disponibilidad (string id, string nombre, string apellido, vector <vector<string>> disponibilidad,){
  this -> id_profesor=id;
  this -> nombres = nombre;
  this -> apellidos =apellido;
  this -> disponibilidad_profesor = disponibilidad;
}
Profesor::cambiar_disponibilidad (vector>vector<string>> disponibilidad){
  this -> disponibilidad_profesor=disponibilidad;
}


//********clase sala*********
//constructor
Sala:Sala (){
  this -> id_sala=0;
  this -> edificio=0;
  this -> numero_sala = 0;

}
//funciones
Sala::llenar_sala(string id, string edificio, string numero, vector <vector<int>> disponibilidad){
  this -> id_sala=id;
  this -> edificio=edificio;
  this -> numero_sala=numero;

}

//*******clase Seccion**********
//constructor
/*
Secciones:Secciones(){
  this -> id_seccion=0;
  this -> id_curso=0;
  this -> id_sala=0;
  this ->id_profesor=0;
  this ->bloques_asignados=0;
  this ->horario=0;
}
Secciones::agregar_profesor()
*/

//**************clase curso*****************
Curso:Curso(){
  this -> id_curso=0;
  this -> cantidad_bloques=0;
  this -> profes_dictan=0;
}

Curso::llenar_curso(string id, string bloques){
  this -> id_curso=id;
  this -> cantidad_bloques=bloques;

}

Curso::agregar_profesor(string id_profesor){
  profes_dictan.push_back(id_profesor);

}
