#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include "Objetos.h"
#include "Funciones.h"
#include <xlnt/xlnt.hpp>

using namespace xlnt;
using namespace std;

//************clase profesor************

//constructor
Profesor::Profesor(){
  this -> id_profesor = "0";
  this -> nombres = "0";
  this -> apellidos = "0";

}
//funciones
void Profesor::llenar_profesor(string id, string nombre, string apellido,vector<vector<string>> disponibilidad){
  this -> id_profesor=id;
  this -> nombres = nombre;
  this -> apellidos =apellido;
  this -> disponibilidad_profesor=disponibilidad;

}
  void Profesor::cambiar_disponibilidad(vector<vector<string>> disponibilidad){
  this -> disponibilidad_profesor=disponibilidad;
}

void Profesor::imprimir_profe(){


    cout << "Id: " << id_profesor<<endl;
    cout << "Nombres: " << nombres<<endl;
    cout << "Apellidos: " << apellidos<<endl;
    imprimir(disponibilidad_profesor);
}

void Profesor::agrega_disponibilidad(vector <string> disponibilidad){

  disponibilidad_profesor.push_back(disponibilidad);
}

//********clase sala*********
//constructor
Sala::Sala (){
  this -> id_sala="0";
  this -> edificio="0";
  this -> numero_sala = "0";

}
//funciones
void Sala::llenar_sala(string id, string edificio, string numero, vector <vector<string>> disponibilidad){
  this -> id_sala=id;
  this -> edificio=edificio;
  this -> numero_sala=numero;

}
void Sala::imprimir_sala(){

    string edif= edificio;
    string id=id_sala;
    string numero=numero_sala;
    cout << "sala " << id <<endl;
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
Curso::Curso(){
  this -> id_curso="0";
  this ->nombre_curso= "0";
  this -> cantidad_bloques="0";
}

void Curso::llenar_curso(string id,string nombre, string bloques){
  this -> id_curso=id;
  this -> nombre_curso= nombre;
  this -> cantidad_bloques=bloques;
}

void Curso::imprimir_curso(){

    string id=id_curso;
    string bloques=cantidad_bloques;
    cout << "Curso "<<nombre_curso <<",   codigo "<< id <<" ,   cantidad de bloques :"<<bloques<<endl;
}

  void Curso::agregar_profesor(string id_profesor){


}
