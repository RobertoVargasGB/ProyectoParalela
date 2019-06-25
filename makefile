CXX= g++
CXXFLAGS = -std=c++14

FUENTE= main.cpp
NOMBRE= horario.out
XLSX = archivos/Cursos.xlsx archivos/Docentes.xlsx archivos/Salas.xlsx

CLASES= Objetos.cpp
FUNCIONES= Funciones.cpp

LIB = -Ixlnt/include -lxlnt



tarea:	$(FUENTE) $(CLASES) $(FUNCIONES)
	$(CXX) $(FUENTE) -o $(NOMBRE) $(CLASES) $(FUNCIONES) $(CXXFLAGS) $(LIB)
	clear
	./$(NOMBRE) $(XLSX)

ejecutar:
	./$(NOMBRE) $(XLSX)

clear:
	rm $(NOMBRE)
