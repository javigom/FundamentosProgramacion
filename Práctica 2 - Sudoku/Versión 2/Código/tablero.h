#pragma once

#include <string>

#include "conjunto.h"
#include "casilla.h"
#include "checkML.h"

using namespace std;

typedef tCasilla tTablero[MAX][MAX];

void iniciaTablero(tTablero tablero);
bool cargarTablero(string nombreFichero, tTablero tablero);
void dibujarTablero(const tTablero tablero);
bool ponerNum(tTablero tablero, int fila, int col, int c);
bool borrarNum(tTablero tablero, int fila, int col);
bool tableroLleno(const tTablero tablero);
void mostrarPosibles(const tTablero tablero, int fila, int col);
void rellenarSimples(tTablero tablero);

//FUNCIONES PROPIAS
void actualizarPosiblesTablero(tTablero tablero);
void actualizarPosiblesTableroFila(tTablero tablero, int fila, int col);
void actualizarPosiblesTableroCol(tTablero tablero, int fila, int col);
void actualizarPosiblesTableroCuadrado(tTablero tablero, int fila, int col);