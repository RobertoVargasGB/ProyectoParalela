#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <xlnt/xlnt.hpp>
#include <iostream>


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

void imprimir_enteros(vector<vector<int>> vector){
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


xlnt::workbook crear_archivo_salida(vector <Sala> salas){
  xlnt::workbook Salida;
  string dest_filename = "Salida.xlsx";
  vector <string> Dias={"LUNES","MARTES","MIERCOLES","JUEVES","VIERNES","SABADO"};
  vector <string> Bloques={"B1 08:00","B2 09:40","B3 11:20","B4 13:00","B5 14:40","B6 16:20","B7 18:00"};
  for(int i=0; i< salas.size();i++){
    Salida.create_sheet();
    xlnt::worksheet hoja_actual = Salida.sheet_by_index(i);
    string nombre_sala = salas.at(i).get_nombre_sala();
    hoja_actual.title(nombre_sala);
    for(int j=0;j<Bloques.size();j++){
      if (j==6){
        hoja_actual.cell(xlnt::cell_reference(1,j+2)).value(Bloques.at(j));
      }
      else{
        hoja_actual.cell(xlnt::cell_reference(j+2,1)).value(Dias.at(j));
        hoja_actual.cell(xlnt::cell_reference(1,j+2)).value(Bloques.at(j));
      }

    }
  }
  Salida.save(dest_filename);
  return Salida;



}

void escribir_xlsx(xlnt::workbook Salida, string id_profe, int id_sala, string id_curso, int bloque, int dia ){
  string dest_filename = "Salida.xlsx";
  xlnt::worksheet hoja = Salida.sheet_by_index(id_sala);
  hoja.cell(xlnt::cell_reference(dia+1, bloque+1)).value(id_curso + "-" + id_profe);
  Salida.save(dest_filename);
}


//********************funciones de lectura y llenado ***************************

vector <Curso> leer_cursos(xlnt::workbook wb){
  vector <Curso> lectura_cursos;
  // imprimir_vector_cursos(Cursos);
  vector <vector <string>> matriz_curso=leer_pagina(wb,0);

  for (int curso = 1; curso <matriz_curso.size(); curso++){
    string id_curso = matriz_curso.at(curso).at(0);
    string nombre_curso= matriz_curso.at(curso).at(1);
    string id_profe = matriz_curso.at(curso).at(2);
    string cantidad_bloques =matriz_curso.at(curso).at(5);
    Curso nuevo_curso;
    nuevo_curso.llenar_curso(id_curso,nombre_curso,cantidad_bloques,id_profe);
    lectura_cursos.push_back(nuevo_curso);
  }
  return lectura_cursos;
}

vector <Sala> leer_salas(xlnt::workbook wb){
  vector <Sala> lectura_salas;

  //crea la matriz donde se guarda la lectura del archivo salas
  vector< vector<string> > matriz_sala = leer_pagina(wb, 0);

  for (int sala = 1; sala < matriz_sala.size(); sala++){
    int id_sala = sala-1;
    string edificio = matriz_sala.at(sala).at(0);
    string numero_sala = matriz_sala.at(sala).at(1);
    string nombre_sala = edificio + "-" + numero_sala;
    Sala nueva_sala;
    vector <vector<string>> disponibilidad;
    for (int i=0;i<6;i++){
      if(i==5){
        vector <string> disponibilidad_dia;
        for(int j=0;j<4;j++){
          disponibilidad_dia.push_back("1");
        }
        disponibilidad.push_back(disponibilidad_dia);
      }
      else{
        vector <string> disponibilidad_dia;
        for (int j=0;j<7;j++){
          disponibilidad_dia.push_back("1");
        }
        disponibilidad.push_back(disponibilidad_dia);
      }
    }

    nueva_sala.llenar_sala(id_sala,edificio,numero_sala,nombre_sala,disponibilidad);

    lectura_salas.push_back(nueva_sala);
  }
  return lectura_salas;
}

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
        int priority = 0;
        for(int i=3; i<matriz_profes.at(profe).size(); i++){ // se recorren solo los campos de disponibilidad
          string aux=matriz_profes.at(profe).at(i); //variable auxiliar donde se guarda la info de disponibilidad
          if(aux[0]=='N'){ //se evalua con que letra parte la palabra de aux
              disponibilidad_dia.push_back("0"); //si parte con N se agrega un 0 en el vector disponibilidad
            }
          else{
            disponibilidad_dia.push_back("1"); //si no parte con N se agrega un 1 en el vecto disponibilidad
            priority++;
          }

        }
        matriz_disponibilidad.push_back(disponibilidad_dia);
        Profesor nuevo_profe;
        nuevo_profe.llenar_profesor(id_profesor,nombres,apellidos,priority,matriz_disponibilidad);
        lectura_profes.push_back(nuevo_profe);
      }
    }

    if (dia !=0){ //modifica la disponibilidad de los profesores ya creados anteriormente
      vector <vector<string>> matriz_profes=leer_pagina(wb,dia); //se cambia de pagina

      for(int profe=0; profe<matriz_profes.size();profe++){
        vector <string> disponibilidad_dia;
        int priority=0;
        for(int i=3; i<matriz_profes.at(profe).size(); i++){ // se recorren solo los campos de disponibilidad
          string aux=matriz_profes.at(profe).at(i); //variable auxiliar donde se guarda la info de disponibilidad
          if(aux[0]=='N'){ //se evalua con que letra parte la palabra de aux
              disponibilidad_dia.push_back("0"); //si parte con N se agrega un 0 en el vector disponibilidad
            }
          else{
            disponibilidad_dia.push_back("1"); //si no parte con N se agrega un 1 en el vecto disponibilidad
            priority++;
          }

        }

        Profesor profesor=lectura_profes.at(profe);
        profesor.agrega_disponibilidad(disponibilidad_dia, priority);
        lectura_profes.at(profe)=profesor;


      }
    }
  }
    return lectura_profes;
}



//******************Funcion que crea el horario************************
// *optimizable for de prioridad, cantidad de cursos de los profes.


void crear_horario(vector <Profesor> vector_profes, vector <Sala> &vector_salas, vector <Curso> vector_cursos){


  for (int priority=0;priority<39;priority++){ // for que va cambiando la prioridad de los profes


    for(int profe=0;profe<vector_profes.size();profe++){ // Recorre los profesores
      Profesor nuevo_profe=vector_profes.at(profe); // carga el objeto con la info del vector
      vector <vector<string>> disponibilidad_profe=nuevo_profe.get_disponibilidad_profesor(); // se crea una matriz que guarda la disponibilidad del profe
      // cout <<"Recorriendo profesor : "<<nuevo_profe.get_id()<<endl; // linea para saber que esta haciendo

      if (priority==nuevo_profe.get_prioridad()){ // busca a un profe con la prioridad actual del for anterior

        for(int curso=0;curso<vector_cursos.size();curso++){ // se recorre el vector cursos con el objetivo de obtener su info
          bool terminar_bucle=false;
          bool terminar_bucle1=false;
          bool terminar_while_inf_semana=false;
          Curso nuevo_curso=vector_cursos.at(curso); // Se carga el objeto con su info
          string id_curso=nuevo_curso.get_id_curso(); // se obtiene la id del curso
          string aux_bloques_curso=nuevo_curso.get_bloques();  // se tranforma de string a int
          int carga_academica= stoi(aux_bloques_curso,nullptr,10); // con la intencion de poder restar la carga despues
          // cout <<"Recorriendo curso :"<<nuevo_curso.get_id_curso()<<endl;

          if(id_curso[2]=='F'&&id_curso[0]=='I'){ // con la id del curso se sabe que tipo de curso es ( info u otro )

            if(nuevo_profe.get_id()==nuevo_curso.get_id_profesor()){ //verificar si el profe imparte el curso

              while (carga_academica>0){ //cantidad de bloques necesarias para el curso


              for(int sala=0;sala<vector_salas.size();sala++){ // Recorrre las salas
                Sala nueva_sala=vector_salas.at(sala); // objeto sala inicializado
                vector <vector<string>> disponibilidad_sala = nueva_sala.get_disponibilidad_sala(); // se obtiene la disponibilidad de la sala actual en una matriz
                string nombre_sala = nueva_sala.get_nombre_sala();
                // cout <<"Recorriendo sala: "<<nombre_sala<<endl;

                if(nombre_sala[0]=='L'){


                    for(int dia=5;dia>=0;dia--){ // se recorre por dia partiendo por el sabado hasta el lunes
                      // cout<<"recorriendo dia de la semana "<<dia<<endl; //

                      if(dia==5){ // si el dia es sabado

                          for (int bloque=0;bloque<4;bloque++){ // se recorren lo bloques de la sala actual
                            if (!carga_academica) break;
                            //cout <<"Recorriendo profesor : "<<nuevo_profe.get_id()<<"Recorriendo curso :"<<nuevo_curso.get_id_curso()<<"Recorriendo sala: "<<nombre_sala<<" recorriendo dia de la semana "<<dia<<" Recorriendo bloque: "<<bloque<<endl;
                            string disponibilidad_sala_instante = disponibilidad_sala.at(dia).at(bloque); // se guarda la disponibilidad de la sala actual
                            string disponibilidad_profe_instante= disponibilidad_profe.at(dia).at(bloque); // se guarda la disponibilidad del profe actual

                            if(disponibilidad_profe_instante=="1"&&disponibilidad_sala_instante=="1"){ // si el profe y la sala esta disponible
                              //cout <<"ASIGNANDO BLOQUE HORARIO"<<endl;
                              disponibilidad_profe.at(dia).at(bloque)="0"; // cambia a no disponible la disponibilidad actual del profe
                              disponibilidad_sala.at(dia).at(bloque)=nuevo_curso.get_id_curso()+ "-" + nuevo_profe.get_id(); // cambia la disponibildad de la sala y se guardan las id
                              nueva_sala.set_disponibilidad(disponibilidad_sala);
                              vector_salas.at(sala)=nueva_sala;
                              carga_academica=carga_academica-2;

                            }

                          }

                      } //if dia sabado
                      else{//si es otro dia distinto de sabado
                        // si la sala actual  es lab

                            for (int bloque=0;bloque<7;bloque++){ // se recorren lo bloques de la sala actual
                              if (carga_academica<=0) {
                                terminar_bucle=true;
                                break;
                              }
                            //  cout <<"Recorriendo profesor : "<<nuevo_profe.get_id()<<"Recorriendo curso :"<<nuevo_curso.get_id_curso()<<"Recorriendo sala: "<<nombre_sala<<" recorriendo dia de la semana "<<dia<<" Recorriendo bloque: "<<bloque<<endl;

                            string disponibilidad_sala_instante = disponibilidad_sala.at(dia).at(bloque); // se guarda la disponibilidad de la sala actual
                            string disponibilidad_profe_instante= disponibilidad_profe.at(dia).at(bloque); // se guarda la disponibilidad del profe actual

                            if(disponibilidad_profe_instante=="1"&&disponibilidad_sala_instante=="1"){ // si el profe y la sala esta disponible
                              //cout <<"ASIGNANDO BLOQUE HORARIO"<<endl;
                              disponibilidad_profe.at(dia).at(bloque)="0"; // cambia a no disponible la disponibilidad actual del profe
                              disponibilidad_sala.at(dia).at(bloque)=nuevo_curso.get_id_curso()+"-" + nuevo_profe.get_id(); // cambia la disponibildad de la sala y se guardan las id
                              nueva_sala.set_disponibilidad(disponibilidad_sala);
                              vector_salas.at(sala)=nueva_sala;
                              carga_academica=carga_academica-2;
                            }

                          }
                          if (terminar_bucle) {   //Para salir del bucle dia
                            terminar_bucle1=true;
                            break;
                          }

                      }//else otro dia
                    }
                    if (terminar_bucle1) {   //Para salir del bucle salas
                      terminar_while_inf_semana=true;
                      break;
                    }
                  nueva_sala.set_disponibilidad(disponibilidad_sala);
                  vector_salas.at(sala)=nueva_sala;
                  }
                }
                if (terminar_while_inf_semana) {
                  curso++;
                  break;
                }
              }//for salas
            }
          }//Cierre del if curso tipo informatica

          else{ // no es de info el curso
            if(nuevo_profe.get_id()==nuevo_curso.get_id_profesor()){ //verificar si el profe imparte el curso   //ESTE ESTA FUNCIONANDO
              string aux_bloques_curso=nuevo_curso.get_bloques();  // se tranforma de string a int
              int carga_academica= stoi(aux_bloques_curso,nullptr,10); // con la intencion de poder restar la carga despues

              while (carga_academica>0){ //cantidad de bloques necesarias para el curso

              for(int sala=0;sala<vector_salas.size();sala++){ // Recorrre las salas
                Sala nueva_sala=vector_salas.at(sala); // objeto sala inicializado
                vector <vector<string>> disponibilidad_sala = nueva_sala.get_disponibilidad_sala(); // se obtiene la disponibilidad de la sala actual en una matriz
                string nombre_sala = nueva_sala.get_nombre_sala();

                if(nombre_sala[0]!='L'){

                    for(int dia=5;dia>=0;dia--){ // se recorre por dia partiendo por el sabado hasta el lunes
                    //  cout<<"recorriendo dia de la semana"<<dia<<endl; //

                      if(dia==5){ // si el dia es sabado

                        for (int bloque=0;bloque<4;bloque++){ // se recorren lo bloques de la sala actual
                        //  cout <<"Recorriendo bloque: "<<bloque<<endl;
                          string disponibilidad_sala_instante = disponibilidad_sala.at(dia).at(bloque); // se guarda la disponibilidad de la sala actual
                          string disponibilidad_profe_instante= disponibilidad_profe.at(dia).at(bloque); // se guarda la disponibilidad del profe actual

                          if(disponibilidad_profe_instante=="1"&&disponibilidad_sala_instante=="1"){ // si el profe y la sala esta disponible
                        //    cout <<"ASIGNANDO BLOQUE HORARIO"<<endl;
                            disponibilidad_profe.at(dia).at(bloque)="0"; // cambia a no disponible la disponibilidad actual del profe
                            disponibilidad_sala.at(dia).at(bloque)=nuevo_curso.get_id_curso()+"-" + nuevo_profe.get_id(); // cambia la disponibildad de la sala y se guardan las id
                            nueva_sala.set_disponibilidad(disponibilidad_sala);
                            vector_salas.at(sala)=nueva_sala;
                            carga_academica=carga_academica-2;
                          }
                        }
                      }
                      else{
                          for (int bloque=0;bloque<7;bloque++){ // se recorren lo bloques de la sala actual
                          if (carga_academica<=0){
                            terminar_bucle=true;

                            break;
                          }
                        //  cout <<"Recorriendo bloque: "<<bloque<<endl;
                          string disponibilidad_sala_instante = disponibilidad_sala.at(dia).at(bloque); // se guarda la disponibilidad de la sala actual
                          string disponibilidad_profe_instante= disponibilidad_profe.at(dia).at(bloque); // se guarda la disponibilidad del profe actual

                          if(disponibilidad_profe_instante=="1"&&disponibilidad_sala_instante=="1" && carga_academica>0){ // si el profe y la sala esta disponible
                        //    cout <<"ASIGNANDO BLOQUE HORARIO"<<endl;
                            disponibilidad_profe.at(dia).at(bloque)="0"; // cambia a no disponible la disponibilidad actual del profe
                            disponibilidad_sala.at(dia).at(bloque)=nuevo_curso.get_id_curso()+"-" + nuevo_profe.get_id(); // cambia la disponibildad de la sala y se guardan las id
                            nueva_sala.set_disponibilidad(disponibilidad_sala);
                            vector_salas.at(sala)=nueva_sala;
                            carga_academica=carga_academica-2;
                          }
                        }
                        if (terminar_bucle) {   //Para salir del bucle dia
                          terminar_bucle1=true;
                          break;
                      }
                    }
                    nueva_sala.set_disponibilidad(disponibilidad_sala);
                    vector_salas.at(sala)=nueva_sala;

                    //cout <<carga_academica<<"despues de la resta "<<endl;
                  }
                  if (terminar_bucle1) {   //Para salir del bucle salas
                    terminar_while_inf_semana=true;
                    break;
                  }
                  nueva_sala.set_disponibilidad(disponibilidad_sala);
                  vector_salas.at(sala)=nueva_sala;
                }// for sala
              }
              if (terminar_while_inf_semana) {
                curso++;
                break;
              }
            }
          }//cierre else curso no informatica
        }
      }
    }
  }
}
}
