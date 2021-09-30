#pragma once

#include "conjunto.h"
#include "casilla.h"
#include "tablero.h"
#include "juego.h"
#include "listaSudokus.h"
#include "jugador.h"
#include "checkML.h"

using namespace std;

const int MAX_JUGADORES = 5;

typedef struct {
	tJugadorPtr jugadores;
	int contador;
	int capacidad; 
}tListaJugadores;

void creaListaVacia(tListaJugadores & lista);
bool cargar(tListaJugadores & lista);
void mostrar(const tListaJugadores & lista);
bool guardar(const tListaJugadores & lista);
void puntuarJugador(tListaJugadores & lista, int puntos);
bool buscar(const tListaJugadores & lista, string id, int & pos, int ini, int fin);
tListaJugadores ordenarPorRanking(const tListaJugadores & lista);

void ampliar(tListaJugadores & lista);
void borrarListaJugadores(tListaJugadores & lista);