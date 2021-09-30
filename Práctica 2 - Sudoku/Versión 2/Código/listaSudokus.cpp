#include <iostream>
#include <fstream>
#include <string>

#include "conjunto.h"
#include "casilla.h"
#include "tablero.h"
#include "juego.h"
#include "listaSudokus.h"
#include "checkML.h"

using namespace std;

//Inicializa lista a una lista vacia
void creaListaVacia(tListaSudokus & lista)
{
	lista.contador = 0;
}

//Funcion que carga los sudokus del fichero listaSudokus.txt, devuelve true si la carga ha tenido éxito
bool cargar(tListaSudokus & lista)
{
	bool cargado = false;
	string nombre;
	int puntos;
	ifstream archivo;
	archivo.open("listaSudokus.txt");
	if (archivo.is_open())
	{
		archivo >> nombre;
		while (!archivo.eof() && (lista.contador < MAX_SUDOKUS))
		{
			archivo >> puntos;
			cargaSudoku(lista.arraySudokus[lista.contador], nombre, puntos);
			lista.contador++;
			archivo >> nombre;
		}
		cargado = true;
		archivo.close();
	}

	return cargado;
}

//Visualiza por pantalla la lista de sudokus dada
void mostrar(const tListaSudokus & lista)
{
	cout << endl << "Lista de sudokus registrados: " << endl;
	cout << "	" << "Fichero de carga	Puntos/Nivel" << endl;
	for (int i = 0; i < lista.contador; i++)
	{
		muestraSudoku(lista.arraySudokus[i], i);
	}
}

//Devuelve true si se ha podido guardar en el fichero el contenido de la lista
bool guardar(const tListaSudokus & lista)
{
	bool guardado = false;
	int puntos;
	string nombre;
	ofstream archivo;
	archivo.open("listaSudokus.txt");
	if (archivo.is_open())
	{
		for (int i = 0; i < lista.contador; i++)
		{
			guardaSudoku(lista.arraySudokus[i], nombre, puntos);
			archivo << nombre << " " << puntos << endl;
		}
		archivo.close();
		guardado = true;
	}

	return guardado;
}

//Solicita los datos de un nuevo sudoku, y si es posible lo almacena. Devuelve true si se ha podido realizar.
bool registrarSudoku(tListaSudokus & lista)
{
	bool registrado = true;
	string nombre;
	int puntos, posicion;
	cout << "Introduce el nombre del fichero: ";
	cin >> nombre;
	cout << "Introduce los puntos: ";
	cin >> puntos;
	tSudoku sudoku;
	cargaSudoku(sudoku, nombre, puntos);

	if (lista.contador == MAX_SUDOKUS)
	{
		registrado = false;
	}

	else
	{
		for (int i = 0; i < lista.contador; i++)
		{
			if (comparaSudoku(lista.arraySudokus[i], nombre))
			{
				registrado = false;
			}
		}
	}
	
	if (registrado)
	{
		tSudoku sudokuAux;
		posicion = buscarPos(lista, sudoku);
		for (int i = lista.contador; i > posicion; i--)
		{
			lista.arraySudokus[i] = lista.arraySudokus[i - 1];
		}
		lista.contador++;
		cargaSudoku(lista.arraySudokus[posicion], nombre, puntos);	
	}
	return registrado;
}

//Devuelve un booleano que indica si existe o no un sudoku en la lista con el nombre recibido
bool buscarFichero(const tListaSudokus & lista, string nombreFich)
{
	bool encontrado = false;
	for (int i = 0; i < lista.contador; i++)
	{
		if (comparaSudoku(lista.arraySudokus[i], nombreFich))
			encontrado = true;
	}
	return encontrado;
}

//Devuelve la posicion de la lista en la que se debería insertar un sudoku mediante búsqueda binaria
int buscarPos(const tListaSudokus & lista, const tSudoku & sudoku)
{
	bool encontrado = false;
	int ini = 0, fin = lista.contador - 1, mitad;
	int buscado = puntosSudoku(sudoku);
	while ((ini <= fin) && !encontrado)
	{
		mitad = (ini + fin) / 2;
		if (buscado == puntosSudoku(lista.arraySudokus[mitad]))
			encontrado = true;
		else if (buscado < puntosSudoku(lista.arraySudokus[mitad]))
			fin = mitad - 1;
		else
			ini = mitad + 1;
	}
	if (mitad == 0)
		return mitad;

	else
		return mitad + 1; 

	//POSICION REAL EN EL ARRAY: DE 0 A MAX - 1;
}