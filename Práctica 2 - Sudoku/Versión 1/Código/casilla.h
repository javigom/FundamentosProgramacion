#pragma once

#include "conjunto.h"

typedef enum { VACIA, FIJA, RELLENADA }tEstado;

typedef struct {
	tEstado estado;
	int valor;
	tConjunto conjunto;
}tCasilla;

void iniciaCasilla(tCasilla & casilla); //Inicializa el estado de la casilla dada a vacío y su conjunto de valores posibles al conjunto [1,2,3,4,5,6,7,8,9]
void rellenaCasilla(tCasilla & casilla, char c, bool fija); //Rellena el estado y número de casilla de acuerdo con los valores de fija y c
void dibujaCasilla(const tCasilla & casilla); //Pinta en pantalla la casilla dada
void colorFondo(int color); 
bool esSimple(const tCasilla & casilla, int & numero); //Devuelve un valor que indica si una cailla vacía tiene un único valor posible y, en caso afirmativo lo devuelve


//Funciones propias
bool casillaVacia(const tCasilla & casilla);
bool casillaPertenece(const tCasilla & casilla, int num);
void actualizaPosiblesCasilla(tCasilla & casillaBorrar, tCasilla & casillaNum);
bool casillaFija(const tCasilla & casilla);
void mostrarPosiblesCasilla(const tCasilla & casilla);