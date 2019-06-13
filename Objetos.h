#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdio.h>


class Profesor{
public:
  void inicializar_disponibilidad(); //metodo que llena el vector dispinibilidad
                                //con 1 en el horario que el profesor se encuentra disponible

  void cambiar_disponibilidad(); //cambia la disponibilidad del profesor cuando se le asigna un ramo
private:
  int id_profesor;
  string nombre;
  vector int disponibilidad_profesor (39,1) //Vector con 0 y 1, 0 es no disponible y 1 disponible
                                            //se considera cada espacio del vector como un bloque horario
                                            //cada dia tiene 7 bloques, menos el sabado que tiene 4 bloques
};
class Sala{
public:
  void cambiar_disponibilidad(); //cambia la disponibilidad de la sala una vez que se asigna un curso en cierto horario
  void asignar_id(); //le asigna una id a la sala de acuerdo al numero y edificio

private:
  int id_sala; //identificacion unica de la Sala
  string edificio; //edificio al cual pertenece la Sala
  int numero; //numero de Sala
  vector int disponibilidad_sala (39,1); //funciona igual que la disponibilidad_profesor
}



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
