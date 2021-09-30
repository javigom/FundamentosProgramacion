#include <iostream>
#include <fstream>

#include "conjunto.h"
#include "casilla.h"
#include "tablero.h"
#include "juego.h"
#include "listaSudokus.h"
#include "jugador.h"
#include "listaJugadores.h"
#include "checkML.h"

using namespace std;

//Inicializa lista a una lista vacia
void creaListaVacia(tListaJugadores & lista)
{
	lista.contador = 0;
	lista.jugadores = new tJugador[MAX_JUGADORES];
	lista.capacidad = MAX_JUGADORES;
}

//Devuelve true si ha podido cargar en lista el contenido de listaJugadores.txt
bool cargar(tListaJugadores & lista)
{
	bool cargado = false;
	string id;
	int puntos;

	ifstream archivo;
	archivo.open("listaJugadores.txt");
	if (archivo.is_open())
	{
		archivo >> id;
		while (!archivo.eof())
		{
			if (lista.contador == lista.capacidad) //Si la lista está llena, duplico su capacidad
			{
				ampliar(lista);
			}
			archivo >> puntos;
			cargaJugador(lista.jugadores[lista.contador], id, puntos);
			lista.contador++;
			archivo >> id;
		}
		
		cargado = true;
		archivo.close();
	}
	return cargado;
}

//Muestra por pantalla la lista de jugadores recibida por parámetro
void mostrar(const tListaJugadores & lista)
{
	cout << endl << "Lista de jugadores registrados: " << endl;
	cout << "	" << "Identificador	Puntos" << endl;

	for (int i = 0; i < lista.contador; i++)
	{
		cout << "  " << i + 1 << ".	" << toString(lista.jugadores[i]) << endl;
	}
	cout << endl;
}

//Almacena en listaJugadores.txt el contenido de lista y devuelve un booleano indicando si fue posible
bool guardar(const tListaJugadores & lista)
{
	bool guardado = false;
	ofstream archivo;
	archivo.open("listaJugadores.txt");

	if (archivo.is_open())
	{
		for (int i = 0; i < lista.contador; i++)
		{
			archivo << toString(lista.jugadores[i]) << endl;
		}
		archivo.close();
		guardado = true;
	}

	return guardado;
}

//Actualiza los puntos de un jugador, solicitando su identificador
void puntuarJugador(tListaJugadores & lista, int puntos)
{
	int pos;
	string nombre;
	cout << "Introduce el identificador del jugador: ";
	cin >> nombre;
	int ini = 0, fin = lista.contador - 1;

	if (buscar(lista, nombre, pos, ini, fin)) //Si el nombre se encuentra en la lista, guarda la posicion en pos
	{
		modificarJugador(lista.jugadores[pos], puntos);
	}

	else
	{
		if (lista.contador == lista.capacidad) //Si la lista está llena, amplio la capacidad
		{
			ampliar(lista);
		}

		tJugador jugador;
		cargaJugador(jugador, nombre, puntos);

		for (int i = lista.contador; i > pos; i--)
		{
			lista.jugadores[i] = lista.jugadores[i - 1];
		}

		lista.jugadores[pos] = jugador;
		lista.contador++;
	}

	cout << "Puntuado correctamente." << endl;
	cout << "Puntuacion total del jugador " << nombre << ": " << puntosJugador(lista.jugadores[pos]) << " punto(s)." << endl << endl;
}

//Devuelve true si el jugador se encuentra en la lista. Esté o no, devuelve la posicion en la que deberia ser insertado o actualizado
bool buscar(const tListaJugadores & lista, string id, int & pos, int ini, int fin)
{
	//Búsqueda binaria recursiva
	bool encontrado = false;
	int mitad = (ini + fin) / 2;
	if (ini <= fin)
	{
		if (id == idJugador(lista.jugadores[mitad]))
		{
			pos = mitad;
			encontrado = true;
		}
		else if (id < idJugador(lista.jugadores[mitad]))
		{
			encontrado = buscar(lista, id, pos, ini, mitad - 1);
		}
		else
		{
			encontrado = buscar(lista, id, pos, mitad + 1, fin);
		}
	}

	else
	{
		pos = mitad + 1;
	}

	return encontrado;
}

//Ordena los jugadores de lista en funcion de los puntos y, en caso de empate, por su identificador
tListaJugadores ordenarPorRanking(const tListaJugadores & lista)
{
	tListaJugadores listaOrdenada; //Creo una nueva lista ordenada por ranking
	listaOrdenada.jugadores = new tJugador[lista.capacidad];
	listaOrdenada.contador = lista.contador;
	listaOrdenada.capacidad = lista.capacidad;

	for (int i = 0; i < lista.contador; i++) //Copio la lista a la nueva
	{
		listaOrdenada.jugadores[i] = lista.jugadores[i];
	}

	tJugador tmp;

	//Ordeno la lista por el método de la burbuja
	for (int i = 0; i < lista.contador - 1; i++)
	{
		for (int j = lista.contador - 1; j > i; j--)
		{
			if (menor(listaOrdenada.jugadores[j - 1], listaOrdenada.jugadores[j]))
			{
				tmp = listaOrdenada.jugadores[j];
				listaOrdenada.jugadores[j] = listaOrdenada.jugadores[j - 1];
				listaOrdenada.jugadores[j - 1] = tmp;
			}
		}
	}
	return listaOrdenada;
}

//Amplía la lista de jugadores al doble de su capacidad
void ampliar(tListaJugadores & lista)
{
	tJugadorPtr p = NULL;
	p = new tJugador[lista.capacidad * 2];
	tJugadorPtr j = NULL;
	j = p;

	for (int i = 0; i < lista.contador; i++) //Copio la lista a otro espacio de memoria más grande
	{
		*j = lista.jugadores[i];
		j++;
	}

	borrarListaJugadores(lista); //Libero la memoria anterior
	lista.jugadores = p; //Asigno el puntero p, al puntero de mi lista
	lista.capacidad = lista.capacidad * 2;
}

//Libera la memoria de reservada por la lista de jugadores
void borrarListaJugadores(tListaJugadores & lista)
{
	delete []lista.jugadores;
}