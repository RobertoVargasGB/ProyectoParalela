#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <iostream>
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
void Profesor::llenar_profesor(string id, string nombre, string apellido,int prioridad, vector<vector<string>> disponibilidad){
  this -> id_profesor=id;
  this -> nombres = nombre;
  this -> apellidos =apellido;
  this -> prioridad_profe = prioridad;
  this -> disponibilidad_profesor=disponibilidad;

}
void Profesor::cambiar_disponibilidad(vector<vector<string>> disponibilidad){
  this -> disponibilidad_profesor=disponibilidad;
}

void Profesor::imprimir_profe(){


    cout << "Id: " << id_profesor<<endl;
    cout << "Nombres: " << nombres<<endl;
    cout << "Apellidos: " << apellidos<<endl;
    cout << "Prioridad:" <<prioridad_profe<<endl;
    imprimir(disponibilidad_profesor);
    cout<<endl;
}

void Profesor::agrega_disponibilidad(vector <string> disponibilidad_dia, int priority){

  disponibilidad_profesor.push_back(disponibilidad_dia);
  prioridad_profe=prioridad_profe+priority;

}

int Profesor::get_prioridad(){
  return prioridad_profe;
}
string Profesor::get_id(){
  return id_profesor;
}
vector<vector<string>> Profesor::get_disponibilidad_profesor(){
  return disponibilidad_profesor;

}
//********clase sala*********
//constructor
Sala::Sala (){
  this -> id_sala=0;
  this -> edificio="0";
  this -> numero_sala = "0";

}
//funciones
void Sala::llenar_sala(int id, string edificio, string numero,string nombre, vector <vector<string>> disponibilidad){
  this -> id_sala=id;
  this -> edificio=edificio;
  this -> numero_sala=numero;
  this -> nombre_sala=nombre;
  this -> disponibilidad_sala=disponibilidad;

}

void Sala::imprimir_sala(){
    cout << "sala " << id_sala <<"  "<<nombre_sala<< " "<< endl;
    imprimir(disponibilidad_sala);
    cout<<endl;
}

vector <vector<string>>Sala::get_disponibilidad_sala(){
  return disponibilidad_sala;
}

string Sala::get_nombre_sala(){
  return nombre_sala;
}
int Sala::get_id_sala(){
  return id_sala;
}

void Sala::set_disponibilidad(vector <vector<string>> disponibilidad_nueva){
  this -> disponibilidad_sala=disponibilidad_nueva;
}
//**************clase curso*****************
Curso::Curso(){
  this -> id_curso="0";
  this ->nombre_curso= "0";
  this -> cantidad_bloques="0";
}

void Curso::llenar_curso(string id,string nombre, string bloques, string id_profe){
  this -> id_curso=id;
  this -> nombre_curso= nombre;
  this -> cantidad_bloques=bloques;
  this -> id_profesor= id_profe;
}

void Curso::imprimir_curso(){


    cout << "Curso "<<nombre_curso <<",   codigo "<< id_curso <<" ,   cantidad de bloques :"<< cantidad_bloques<< "  , id profe: "<< id_profesor<<endl;
};

string Curso::get_id_profesor(){
    return id_profesor;
}

string Curso::get_bloques(){
  return cantidad_bloques;
}

void Curso::set_bloques(string bloques){
  this -> cantidad_bloques=bloques;
}

string Curso::get_id_curso(){
  return id_curso;
}
