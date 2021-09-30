#include <iostream>

#include "conjunto.h"
#include "casilla.h"
#include "tablero.h"
#include "juego.h"
#include "listaSudokus.h"

using namespace std;


int menuPrincipal();
void elegirSudoku(tSudoku & sudoku);


int main()
{
	int opcion, puntos = 0;
	tSudoku sudoku;
	tJuego juego;
	do {
		opcion = menuPrincipal();

		if (opcion == 1)
		{
			elegirSudoku(sudoku);
			iniciaJuego(juego, sudoku);

			if (cargaJuego(juego, sudoku))
			{
				mostrarJuego(juego);
				puntos = jugarUnSudoku(sudoku);
			}
		}

	} while (opcion != 0);
	
	system("PAUSE");
	return 0;
}

int menuPrincipal()
{
	int opcion;
	cout << "1. Jugar" << endl;
	cout << "0. Salir" << endl;
	cout << endl << "Introduce una opcion: ";
	cin >> opcion;
	while (opcion < 0 || opcion > 1 || cin.fail())
	{
		cin.clear();
		cin.ignore();
		cout << "Opcion incorrecta. Introduce una opcion: ";
		cin >> opcion;
	}
	return opcion;
}

void elegirSudoku(tSudoku & sudoku)
{
	tListaSudokus lista;
	creaListaVacia(lista);
	int eleccion;
	if (cargar(lista)) 
	{
		mostrar(lista);
		cout << endl << "Introduce el numero del sudoku al que deseas jugar: ";
		cin >> eleccion;
		while (eleccion < 0 || eleccion >= lista.contador || cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Opcion incorrecta. Introduce una opcion: ";
			cin >> eleccion;
		}
		sudoku = lista.arraySudokus[eleccion - 1];
	}

	else
	{
		cout << "No se pudo abrir el fichero listaSudokus.txt" << endl;
	}

}