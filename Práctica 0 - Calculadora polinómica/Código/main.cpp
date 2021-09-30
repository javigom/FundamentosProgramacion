// Calculadora polinómica. Práctica realizada por Álvaro Lopez Olmos y Javier Gómez Moraleda (1ºF) 

//Bibliotecas
#include <iostream>
#include <cmath>

using namespace std;

const int MAX = 6;

typedef float tPolinomio[MAX];

//Prototipos funciones
int menu();
void leerPolinomio(tPolinomio polinomio);
void mostrarPolinomio(tPolinomio polinomio);
void derivarPolinomio(tPolinomio usuario, tPolinomio derivado);
bool integrarPolinomio(tPolinomio usuario, tPolinomio integrado);
float evaluar(tPolinomio usuario, float n);
void leerPolinomioGradoDos(tPolinomio usuario);
void calcularRaices(tPolinomio usuario);

//Función principal
int main()
{
	int op;
	float x, evaluado, sol1, sol2;
	tPolinomio usuario, deriv, integ;
	do {
		op = menu();

		if (op == 1) //Si la opción es 1, deriva el polinomio
		{
			leerPolinomio(usuario);
			cout << "Polinomio introducido: ";
			mostrarPolinomio(usuario);
			derivarPolinomio(usuario, deriv);
			cout << "Polinomio derivado: ";
			mostrarPolinomio(deriv);
			cout << endl;
		}

		else if (op == 2) //Si la opción es 2, integra el polinomio
		{
			cout << "(Solo para polinomios de grado 4 como maximo)" << endl;
			leerPolinomio(usuario);
			while (!integrarPolinomio(usuario, integ))
			{
				cout << "Introduce un polinomio cuyo coeficiente de grado 5 sea 0. " << endl;
				leerPolinomio(usuario);
				integrarPolinomio(usuario, integ);
			}
			cout << "Polinomio introducido: ";
			mostrarPolinomio(usuario);
			integrarPolinomio(usuario, integ);
			cout << "Polinomio integrado: ";
			mostrarPolinomio(integ);
			cout << endl;
		}

		else if (op == 3) //Si la opción es 3, evalua el polinomio
		{
			leerPolinomio(usuario);
			cout << "Introduce un valor de x: ";
			cin >> x;
			evaluado = evaluar(usuario, x);
			cout << "Polinomio introducido: ";
			mostrarPolinomio(usuario);
			cout << "El valor polinomio para x = " << x << " es " << evaluado << endl << endl;
		}

		else if (op == 4) //Si la opción es 4, calcula las raices del polinomio
		{
			leerPolinomioGradoDos(usuario);
			cout << "Polinomio introducido: ";
			mostrarPolinomio(usuario);
			calcularRaices(usuario);
		}

		else //Si la opción es 5, sale del programa
		{
			cout << "Has salido del programa." << endl;
		}

	} while (op != 5);

	system("PAUSE");
	return 0;
}

//Función que muestra el menú y pide una opcion al usuario entre 1 y 5
int menu() 
{
	int opcion;
	cout << "MENU: " << endl << endl;
	cout << "1-Derivar polinomio " << endl;
	cout << "2-Integrar polinomios" << endl;
	cout << "3-Evaluar" << endl;
	cout << "4-Calcular raices" << endl;
	cout << "5-Finalizar" << endl << endl;
	cout << "Elija opcion: ";
	cin >> opcion;

	while (cin.fail() || (opcion < 1) || (opcion > 5)) //Si la opción no es un entero y está entre 1 y 5, vuelve a solicitarla
	{
		cin.clear();
		cin.ignore();
		cout << "Opcion incorrecta. Introduce un numero del 1 al 5: ";
		cin >> opcion;
	}

	return opcion;
}

//FUnción que lee por pantalla el polinomio que introduce el usuario
void leerPolinomio(tPolinomio polinomio) 
{
	for (int i = 0; i < MAX; i++)
	{
		cout << "Introduce el coeficiente del grado " << i << " del polinomio: ";
		cin >> polinomio[i];
	}
}

//Función que muestra por pantalla el polinomio almacenado en el array
void mostrarPolinomio(tPolinomio polinomio)
{
	bool cero = true;

	for (int i = 0; i < MAX; i++) //Comprueba si el polinomio es 0
	{
		if (polinomio[i] != 0)
		{
			cero = false;
		}
	}

	if (cero) //Si el polinomio es 0, lo muestra por pantalla
	{
		cout << "0";
	}

	else 
	{
		for (int i = MAX - 1; i >= 0; i--)
		{
			if (polinomio[i] > 0)
			{
				if (i==0)
				{
					cout << "+" << polinomio[i];
				}
				else 
				{
					cout << "+" << polinomio[i] << "x" << i;
				}
			}
			else if (polinomio[i] < 0)
			{
				if (i == 0) 
				{
					cout << polinomio[i];
				}
				else
				{
					cout << polinomio[i] << "x" << i;
				}
				
			}
			
		}
		
	}
	cout << endl;
}

//Función que deriva el polinomio y lo almacena derivado en otro array
void derivarPolinomio(tPolinomio usuario, tPolinomio derivado)
{
	derivado[MAX - 1] = 0;
	for (int i = MAX - 1; i >= 1; i--)
	{
		derivado[i - 1] = usuario[i] * i;
	}
}

//Función que integra el polinomio y lo almacena en otro array
bool integrarPolinomio(tPolinomio usuario, tPolinomio integrado)
{
	bool integracion = true; //Booleano que comprueba que el usuario introduza un polinomio de grado 4
	integrado[0] = 0;

	if (usuario[MAX - 1] != 0)
	{
		integracion = false;
	}

	else
	{
		for (int i = 0; i < MAX; i++)
		{
			integrado[i + 1] = usuario[i] / (i + 1);
		}
	}

	return integracion;
}

//Función que evalua un polinomio en función del valor introducido por el usuario
float evaluar(tPolinomio usuario, float n)
{
	float resultado = 0;
	for (int i = 0; i < MAX; i++)
	{
		resultado = resultado + usuario[i] *pow(n, i);
	}
	return resultado;
}

//Función que lee un polinomio para calcular sus raices (sólo lee hasta grado 2)
void leerPolinomioGradoDos(tPolinomio usuario)
{
	cout << "Introduce un polinomio de grado 2." << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "Introduce el coeficiente del grado " << i << " del polinomio: ";
		cin >> usuario[i];
	}
	for (int i = 3; i < MAX; i++)
	{
		usuario[i] = 0;
	}
}
//Función que calcula las raices del polinomio de grado 2
void calcularRaices(tPolinomio usuario)
{
	float a = usuario[2], b = usuario[1], c = usuario[0];
	float sol1, sol2;
	float raiz = (pow(b, 2) - 4 * (a*c));
	if (raiz >= 0) //Comprueba si el contenido de la raiz es positivo para calcular la solución
	{
		sol1 = ((-b + sqrt(raiz)) / (2 * a));
		sol2 = ((-b - sqrt(raiz)) / (2 * a));

		if (sol1 == sol2)
		{
			cout << "La única solución del polinomio es x = " << sol1 << endl << endl;
		}

		else
		{
			cout << "Las soluciones del polinomio introducido son: x1 = " << sol1 << " y x2 = " << sol2 << endl << endl;
		}
	}

	else
	{
		cout << "El polinomio introducido tiene raices imaginarias. No es posible calcular la solucion. " << endl << endl;
	}
}
