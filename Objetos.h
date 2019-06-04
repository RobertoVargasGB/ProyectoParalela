#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdio.h>


class Profesor{
public:
  void agregar_disponibilidad(); //metodo que llena el vector dispinibilidad
                                //con 1 en el horario que el profesor se encuentra disponible

private:
  int id_profesor;
  string nombre;
  vector int disponibilidad (39,0); //Vector con 0 y 1, 0 es no disponible y 1 disponible

};

class Seccion{ //Seccion de un curso que tiene asignado solo un profesor, una sala y un horario.
              // Un profesor puede hacer mas de una seccion pero el horario debe ser distinto.

public:
  void agregar_profesor(); //metodo que agrega un profesor de acuerdo a su disponibilidad.
  void agregar_sala(); //metodo que agrega la sala y horario segun disponibilidad del profesor.


private:
  int id_seccion;
  int id_curso;
  int id_sala;
  int id_profesor;
  int bloques_asignados; //cantidad de bloques asignados de la asignatura.
  vector int horario(39,0); // vector que contiene el horario asignado para la Seccion
                            //se inicializa en 0 y se llena con 1 en el horario asignado.

  vector int bloques_diarios (6,4); // vector

};

class Curso{ //Asignatura que tiene cantidad de bloques y un codigo de asignatura.
          //puede ser dictada por un profesor o más pero no en el mismo horario.
public:
  void verificar_profesores(); //verifica los profesores que pueden dictar la Asignatura
                               //el resultado es arrojado a un vector que contiene el id del profesor.

  void
private:
  int id_curso;
  int cantidad_bloques;
  vector int profes_dictan;





};
