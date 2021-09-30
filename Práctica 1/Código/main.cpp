// Práctica realizada por Álvaro Lopez Olmos y Javier Gómez Moraleda (1ºF) 

//Bibliotecas.
#include <iostream>
#include <string>
#include <fstream>
#include<stdlib.h>
#include <time.h>

using namespace std;

//Constantes.
const int MAX_CARTAS = 40;
const int MAX_TIPO = 8;
typedef int tArrayMazo[MAX_CARTAS];
typedef int tArrayRestantes[MAX_TIPO];

//Prototipos de las funciones.
int menu();
void jugarPartidaModoA(int aleatorio);
void jugarPartidaModoB(int aleatorio);
void jugarPartidaModoC();
void jugarPartidaModoD(int numPartida);
int numeroAleatorio();
bool localizacionMazo(tArrayMazo mazo);
int robarCarta(tArrayMazo mazo, int &n, float &puntuacion);	
string ganador(float totalJugador, float totalMaquina);
bool finalizarPartida(float total);
void marcadorRobar(int carta, float puntos);
bool turnoHumano(int n, tArrayMazo baraja, int &pos, float &total, int auxModo, tArrayRestantes restantes, int &numCartas, tArrayMazo cartasRobadas);
bool turnoMaquina(int n, tArrayMazo baraja, int &pos, float &total, int auxModo, float totalHumano, tArrayRestantes restantes, int &numCartas, tArrayMazo cartasRobadas);
bool seguirRobandoHumano();
void inicializarRecuento(tArrayRestantes restantes);
void recuentoCartas(tArrayRestantes restantes, int carta);
float probabilidadRobarMaquina(tArrayRestantes restantes, float & total);
string ganadorAleatorio();
int generarCarta();
void mazoAleatorio(tArrayMazo mazo);
void marcadorRobarModoD(int carta, float puntos, tArrayMazo cartas, int cont);
void ficheroPartida(int num, string ganador, float puntHumano, int numCartasHumano, tArrayMazo cartasHumano, float puntMaquina, int numCartasMaquina, tArrayMazo cartasMaquina);

//Funcion Principal.
int main()
{
	srand(time(NULL));
	int opcion, aleatorio, numPartidas = 0;
	do {
		opcion = menu();
		aleatorio = numeroAleatorio(); //Genera un número aleatorio del 3 al 5.
		if (opcion == 1)
		{
			jugarPartidaModoA(aleatorio);
		}

		else if (opcion == 2)
		{
			jugarPartidaModoB(aleatorio);
		}

		else if (opcion == 3)
		{
			jugarPartidaModoC();
		}
		else if (opcion == 4)
		{
			numPartidas++;
			jugarPartidaModoD(numPartidas);
		}
		else
			cout << "Has salido. Hasta pronto!" << endl << endl;

	} while (opcion != 0); //Muestra el menú si la opción es distinta de 0.

	system("PAUSE");
	return 0;
}

//Función que muestra el menú y devuelve la opción.
int menu()
{
	int op;
	cout << "Las Siete y Media" << endl;
	cout << "1 - Jugar partida en modo A." << endl;
	cout << "2 - Jugar partida en modo B." << endl;
	cout << "3 - Jugar partida en modo C." << endl;
	cout << "4 - Jugar partida en modo D." << endl;
	cout << "0 - Salir." << endl << endl;
	cout << "Introduce una opcion: ";
	cin >> op;

	while (cin.fail() || (op < 0) || (op > 4)) 
	{
		cin.clear();
		cin.ignore();
		cout << "Opcion incorrecta." << endl;
		cout << "Introduce una opcion: ";
		cin >> op;
	}

	return op;
}

//Función que permite jugar en el modo A.
void jugarPartidaModoA(int aleatorio)
{
	tArrayMazo baraja, auxCartas;
	bool encontrado = localizacionMazo(baraja);
	tArrayRestantes recuento;

	if (encontrado) //Si se ha encontrado el fichero de texto, comienza la partida.
	{
		bool final;
		int posicion = 0, auxModo = 1, auxNumcartas;
		float totalHumano = 0, totalMaquina = 0;
		final = turnoHumano(aleatorio, baraja, posicion, totalHumano, auxModo, recuento, auxNumcartas, auxCartas);

		if (!final) //Si el humano no se ha pasado de 7.5, es el turno de la máquina.
		{
			final = turnoMaquina(aleatorio, baraja, posicion, totalMaquina, auxModo, totalHumano, recuento, auxNumcartas, auxCartas);
		}
		ganador(totalHumano, totalMaquina); //Determina el ganador de la partida en función de los puntos obtenidos.
	}
}

//Función que permite jugar en el modo B.
void jugarPartidaModoB(int aleatorio)
{
	tArrayMazo baraja, auxCartas;
	bool encontrado = localizacionMazo(baraja);
	tArrayRestantes recuento;

	if (encontrado) //Si se ha encontrado el fichero de texto, comienza la partida.
	{
		bool final;
		int posicion = 0, auxModo = 2, auxNumCartas;
		float totalHumano = 0, totalMaquina = 0;
		final = turnoHumano(aleatorio, baraja, posicion, totalHumano, auxModo, recuento, auxNumCartas, auxCartas);

		if (!final) //Si el humano no se ha pasado de 7.5, es el turno de la máquina.
		{
			final = turnoMaquina(aleatorio, baraja, posicion, totalMaquina, auxModo, totalHumano, recuento, auxNumCartas, auxCartas);
		}
		ganador(totalHumano, totalMaquina); //Determina el ganador de la partida en función de los puntos obtenidos.
	}
}

//Función que permite jugar en el modo C.
void jugarPartidaModoC()
{
	tArrayMazo baraja, auxCartas;
	bool encontrado = localizacionMazo(baraja);
	tArrayRestantes recuento;
	inicializarRecuento(recuento);

	if (encontrado) //Si se ha encontrado el fichero de texto, comienza la partida.
	{
		bool final;
		int posicion = 0, auxModo = 3, aleatorio = 40, auxNumcartas;
		float totalHumano = 0, totalMaquina = 0;
		final = turnoHumano(aleatorio, baraja, posicion, totalHumano, auxModo, recuento, auxNumcartas, auxCartas);

		if (!final) //Si el humano no se ha pasado de 7.5, es el turno de la máquina.
		{
			final = turnoMaquina(aleatorio, baraja, posicion, totalMaquina, auxModo, totalHumano, recuento, auxNumcartas, auxCartas);
		}

		if ((totalHumano == totalMaquina) && totalHumano <= 7.5)
		{
			ganadorAleatorio();
		}

		else
		{
			ganador(totalHumano, totalMaquina);
		}
	}
}

//Función que permite jugar en el modo D.
void jugarPartidaModoD(int numPartida)
{
	tArrayMazo baraja, cartasHumano, cartasMaquina;
	mazoAleatorio(baraja);
	tArrayRestantes recuento;
	inicializarRecuento(recuento);
	bool final;
	int posicion = 0, auxModo = 4, aleatorio = 40, numCartasHumano = 0, numCartasMaquina = 0;
	float totalHumano = 0, totalMaquina = 0;
	string ganadorPartida;
	final = turnoHumano(aleatorio, baraja, posicion, totalHumano, auxModo, recuento, numCartasHumano, cartasHumano);

	if (!final) //Si el humano no se ha pasado de 7.5, es el turno de la máquina.
	{
		final = turnoMaquina(aleatorio, baraja, posicion, totalMaquina, auxModo, totalHumano, recuento, numCartasMaquina, cartasMaquina);
	}

	if ((totalHumano == totalMaquina) && (totalHumano <= 7.5)) 
	{
		if (numCartasHumano == numCartasMaquina) //Si ambos tienen el mismo número de cartass, el ganador se determina aleatoriamente.
			ganadorAleatorio();

		else if (numCartasHumano < numCartasMaquina) //Si la máquina tiene mas cartas, gana el jugador humano.
		{
			cout << "\nGana el jugador humano al tener menos cartas." << endl << endl;
			ganadorPartida = "Humano";
		}

		else //Si el humano tiene mas cartas, gana la máquina.
		{
			cout << "\nGana la maquina al tener menos cartas." << endl << endl;
			ganadorPartida = "Maquina";
		}
	}
	else
	{
		ganadorPartida = ganador(totalHumano, totalMaquina);
	}

	ficheroPartida(numPartida, ganadorPartida, totalHumano, numCartasHumano, cartasHumano, totalMaquina, numCartasMaquina, cartasMaquina);
}

//Función que genera un número aleatorio entre 3 y 5.
int numeroAleatorio()
{
	int aleatorio;
	aleatorio = 3 + rand() % 3;
	return aleatorio;
}

//Función que extrae el mazo de un fichero de texto y lo almacena en un array del tipo tArrayMazo.
bool localizacionMazo(tArrayMazo mazo)
{
	bool localizado = false;
	string fichero;
	cout << "Introduce el nombre del fichero con el mazo: ";
	cin >> fichero; //Lee el nombre del fichero introducido por el usuario.
	ifstream archivo;
	archivo.open(fichero);
	if (archivo.is_open()) //Si ha encontrado el fichero, guarda el mazo leido del mismo en un array.
	{
		for (int i = 0; i < MAX_CARTAS; i++)
		{
			archivo >> mazo[i];
		}
		archivo.close(); //Cierra el fichero.
		localizado = true;
	}
	else
		cout << "Fichero no encontrado. Imposible jugar." << endl << endl;

	return localizado;
}

//Función que devuelve una carta del mazo del tipo tArrayMazo. También cuenta la puntuación y tiene un contador para recorrer el mazo.
int robarCarta(tArrayMazo mazo, int &n, float &puntuacion)
{
	int carta = mazo[n]; //guarda la carta de una posición n del array mazo.
	float puntos = 0; //Determina los puntos en función de la carta.
	n = n + 1;
	if (carta >= 10) //Si la carta es una figura, la puntuación es 0.5.
	{
		puntos = 0.5;
	}
	else
	{
		puntos = carta;
	}
	puntuacion = puntuacion + puntos;
	return carta;
}

//Función que recibe dos puntuaciones y determina el ganador mostrándolo por pantalla.
string ganador(float totalJugador, float totalMaquina)
{
	string quienGana;
	if (totalJugador == totalMaquina) //Si tienen los mismos puntos, es empate (Sólo modo A y B).
	{
		cout << "\nEmpate." << endl << endl;
		quienGana = "Empate";
	}

	else if (totalJugador < totalMaquina)
	{
		if (totalMaquina <= 7.5)
		{
			cout << "\nGana la maquina. " << endl << endl;
			quienGana = "Maquina";
		}
		else if (totalMaquina > 7.5)
		{
			cout << "\nGana el jugador humano. " << endl << endl;
			quienGana = "Humano";
		}
	}

	else
	{
		if (totalJugador <= 7.5)
		{
			cout << "\nGana el jugador humano." << endl << endl;
			quienGana = "Humano";
		}
		else if (totalJugador > 7.5)
		{
			cout << "\nGana la maquina. " << endl << endl;
			quienGana = "Maquina";
		}
	}
	return quienGana;
}

//Función que devuelve true si la puntuación recibida es superior a 7.5.
bool finalizarPartida(float total)
{
	bool final = false;
	if (total > 7.5)
	{
		final = true;
	}
	return final;
}

//Función que muestra la carta robada y la puntuación total.
void marcadorRobar(int carta, float puntos)
{
	cout << "Has robado un " << carta << endl;
	cout << "Puntuacion total: " << puntos << endl << endl;
}

//Funcion que muestra la carta que has robado, las que llevas robadas y la puntuación total. Sólo para el modo D.
void marcadorRobarModoD(int carta, float puntos, tArrayMazo cartas, int cont)
{
	cout << "Has robado un " << carta << endl;
	cout << "Cartas robadas: ";
	for (int i = 0; i < cont; i++)
	{
		cout << cartas[i] << " ";
	}
	cout << endl;
	cout << "Puntuacion total: " << puntos << endl << endl;
}

//Función del turno del humano en todos los modos de juego.
bool turnoHumano(int n, tArrayMazo baraja, int &pos, float &total, int auxModo, tArrayRestantes restantes, int &numCartas, tArrayMazo cartasRobadas)
{
	bool fin = false, robar = true;
	int contador = 0, carta;
	cout << "\nTurno del jugador humano." << endl;
	if ((auxModo == 1) || (auxModo == 2)) //Si es el modo A o B, muestra el límite de cartas que puede robar cada jugador.
	{
		cout << "Puedes robar hasta un maximo de " << n << " cartas." << endl << endl;
	}
	while ((contador < n) && (!fin) && (robar)) //Si contador es menor que el limite, no se ha pasado de puntos y sigue robando. 
	{
		carta = robarCarta(baraja, pos, total);
		recuentoCartas(restantes, carta);
		
		if (auxModo == 4) //Almacena las cartas que roba en un array (Sólo para el modo D).
		{
			cartasRobadas[contador] = carta;
			contador++;
			marcadorRobarModoD(carta, total, cartasRobadas, contador);
		}
		else
		{
			marcadorRobar(carta, total);
			contador++;
		}		
		numCartas = contador;
		fin = finalizarPartida(total); //Comprueba si la puntuación del humano es superior a 7.5.
		if ((auxModo == 2) || (auxModo == 3) || (auxModo == 4)) //Salvo en el modo A, preguntará al jugador si desea seguir robando cartas.
		{
			if ((!fin) && (contador < n) && (robar))
			{
				robar = seguirRobandoHumano();
			}
		}
	}
	return fin;
}

//Función del turno de la máquina en todos los modos de juego.
bool turnoMaquina(int n, tArrayMazo baraja, int &pos, float &total, int auxModo, float totalHumano, tArrayRestantes restantes, int &numCartas, tArrayMazo cartasRobadas)
{
	bool fin = false;
	int contador = 0, carta;
	float probabilidad;
	cout << "\nTurno de la maquina." << endl << endl;
	while ((contador < n) && (!fin))
	{
		carta = robarCarta(baraja, pos, total);
		recuentoCartas(restantes, carta);
		if (auxModo == 4) //Almacena las cartas que roba en un array (Sólo para el modo D).
		{
			cartasRobadas[contador] = carta;
			contador++;
			marcadorRobarModoD(carta, total, cartasRobadas, contador);
		}
		else
		{
			marcadorRobar(carta, total);
			contador++;
		}
		numCartas = contador;
		fin = finalizarPartida(total); //Comprueba si la puntuación del humano es superior a 7.5.
		if ((auxModo == 2) || (auxModo == 3) || (auxModo == 4)) //Salvo en el modo A, la máquina decide si sigue robando.
		{
			if ((total > totalHumano) || (total == 7.5)) //Si tiene mas puntos que el humano o a llegado a 7.5, se planta.
			{
				fin = true;
			}
			else if (((auxModo == 3) || (auxModo == 4)) && (total == totalHumano) && (total < 7.5)) //En el modo C y D, calculará la probabilidad de pasarse.
			{
				probabilidad = probabilidadRobarMaquina(restantes, total);
				if (probabilidad > 0.5) //Si la probabilidad de pasarse es superior a 0.5, dejará de robar.
				{
					fin = true;
				}
			}
		}
	}
	return fin;
}

//Función que devuele false cuando el humano decida parar de robar.
bool seguirRobandoHumano()
{
	bool robar = true;
	char robo;
	cout << "Deseas robar otra carta? (s/n): ";
	cin >> robo;
	while ((robo != 'n') && (robo != 's'))
	{
		cout << "Caracter incorrecto. Introduce si o no para continuar (s/n): ";
		cin >> robo;
	}
	if (robo == 'n')
	{
		robar = false;
	}
	return robar;
}

//Función que inicializa un array del tipo tArrayRestantes con todas las cartas del mazo.
void inicializarRecuento(tArrayRestantes restantes)
{
	restantes[0] = 12; //En la posición 0 del array se contarán el número de figuras.
	for (int i = 1; i < MAX_TIPO; i++) //En las demás posiciones, su número correspondiente.
	{
		restantes[i] = 4;
	}
}

//Función que recibe una carta y la resta del array del tipo tArrayRestantes para llevar el recuento de las cartas.
void recuentoCartas(tArrayRestantes restantes, int carta)
{
	if (carta == 1)
		restantes[1]--;
	else if (carta == 2)
		restantes[2]--;
	else if (carta == 3)
		restantes[3]--;
	else if (carta == 4)
		restantes[4]--;
	else if (carta == 5)
		restantes[5]--;
	else if (carta == 6)
		restantes[6]--;
	else if (carta == 7)
		restantes[7]--;
	else
		restantes[0]--;
}

//Función que calcula la probabilidad de la maquina de pasarse de la puntuación máxima en funcion de los puntos y de las cartas que quedan en el mazo.
float probabilidadRobarMaquina(tArrayRestantes restantes, float & total)
{
	float prob, suma = 0;
	int cartasRestantes = 0, resta;
	for (int i = 0; i < MAX_TIPO; i++) //Recorre el array restantes para saber el número de cartas que quedan en el mazo.
	{
		cartasRestantes = cartasRestantes + restantes[i];
	}

	resta = (7.5 - total); //Resta la puntuación que lleva a 7.5, lo cual nos dará un entero siempre.
	resta++; //Incrementamos en 1 la resta para saber cuando empezar a contar las cartas con las que se pasa.

	for (int i = resta; i < MAX_TIPO; i++) //Recorre de nuevo el array restantes pero a partir de la posición resta.
	{
		suma = suma + restantes[i];
	}

	prob = suma / cartasRestantes; //Divide las cantidad de cartas con las que se pasa entre las que quedan en el mazo.
	return prob;
}

//Función que, en caso de empate determina un ganador aleatorio.
string ganadorAleatorio()
{
	string quienGana;
	int aleatorio = rand() % 2; //Genera un número entre 1 y 0.
	cout << "\nEmpate. Ganador generado aleatoriamente." << endl;
	if (aleatorio == 0)
	{
		cout << "Gana el jugador humano." << endl << endl;
		quienGana = "Humano";
	}
		
	else
	{
		cout << "Gana la maquina." << endl << endl;
		quienGana = "Maquina";
	}
	return quienGana;
}

//Función que genera un numero aleatorio entre 1 y 12 excluyendo el 8 y el 9.
int generarCarta()
{
	int aleatorio;
	do {
		aleatorio = 1 + rand() % 12;
	} while ((aleatorio == 8) || (aleatorio == 9)); //Mientras que el número generado sea igual a 8 o a 9, se generará otro número.
	return aleatorio;
}

//Función que genera un mazo aleatorio del tipo tArrayMazo.
void mazoAleatorio(tArrayMazo mazo)
{
	int contadorCartas[10], cartaAleatoria, pos = 0, aux;

	for (int i = 0; i < 10; i++) //Creo un array de 10 posiciónes para llevar el recuento al generar el mazo aleatorio.
	{
		contadorCartas[i] = 4;
	}
	for (int i = 0; i < MAX_CARTAS; i++) //Bucle for que irá rellenando el array mazo con distintos números.
	{
		do {
			cartaAleatoria = generarCarta(); //Genero un número entre 1 y 12 (menos 8 y 9).
			if (cartaAleatoria <= 7) //Si la carta generada es menor o igual a 7.
			{
				aux = cartaAleatoria - 1; //Aux determina la posición del array en el que llevo la cuenta de las cartas que he generado. 
			}
			else
			{
				aux = cartaAleatoria - 3; //Las posiciones 7, 8 y 9 del array contadorCartas guardarán respectivamente el 10, 11, 12.
			}
		} while (contadorCartas[aux] == 0); //Si contadorCartas es igual a 0, significa que ya he guardado 4 cartas del valor cartaAleatoria.
		contadorCartas[aux]--; //Resto 1 al contador de cartas.
		mazo[i] = cartaAleatoria; //Almaceno la carta generada en el mazo.
	}
}

//Función que genera un fichero al acabar la partida en el modo D.
void ficheroPartida(int num, string ganador, float puntHumano, int numCartasHumano, tArrayMazo cartasHumano, float puntMaquina, int numCartasMaquina, tArrayMazo cartasMaquina)
{
	string nombreFichero;
	nombreFichero = "partida" + to_string(num) + ".txt"; //Guarda en una variable string el número de la partida jugada.
	ofstream archivo; //Crea un fichero.
	archivo.open(nombreFichero); //Lo llama partidaXXX.txt.
	archivo << "Numero de partida: " << num << endl;
	archivo << "Ganador: " << ganador << endl;
	archivo << "Humano. Puntuacion: " << puntHumano << endl;
	archivo << "Cartas: ";
	for (int i = 0; i < numCartasHumano; i++) //Recorre un array que contiene las cartas robadas por el humano.
	{
		archivo << cartasHumano[i] << " ";
	}
	archivo << endl;
	archivo << "Maquina. Puntuacion: " << puntMaquina << endl;
	archivo << "Cartas: ";
	for (int i = 0; i < numCartasMaquina; i++) //Recorre un array que contiene las cartas robadas por la máquina.
	{
		archivo << cartasMaquina[i] << " ";
	}
	archivo << endl;
	archivo.close(); //Cierra el archivo.
}