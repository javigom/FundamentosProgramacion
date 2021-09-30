#pragma once

#include <string>

#include "conjunto.h"
#include "casilla.h"
#include "tablero.h"
#include "checkML.h"

using namespace std;

typedef struct {
	int puntos;
	string nombre;
}tSudoku;

typedef struct {
	tSudoku sudoku;
	tTablero tablero;
	bool completo;
}tJuego;

void iniciaJuego(tJuego & juego, const tSudoku & sudoku);
void mostrarJuego(const tJuego & juego);
bool cargaJuego(tJuego & juego, const tSudoku & sudoku);
int jugarUnSudoku(const tSudoku & sudoku);

//FUNCIONES PROPIAS
int menuJuego();
void casillaValida(int & fila, int & col);
void valoresCasillaVacia(const tJuego & juego);
void colocarValorCasilla(tJuego & juego);
void borrarValorCasilla(tJuego & juego);
void cargaSudoku(tSudoku & sudoku, const string nombre, const int puntos);
void muestraSudoku(const tSudoku & sudoku, int pos);
void guardaSudoku(const tSudoku & sudoku, string & nombre, int & puntos);
bool comparaSudoku(const tSudoku & sudoku, string nombre);
int puntosSudoku(const tSudoku & sudoku);