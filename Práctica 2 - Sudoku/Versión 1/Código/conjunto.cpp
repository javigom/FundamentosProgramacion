#include <iostream>

#include "conjunto.h"

void cjto_vacio(tConjunto & c)
{
	for (int i = 0; i < MAX; i++)
	{
		c.arrayConjunto[i] = false;
	}
	c.contador = 0;
}

void cjto_lleno(tConjunto & c)
{
	for (int i = 0; i < MAX; i++)
	{
		c.arrayConjunto[i] = true;
	}
	c.contador = MAX;
}

bool pertenece(const tConjunto & c, int e)
{
	bool pertenece = false;
	int aux = e - 1;
	if (c.arrayConjunto[aux] == true)
	{
		pertenece = true;
	}
	return pertenece;
}

void annadeElemento(tConjunto & c, int e)
{
	int aux = e - 1;
	if (c.arrayConjunto[aux] == false)
	{
		c.arrayConjunto[aux] = true;
		c.contador++;
	}
}

void borraElemento(tConjunto & c, int e)
{
	int aux = e - 1;
	if (c.arrayConjunto[aux] == true)
	{
		c.arrayConjunto[aux] = false;
		c.contador--;
	}
}

int numElems(const tConjunto & c)
{
	return c.contador;
}

bool esUnitario(const tConjunto & c, int & e)
{
	bool unitario = false;
	int cont = 0;
	if (c.contador == 1)
	{
		while (!unitario && cont < MAX)
		{
			if (c.arrayConjunto[cont] == true)
			{
				unitario = true;
				e = cont + 1;
			}
			else
			{
				cont++;
			}
		}
	}
	return unitario;
}

void mostrar(const tConjunto & c)
{
	for (int i = 0; i < MAX; i++)
	{
		if (c.arrayConjunto[i] == true)
		{
			cout << i + 1 << " ";
		}
	}
	cout << endl;
}