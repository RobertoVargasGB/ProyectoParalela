#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdio.h>

#include <Funciones.h>


vector<vector<string> > leerPagina(xlnt::workbook wb, int index){
        xlnt::worksheet hojaActiva = wb.sheet_by_index(index);

        vector<vector<string> > matriz_pagina;

        for(auto fila : hojaActiva.rows(false)) {
                vector<string> filas;
                for (auto celda : fila)
                        filas.push_back(celda.to_string());

                matriz_pagina.push_back(vectorFilasIndividuales);
        }

        return matriz_pagina;
}
