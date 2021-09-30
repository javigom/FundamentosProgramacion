#pragma once

#include "conjunto.h"
#include "casilla.h"
#include "tablero.h"
#include "juego.h"
#include "checkML.h"

using namespace std;

const int MAX_SUDOKUS = 20;

typedef tSudoku tArraySudokus[MAX_SUDOKUS];

typedef struct {
	tArraySudokus arraySudokus;
	int contador;
}tListaSudokus;

void creaListaVacia(tListaSudokus & lista);
bool cargar(tListaSudokus & lista);
void mostrar(const tListaSudokus & lista);
bool guardar(const tListaSudokus & lista);
bool registrarSudoku(tListaSudokus & lista);
bool buscarFichero(const tListaSudokus & lista, string nombreFich);
int buscarPos(const tListaSudokus & lista, const tSudoku & sudoku);