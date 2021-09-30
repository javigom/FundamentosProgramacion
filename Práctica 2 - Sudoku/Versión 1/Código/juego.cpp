#include <iostream>

using namespace std;

#include "conjunto.h"
#include "casilla.h"
#include "tablero.h"
#include "juego.h"

void iniciaJuego(tJuego & juego, const tSudoku & sudoku)
{
	juego.sudoku = sudoku;
	juego.completo = false;
	iniciaTablero(juego.tablero);
}

void mostrarJuego(const tJuego & juego)
{
	cout << endl << "Puntuacion maxima: " << juego.sudoku.puntos << endl;
	cout << "Nombre del fichero: " << juego.sudoku.nombre << endl;
	dibujarTablero(juego.tablero);
}

bool cargaJuego(tJuego & juego, const tSudoku & sudoku)
{
	return cargarTablero(sudoku.nombre, juego.tablero);
}

int jugarUnSudoku(const tSudoku & sudoku)
{
	tJuego juego;
	iniciaJuego(juego, sudoku);
	int opcion, puntos = 0;
	bool lleno = false;
	if (cargaJuego(juego, sudoku))
	{
		
		do {
			opcion = menuJuego();
			switch (opcion)
			{
			case 1: valoresCasillaVacia(juego);
					break;

			case 2: colocarValorCasilla(juego);
					break;

			case 3: borrarValorCasilla(juego);
					break;
			case 4: iniciaJuego(juego, sudoku);
					cargaJuego(juego, sudoku);
					break;
			case 5: rellenarSimples(juego.tablero);
					break;

			case 0: break;
			}

			if (opcion != 0)
			{
				dibujarTablero(juego.tablero);
			}
			
			if (tableroLleno(juego.tablero))
			{
				puntos = juego.sudoku.puntos;
				lleno = true;
			}
			
		} while ((opcion != 0) && !lleno);
	}

	else
	{
		cout << "No se ha podido cargar el juego. " << endl;
	}

	return puntos;
}

//Funciones propias

int menuJuego()
{
	int opcion;
	cout << "Opciones de juego:" << endl;
	cout << "1.- Ver posibles valores de una casilla vacia" << endl;
	cout << "2.- Colocar valor en una casilla" << endl;
	cout << "3.- Borrar valor de una casilla" << endl;
	cout << "4.- Reiniciar el tablero" << endl;
	cout << "5.- Autocompletar celdas simples" << endl;
	cout << "0.- Abortar la resolucion y volver al menu principal" << endl;
	cout << endl << "Introduce opcion: ";
	cin >> opcion;
	while (opcion < 0 || opcion > 5 || cin.fail())
	{
		cin.clear();
		cin.ignore();
		cout << "Opcion incorrecta. Introduce una opcion: ";
		cin >> opcion;
	}
	return opcion;
}

//Funcion que solicita una fila y una columna al usuario en el rango [1-9]
void casillaValida(int & fila, int & col)
{
	cout << "Introduce fila valida [1-9]: ";
	cin >> fila;
	while (fila < 1 || fila > 9 || cin.fail())
	{
		cin.clear();
		cin.ignore();
		cout << "Fila incorrecta. Introduce una fila valida [1-9]: ";
		cin >> fila;
	}

	cout << "Introduce columna valida [1-9]: ";
	cin >> col;
	while (col < 1 || col > 9 || cin.fail())
	{
		cin.clear();
		cin.ignore();
		cout << "Columna incorrecta. Introduce una columna valida [1-9]: ";
		cin >> col;
	}
}

void valoresCasillaVacia(const tJuego & juego)
{
	int fila, columna;
	casillaValida(fila, columna);
	mostrarPosibles(juego.tablero, fila - 1, columna - 1);
}

void colocarValorCasilla(tJuego & juego)
{
	int fila, columna, valor;
	casillaValida(fila, columna);
	do {
		cout << "Introduce el numero de la casilla: ";
		cin >> valor;
	} while (valor < 1 || valor > MAX);
	
	if (ponerNum(juego.tablero, fila - 1, columna - 1, valor))
	{
		cout << "Valor introducido correctamente." << endl;
	}
	else
	{
		cout << "No se pudo introducir el valor." << endl;
	}
}

void borrarValorCasilla(tJuego & juego)
{
	int fila, columna;
	casillaValida(fila, columna);
	if (borrarNum(juego.tablero, fila - 1, columna - 1))
	{
		cout << "Valor borrado correctamente. " << endl;
	}

	else
	{
		cout << "No se pudo eliminar el valor (casilla vacia o fija). " << endl;
	}
}

void cargaSudoku(tSudoku & sudoku, string nombre, int puntos)
{
	sudoku.puntos = puntos;
	sudoku.nombre = nombre;
}

void muestraSudoku(const tSudoku & sudoku, int pos)
{
	cout << "  " << pos + 1 << ".	" << sudoku.nombre << "		" << sudoku.puntos << endl;
}