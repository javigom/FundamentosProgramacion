#include <iostream>

#include "conjunto.h"
#include "casilla.h"
#include "Windows.h"

using namespace std;

void iniciaCasilla(tCasilla & casilla)
{
	casilla.estado = VACIA;
	cjto_lleno(casilla.conjunto);
}

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

bool esSimple(const tCasilla & casilla, int & numero)
{
	return esUnitario(casilla.conjunto, numero);
}

//Funciones propias

bool casillaVacia(const tCasilla & casilla)
{
	return casilla.estado == VACIA;
}

bool casillaPertenece(const tCasilla & casilla, int num)
{
	return pertenece(casilla.conjunto, num);
}

void actualizaPosiblesCasilla(tCasilla & casillaBorrar, tCasilla & casillaNum)
{
	int c = casillaNum.valor;
	borraElemento(casillaBorrar.conjunto, c);
}

bool casillaFija(const tCasilla & casilla)
{
	return casilla.estado == FIJA;
}

void mostrarPosiblesCasilla(const tCasilla & casilla)
{
	mostrar(casilla.conjunto);
}