CXX= g++
CXXFLAGS = -std=c++14

FUENTE= main.cpp
NOMBRE= horario
XLSX = archivos/Cursos.xlsx archivos/Docentes.xlsx archivos/Salas.xlsx Salida.xlsx

CLASES= Objetos.cpp
FUNCIONES= Funciones.cpp

LIB = -Ixlnt/include -lxlnt



Horario:	$(FUENTE) $(CLASES) $(FUNCIONES)
	$(CXX) $(FUENTE) -o $(NOMBRE) $(CLASES) $(FUNCIONES) $(CXXFLAGS) $(LIB)
	clear
	./$(NOMBRE) $(XLSX)

ejecutar:
	./$(NOMBRE) $(XLSX)

clear:
	rm $(NOMBRE)
