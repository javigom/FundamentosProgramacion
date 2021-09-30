#pragma once

using namespace std;

const int MAX = 9;

typedef bool arrayBool[MAX];

typedef struct {
	arrayBool arrayConjunto;
	int contador;
}tConjunto;

void cjto_vacio(tConjunto & c); //Inicializa el conjunto c al conjunto vacío.
void cjto_lleno(tConjunto & c); //Inicializa el conjunto c al conjunto formado por todos los valores del intervalo [1, 9].
bool pertenece(const tConjunto & c, int e); //Devuelve un booleano que indica si el elemento e (nº entero ∈ [1, 9]) se encuentra en el conjunto c.
void annadeElemento(tConjunto & c, int e); //Mete el elemento e (nº entero ∈ [1, 9]) en el conjunto c.
void borraElemento(tConjunto & c, int e); //Saca el elemento e (nº entero ∈ [1, 9]) del conjunto c.
int numElems(const tConjunto & c); //Devuelve el nº de elementos que hay en el conjunto c.
bool esUnitario(const tConjunto & c, int & e); //Devuelve un booleano que indica si el conjunto c tiene un único elemento y, de ser así, lo devuelve.
void mostrar(const tConjunto & c); //Visualiza por pantalla los elementos del conjunto c.