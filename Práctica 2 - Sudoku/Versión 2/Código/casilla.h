#pragma once

#include "conjunto.h"
#include "checkML.h"

using namespace std;

typedef enum { VACIA, FIJA, RELLENADA }tEstado;

typedef struct {
	tEstado estado;
	int valor;
	tConjunto conjunto;
}tCasilla;

void iniciaCasilla(tCasilla & casilla); 
void rellenaCasilla(tCasilla & casilla, char c, bool fija); 
void dibujaCasilla(const tCasilla & casilla);
void colorFondo(int color); 
bool esSimple(const tCasilla & casilla, int & numero); 

//FUNCIONES PROPIAS
bool casillaVacia(const tCasilla & casilla);
bool casillaPertenece(const tCasilla & casilla, int num);
void actualizaPosiblesCasilla(tCasilla & casillaBorrar, tCasilla & casillaNum);
bool casillaFija(const tCasilla & casilla);
void mostrarPosiblesCasilla(const tCasilla & casilla);
void annadeElementoCasilla(tCasilla & casillaAnnadir, tCasilla & casillaNum);