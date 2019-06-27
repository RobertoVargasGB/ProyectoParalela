#ifndef OBJETOS_H
#define OBJETOS_H

using namespace std;

class Profesor{
public:
  Profesor();
  void llenar_profesor(string,string,string,int,vector<vector<string>>); //inicializa el profesor con los datos que se reciben por parametro
  void imprimir_profe();
  void cambiar_disponibilidad(vector<vector<string>>); //cambia la disponibilidad del profesor cuando se le asigna un ramo
  void agrega_disponibilidad(vector<string>, int);
  vector <vector< string>> disponibilidad_profesor; //Vector con 0 y 1, 0 es no disponible y 1 disponible
  int get_prioridad();
  int get_id();                                        //el primer vector representa el bloque y el segundo el día


private:
  string id_profesor;
  string nombres;
  string apellidos;
  int prioridad_profe;

};


class Sala{
public:
  Sala();
  void llenar_sala(int,string,string,string,vector<vector<string>>);
  void imprimir_sala ();

private:
  int id_sala;//identificacion unica de la Sala
  string nombre_sala;
  string edificio; //edificio al cual pertenece la Sala
  string numero_sala; //numero de Sala

};



class Secciones{ //Seccion de un curso que tiene asignado solo un profesor

public:

private:
  string id_curso;
  string id_profesor;

};



class Curso{ //Asignatura que tiene cantidad de bloques y un codigo de asignatura.
          //puede ser dictada por un profesor o más pero no en el mismo horario.
public:
  Curso();
  void llenar_curso(string,string,int,string) ;
  void imprimir_curso();
  int get_id_profesor();
  int get_bloques();
  int set_bloques();


private:
  string id_curso;
  string nombre_curso;
  int cantidad_bloques;
  string id_profesor;

};

#endif
