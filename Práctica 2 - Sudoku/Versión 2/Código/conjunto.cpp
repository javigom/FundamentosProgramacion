#include <iostream>

#include "conjunto.h"
#include "checkML.h"

using namespace std;

//Inicializa el conjunto c al conjunto vacío.
void cjto_vacio(tConjunto & c)
{
	for (int i = 0; i < MAX; i++)
	{
		c.arrayConjunto[i] = false;
	}
	c.contador = 0;
}

//Inicializa el conjunto c al conjunto formado por todos los valores del intervalo [1, 9].
void cjto_lleno(tConjunto & c)
{
	for (int i = 0; i < MAX; i++)
	{
		c.arrayConjunto[i] = true;
	}
	c.contador = MAX;
}

//Devuelve un booleano que indica si el elemento e (nº entero ∈ [1, 9]) se encuentra en el conjunto c.
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

//Mete el elemento e (nº entero ∈ [1, 9]) en el conjunto c.
void annadeElemento(tConjunto & c, int e)
{
	int aux = e - 1;
	if (c.arrayConjunto[aux] == false)
	{
		c.arrayConjunto[aux] = true;
		c.contador++;
	}
}

//Saca el elemento e (nº entero ∈ [1, 9]) del conjunto c.
void borraElemento(tConjunto & c, int e)
{
	int aux = e - 1;
	if (c.arrayConjunto[aux] == true)
	{
		c.arrayConjunto[aux] = false;
		c.contador--;
	}
}

//Devuelve el nº de elementos que hay en el conjunto c.
int numElems(const tConjunto & c)
{
	return c.contador;
}

//Devuelve un booleano que indica si el conjunto c tiene un único elemento y, de ser así, lo devuelve.
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

//Visualiza por pantalla los elementos del conjunto c.
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