#include <iostream>

#include "conjunto.h"
#include "casilla.h"
#include "Windows.h"
#include "checkML.h"

using namespace std;

//Inicializa el estado de la casilla dada a vacío y su conjunto de valores posibles al conjunto [1,2,3,4,5,6,7,8,9]
void iniciaCasilla(tCasilla & casilla)
{
	casilla.estado = VACIA;
	cjto_lleno(casilla.conjunto);
}

//Rellena el estado y número de casilla de acuerdo con los valores de fija y c
void rellenaCasilla(tCasilla & casilla, char c, bool fija)
{
	
	if (c == ' ')
	{
		casilla.estado = VACIA;
		casilla.valor = 0;
	}
	else
	{
		if (fija)
		{
			casilla.estado = FIJA;
			casilla.valor = c - '0';
		}
		else
		{
			casilla.estado = RELLENADA;
			casilla.valor = c;
		}
		
	}
}

//Pinta en pantalla la casilla dada
void dibujaCasilla(const tCasilla & casilla)
{
	if (casilla.estado == VACIA)
	{
		colorFondo(0);
		cout << " ";
	}

	else if (casilla.estado == FIJA)
	{
		colorFondo(1);
		cout << casilla.valor;
	}
	else
	{
		colorFondo(4);
		cout << casilla.valor;
	}
	colorFondo(0);
}

void colorFondo(int color)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

//Devuelve un valor que indica si una cailla vacía tiene un único valor posible y, en caso afirmativo lo devuelve
bool esSimple(const tCasilla & casilla, int & numero)
{
	return esUnitario(casilla.conjunto, numero);
}

//FUNCIONES PROPIAS

//Devuelve true si la casilla esta vacia
bool casillaVacia(const tCasilla & casilla)
{
	return casilla.estado == VACIA;
}

//Devuelve true si num pertenece al conjunto de los posibles
bool casillaPertenece(const tCasilla & casilla, int num)
{
	return pertenece(casilla.conjunto, num);
}

//Dadas dos casillas, quita el numero de la segunda casilla de los posibles de la primera
void actualizaPosiblesCasilla(tCasilla & casillaBorrar, tCasilla & casillaNum)
{
	int c = casillaNum.valor;
	borraElemento(casillaBorrar.conjunto, c);
}

//Devuelve true si la casilla es fija
bool casillaFija(const tCasilla & casilla)
{
	return casilla.estado == FIJA;
}

//Muestra los valores posibles de una casilla
void mostrarPosiblesCasilla(const tCasilla & casilla)
{
	mostrar(casilla.conjunto);
}

//Dadas dos casillas, añade a los posibles el valor de la segunda en la primera
void annadeElementoCasilla(tCasilla & casillaAnnadir, tCasilla & casillaNum)
{
	int c = casillaNum.valor;
	annadeElemento(casillaAnnadir.conjunto, c);
}