#pragma once

#include "conjunto.h"
#include "casilla.h"
#include "tablero.h"
#include "juego.h"
#include "listaSudokus.h"
#include "checkML.h"

using namespace std;

typedef struct {
	string id;
	int puntos;
}tJugador;

typedef tJugador *tJugadorPtr;

string toString(tJugador jugador);
void modificarJugador(tJugador & jugador, int puntos);
bool operator<(const tJugador & opIzq, const tJugador & opDer);
bool menor(const tJugador & j1, const tJugador & j2);

//FUNCIONES PROPIAS
void cargaJugador(tJugador & jugador, string id, int puntos);
string idJugador(const tJugador & jugador);
int puntosJugador(const tJugador & jugador);