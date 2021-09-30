#include <iostream>
#include <fstream>

#include "conjunto.h"
#include "casilla.h"
#include "tablero.h"
#include "juego.h"
#include "listaSudokus.h"

using namespace std;

void creaListaVacia(tListaSudokus & lista)
{
	lista.contador = 0;
}

bool cargar(tListaSudokus & lista)
{
	bool cargado = false;
	lista.contador = 0;
	string nombre;
	int puntos;
	ifstream archivo;
	archivo.open("listaSudokus.txt");
	if (archivo.is_open())
	{
		cargado = true;
		do {
			archivo >> nombre;
			archivo >> puntos;
			cargaSudoku(lista.arraySudokus[lista.contador], nombre, puntos);
			lista.contador++;
		} while (!archivo.eof());

		archivo.close();
	}

	return cargado;
}

void mostrar(const tListaSudokus & lista)
{
	cout << endl << "Lista de sudokus registrados: " << endl;
	cout << "	" << "Fichero de carga	Puntos/Nivel" << endl;
	for (int i = 0; i < lista.contador - 1; i++)
	{
		muestraSudoku(lista.arraySudokus[i], i);
	}
}