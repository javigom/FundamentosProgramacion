//Javier Gómez Moraleda y Álvaro López olmos - 1ºF

//Bibliotecas
#include <iostream>

#include "conjunto.h"
#include "casilla.h"
#include "tablero.h"
#include "juego.h"
#include "listaSudokus.h"
#include "jugador.h"
#include "listaJugadores.h"
#include "checkML.h"

using namespace std;

//Funciones
int menuPrincipal();
void jugar(tListaSudokus & listaSudokus, tListaJugadores & listaJugadores);

//Función principal
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Detección de fugas

	int opcion;

	//Creación de listas: sudokus y jugadores
	tListaJugadores listaJugadores;
	tListaJugadores listaRanking;
	creaListaVacia(listaJugadores);

	tListaSudokus listaSudokus;
	creaListaVacia(listaSudokus);

	if (cargar(listaJugadores) && cargar(listaSudokus)) //Si se han podido cargar las listas, arranca el programa
	{
		do {
			opcion = menuPrincipal();

			//Juega una partida
			if (opcion == 1)
			{
				jugar(listaSudokus, listaJugadores);
			}

			//Muestra la lista en orden predeterminado (alfabético)
			else if (opcion == 2)
			{
				mostrar(listaJugadores);
			}

			//Muestra la lista en función de los puntos
			else if (opcion == 3)
			{
				listaRanking = ordenarPorRanking(listaJugadores);
				mostrar(listaRanking);
				borrarListaJugadores(listaRanking); 
			}

			//Registra un sudoku que no esté en la lista
			else if (opcion == 4)
			{
				if (registrarSudoku(listaSudokus))
					cout << "Sudoku registrado correctamente." << endl << endl;
				else
					cout << "No se pudo insertar." << endl << endl;
			}

			//Actualiza y guarda los ficheros tanto de sudokus como de jugadores antes de salir
			else
			{
				if (guardar(listaJugadores) && guardar(listaSudokus))
					cout << "Ficheros guardados y actualizados correctamente. Saliendo... " << endl << endl;
				else
					cout << "No se pudo guardar y/o actualizar algun fichero. " << endl << endl;

				//Libero la memoria ocupada por la lista al finalizar
				borrarListaJugadores(listaJugadores);
			}

		} while (opcion != 0);
	}

	else
	{
		cout << "No se pudo cargar correctamente algun fichero. " << endl;
	}
	
	system("PAUSE");
	return 0;
}

//Función que muestra el menú principal y devuelve una opción válida
int menuPrincipal()
{
	int opcion;
	cout << "1.- Jugar" << endl;
	cout << "2.- Ver jugadores ordenados por identificador" << endl;
	cout << "3.- Ver jugadores ordenados por puntos" << endl;
	cout << "4.- Incorporar sudoku" << endl;
	cout << "0.- Salir" << endl;
	cout << endl << "Introduce una opcion: ";
	cin >> opcion;
	while (opcion < 0 || opcion > 4 || cin.fail())
	{
		cin.clear();
		cin.ignore();
		cout << "Opcion incorrecta. Introduce una opcion: ";
		cin >> opcion;
	}
	return opcion;
}

//Función parajugar un sudoku
void jugar(tListaSudokus & listaSudokus, tListaJugadores & listaJugadores)
{
	int eleccion, puntos = 0;
	tSudoku sudoku;
	tJuego juego;

	mostrar(listaSudokus);
	cout << endl << "Introduce el numero del sudoku al que deseas jugar: ";
	cin >> eleccion;

	while (eleccion < 1 || eleccion > listaSudokus.contador || cin.fail())
	{
		cin.clear();
		cin.ignore();
		cout << "Opcion incorrecta. Introduce una opcion: ";
		cin >> eleccion;
	}

	sudoku = listaSudokus.arraySudokus[eleccion - 1];
	iniciaJuego(juego, sudoku);
	puntos = jugarUnSudoku(sudoku); //Devuelve los puntos de la partida

	if (puntos != 0) //Si devuelve 0, no se puntúa ya que no ha terminado el sudoku
	{
		puntuarJugador(listaJugadores, puntos);
	}
}
