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
};

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
    for(int j=0;j<Dias.size();j++){
      hoja_actual.cell(xlnt::cell_reference(j+2,1)).value(Dias.at(j));
      hoja_actual.cell(xlnt::cell_reference(1,j+2)).value(Bloques.at(j));
    }
  }
  Salida.save(dest_filename);
  return Salida;



}

void escribir_xlsx(xlnt::workbook Salida, string id_profe, int id_sala, string id_curso, int bloque, int dia ){
  string dest_filename = "salida.xlsx";
  xlnt::worksheet hoja = Salida.sheet_by_index(id_sala);
  hoja.cell(xlnt::cell_reference(dia, bloque)).value(id_curso + "-" + id_profe);
  Salida.save(dest_filename);
}


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
  // xlnt::workbook archivo_sala; //objeto donde se cargará el xlsx
  // archivo_sala.load(argv[3]); //carga del xlxs

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


void crear_horario(vector <Profesor> vector_profes, vector <Curso> vector_cursos, vector <Sala> vector_salas,xlnt::workbook Salida){

  for (int priority=0;priority<39;priority++){ // Se privilegia la prioridad del profe ante cualquier cosa

    for (int sala=0;sala<vector_salas.size();sala++){
      Sala nueva_sala=vector_salas.at(sala); // se obtiene la info de la sala actual en el objeto "nueva_sala" de tipo sala
      vector<vector<string>> disponibilidad_sala= nueva_sala.get_disponibilidad_sala(); // se guarda la disponibilidad de la sala actual

      for(int dia=5; dia>0; dia--){ // for para recorrer los dias partiendo del dia sabado

        if (dia==5){ // condicion si el dia es sabado

          for(int bloque=0;bloque<4;bloque++){ // recorriendo solo 4 bloques al ser sabado

            for(int profe=0;profe<vector_profes.size();profe++){ // se recorre el vector profes que ingresa por parametro
              Profesor nuevo_profe=vector_profes.at(profe);//se crea el objeto nuevo_profe con el fin de obtener la info de el
              int prioridad=nuevo_profe.get_prioridad(); // se guarda en una variable la prioridad del profe

              if(prioridad == priority){ // se encuentra al profesor con menor prioridad
                vector<vector<string>> disponibilidad_profe = nuevo_profe.get_disponibilidad_profesor(); // se guarda la disponibilidad del profesor actual

                for(int curso=0;curso<vector_cursos.size();curso++){ // se recorre el vector curso
                  Curso nuevo_curso=vector_cursos.at(curso); // se crea el obejto nuevo curos donde se rescata la info del curso dia_actual

                  if (nuevo_profe.get_id() == nuevo_curso.get_id_profesor()){ // se compara la id del profesor con la de los cursos, para ver si el profe realiza ese curos
                    string aux=nuevo_curso.get_bloques(); // se guarda en una variable auxiliar los bloques del curso
                    int aux2= stoi(aux,nullptr,10); // en otra variable auxiliar para pasar el dato de string a int que son los bloques del curso
                    int bloque_actual=bloque; //  es necesario (?)
                    int dia_actual=dia; //  es necesario (?)

                    while (aux2=!0){
                      if(disponibilidad_profe.at(bloque_actual).at(dia_actual)=="1"&&disponibilidad_sala.at(bloque_actual).at(dia_actual)=="1" ){ // se comprueba la disponibilidad tanto del profe como la de la sala

                        disponibilidad_profe.at(bloque_actual).at(dia_actual)="0"; // al usar la disponibilidad del profe se cambia a no disponible
                        disponibilidad_sala.at(bloque_actual).at(dia_actual)=="0"; // al usar la disponibilidad de la sala se cambia a no disponible
                        escribir_xlsx(Salida,nuevo_profe.get_id(),nueva_sala.get_id_sala(),nuevo_curso.get_id_curso(),bloque,dia); // funcion que escribe excel de salida
                        aux2=aux2-2;// se resta de a 2 ya que la cantidad de bloques corresponden a las horas pedagogicas
                      }
                    }
                  }
                }
              }
            } // cierre del for profe
          } // cierre del bloque
        } // cierre del dia sabado
        else{
          for(int bloque=0;bloque<7;bloque++){

            for(int profe=0;profe<vector_profes.size();profe++){ // se recorre el vector profes que ingresa por parametro
              Profesor nuevo_profe=vector_profes.at(profe);//se crea el objeto nuevo_profe con el fin de obtener la info de el
              int prioridad=nuevo_profe.get_prioridad(); // se guarda en una variable la prioridad del profe

              if(prioridad == priority){ // se encuentra al profesor con menor prioridad
                vector<vector<string>> disponibilidad_profe = nuevo_profe.get_disponibilidad_profesor(); // se guarda la disponibilidad del profesor actual

                for(int curso=0;curso<vector_cursos.size();curso++){ // se recorre el vector curso
                  Curso nuevo_curso=vector_cursos.at(curso); // se crea el obejto nuevo curos donde se rescata la info del curso dia_actual

                  if (nuevo_profe.get_id() == nuevo_curso.get_id_profesor()){ // se compara la id del profesor con la de los cursos, para ver si el profe realiza ese curos
                    string aux=nuevo_curso.get_bloques(); // se guarda en una variable auxiliar los bloques del curso
                    int aux2= stoi(aux,nullptr,10); // en otra variable auxiliar para pasar el dato de string a int que son los bloques del curso
                    int bloque_actual=bloque; //  es necesario (?)
                    int dia_actual=dia; //  es necesario (?)

                    while (aux2=!0){
                      if(disponibilidad_profe.at(bloque_actual).at(dia_actual)=="1"&&disponibilidad_sala.at(bloque_actual).at(dia_actual)=="1" ){ // se comprueba la disponibilidad tanto del profe como la de la sala
                        disponibilidad_profe.at(bloque_actual).at(dia_actual)="0"; // al usar la disponibilidad del profe se cambia a no disponible
                        disponibilidad_sala.at(bloque_actual).at(dia_actual)=="0"; // al usar la disponibilidad de la sala se cambia a no disponible
                        escribir_xlsx(Salida,nuevo_profe.get_id(),nueva_sala.get_id_sala(),nuevo_curso.get_id_curso(),bloque,dia); // funcion que escribe excel de salida
                        aux2=aux2-2;// se resta de a 2 ya que la cantidad de bloques corresponden a las horas pedagogicas
                      }
                    }
                  }
                }
              }
            } // cierre del for profe
          } // Cierre del for de bloques
        }// cierre del else

      } // cierre del dia
    }// cierre de la sala
  }// cierre de la prioridad
}
