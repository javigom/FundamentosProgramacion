#include <iostream>
#include <string>

#include "conjunto.h"
#include "casilla.h"
#include "tablero.h"
#include "juego.h"
#include "listaSudokus.h"
#include "jugador.h"
#include "checkML.h"

using namespace std;

//Guarda en un string el identificador y los puntos del jugador
string toString(tJugador jugador)
{
	return (jugador.id + "		" + to_string(jugador.puntos));
}

//Añade puntos a los puntos que lleva conseguidos el jugador dado
void modificarJugador(tJugador & jugador, int puntos)
{
	jugador.puntos = jugador.puntos + puntos;
}

//Sobrecarga de ddatos del operador < para datos del tipo tJugador
bool operator<(const tJugador & opIzq, const tJugador & opDer)
{
	return (opIzq.id < opDer.id);
}

//Devuelve true si el jugador j1 tiene menos puntos que j2. En caso de empate si el identificador de j2 es menor que el de j1.
bool menor(const tJugador & j1, const tJugador & j2)
{
	bool menor = false;
	if (j1.puntos < j2.puntos)
	{
		menor = true;
	}

	else if ((j1.puntos == j2.puntos) && (j2.id < j1.id))
	{
		menor = true;
	}

	return menor;
}

//FUNCIONES PROPIAS

//Guarda nombre y puntos en una estructura de tipi tJugador
void cargaJugador(tJugador & jugador, string id, int puntos)
{
	jugador.id = id;
	jugador.puntos = puntos;
}

//Función que devuelve el nombre del jugador
string idJugador(const tJugador & jugador)
{
	return jugador.id;
}

//Función que devuelve los puntos del jugador
int puntosJugador(const tJugador & jugador)
{
	return jugador.puntos;
}