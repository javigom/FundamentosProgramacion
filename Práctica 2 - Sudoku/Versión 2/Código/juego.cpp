#include <iostream>

#include "conjunto.h"
#include "casilla.h"
#include "tablero.h"
#include "juego.h"
#include "checkML.h"

using namespace std;

//Dado un juego y un sudoku, incializa el juego con la información del sudoku
void iniciaJuego(tJuego & juego, const tSudoku & sudoku)
{
	juego.sudoku = sudoku;
	juego.completo = false;
	iniciaTablero(juego.tablero);
}

//Muestra por pantalla la informacion del sudoku al que se va a jugar así como el tablero del mismo
void mostrarJuego(const tJuego & juego)
{
	cout << endl << "Puntuacion maxima: " << juego.sudoku.puntos << endl;
	cout << "Nombre del fichero: " << juego.sudoku.nombre << endl;
	dibujarTablero(juego.tablero);
}

//Actualiza el tablero del juego con el contenido del archivo contenido en sudoku
bool cargaJuego(tJuego & juego, const tSudoku & sudoku)
{
	return cargarTablero(sudoku.nombre, juego.tablero);
}

//Dado un sudoku, se inicia la ejecución del juego y devuelve los puntos obtenidos
int jugarUnSudoku(const tSudoku & sudoku)
{
	tJuego juego;
	iniciaJuego(juego, sudoku);
	int opcion, puntos = 0; //Se inicializa a 0 por si el jugador no termina la partida
	if (cargaJuego(juego, sudoku))
	{
		mostrarJuego(juego);
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
				juego.completo = true;
				cout << "Sudoku resuelto, buen trabajo." << endl;
				cout << "Has obtenido " << puntos << " punto(s)." << endl << endl;
			}
			
		} while ((opcion != 0) && !juego.completo);
	}

	else
	{
		cout << "No se ha podido cargar el juego. " << endl << endl;
	}

	return puntos;
}

//FUNCIONES PROPIAS

//Muestra el menu del juego y devuelve una opcion correcta
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

//Muestra los valores posibles de una casilla vacia
void valoresCasillaVacia(const tJuego & juego)
{
	int fila, columna;
	casillaValida(fila, columna);
	mostrarPosibles(juego.tablero, fila - 1, columna - 1);
}

//Coloca un valor en una casilla valida
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

//Borra el valor de una casilla
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

//Carga en sudoku el nombre y los puntos recibidos por parámetros
void cargaSudoku(tSudoku & sudoku, const string nombre, const int puntos)
{
	sudoku.puntos = puntos;
	sudoku.nombre = nombre;
}

//Muestra la informacion del sudoku recibido por parámetro
void muestraSudoku(const tSudoku & sudoku, int pos)
{
	cout << "  " << pos + 1 << ".	" << sudoku.nombre << "		" << sudoku.puntos << endl;
}

//Dado un sudoku, guarda en nombre y puntos el sudoku que hay cargado
void guardaSudoku(const tSudoku & sudoku, string & nombre, int & puntos)
{
	nombre = sudoku.nombre;
	puntos = sudoku.puntos;
}

//Devuelve true si el sudoku tiene el mismo nombre que la variable nombre recibida
bool comparaSudoku(const tSudoku & sudoku, string nombre)
{
	return sudoku.nombre == nombre;
}

//Devuelve los puntos del sudoku recibido por parametro
int puntosSudoku(const tSudoku & sudoku)
{
	return sudoku.puntos;
}