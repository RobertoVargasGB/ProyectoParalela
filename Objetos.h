#ifndef OBJETOS_H
#define OBJETOS_H

using namespace std;

class Profesor{
public:
  Profesor();
  void llenar_profesor(string,string,string,vector<vector<string>>); //inicializa el profesor con los datos que se reciben por parametro

  void cambiar_disponibilidad(vector<vector<string>>); //cambia la disponibilidad del profesor cuando se le asigna un ramo
private:
  string id_profesor;
  string nombres;
  string apellidos;
  vector <vector< string>> disponibilidad_profesor; //Vector con 0 y 1, 0 es no disponible y 1 disponible
                                                //el primer vector representa el dia y el segundo el bloque
};


class Sala{
public:
  Sala();
  void llenar_sala(string,string,string,vector<vector<string>>); //cambia la disponibilidad de la sala una vez que se asigna un curso en cierto horario


//private:
  string id_sala; //identificacion unica de la Sala
  string edificio; //edificio al cual pertenece la Sala
  string numero_sala; //numero de Sala

};


/*
class Secciones{ //Seccion de un curso que tiene asignado solo un profesor, una sala y un horario.
              // Un profesor puede hacer mas de una seccion pero el horario debe ser distinto.

public:
  void agregar_profesor(); //metodo que agrega un profesor de acuerdo a su disponibilidad.
  void agregar_sala(); //metodo que agrega la sala y horario segun disponibilidad del profesor.


private:
  string id_seccion;
  string id_curso;
  string id_sala;
  string id_profesor;
  string bloques_asignados; //cantidad de bloques asignados de la asignatura.
  vector <vector< int >> horario; // vector que contiene el horario asignado para la Seccion
                            //se inicializa en 0 y se llena con 1 en el horario asignado.
                            //el primer vector representa los dias y el segundo los bloques horarios
};

*/


class Curso{ //Asignatura que tiene cantidad de bloques y un codigo de asignatura.
          //puede ser dictada por un profesor o más pero no en el mismo horario.
public:
  Curso();
  void llenar_curso(string,string);
  void agregar_profesor(string);


private:
  string id_curso;
  string cantidad_bloques;



};

#endif
