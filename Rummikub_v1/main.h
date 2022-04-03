#pragma once
#include <iostream>
#include <time.h>
#include <iomanip>
#include <tuple>

// Variables globales
const int MIN_NumJugadores = 2;
const int MAX_NumJugadores = 4;

const int MIN_NumFichas = 8;
const int MAX_NumFichas = 13;

const int MIN_IniFichas = 6;
const int MAX_IniFichas = 14;

const int MaxJugadas = MAX_NumFichas * 2;
const int MaxFichas = 50;

typedef enum  { rojo, verde, azul, amarillo, blanco, libre }tColor;

// Cada ficha tiene un n�mero y color
typedef struct {
	int valor;
	tColor color;
}tFicha;

// El soporte representa las fichas que tiene un jugador
typedef struct {
	tFicha lista_ficha[MaxFichas];
	int num_fichas;		// N�mero de fichas del soporte
}tSoporte;

// Estructura que mantiene los soportes de los jugadores
typedef struct {
	tSoporte soporte_jug[MAX_NumJugadores];
	int ini_fichas;	// N�mero de fichas que se hay que repartir a cada jugador (entre 6 y 14)
	int num_jug; // N�mero de jugadores 
}tSoportes;

// La bolsa contiene las fichas a repartir y de donde se tiene que robar 
typedef struct {
	tFicha fichas[8][MAX_NumFichas];
	int num_fichas;	// Representa el tama�o de la columna del array bidimensional	
	int total_ficha; // El n�mero total de fichas de la bolsa
}tBolsa;

typedef struct {
	tFicha lista_jugada[MAX_NumFichas + 1];
	int num_fichas_jugada;		// N�mero de fichas jugadas
}tJugada;

// El tablero es donde contiene las jugadas 
typedef struct {
	tJugada lista_jugadas[MaxJugadas];
	int max_jugadas;
	int cont_jugadas;
}tTablero;


// Funciones 
int menu();		// Gestiona las opciones que puede seleccionar cada usuario

void inicializarBolsa(tBolsa& bolsa);	// Inicializa la bolsa con las fichas	

tFicha robar(tBolsa& bolsa);	// Devuelve una ficha obtenida de la bolsa

bool robarFicha(tBolsa& bolsa, tSoporte& soporte); // Roba una ficha para un jugador

void repartir(tBolsa& bolsa, tSoportes& soportes);	// Obtiene IniFichas para cada jugador

void ordenarPorNum(tSoporte& soporte);		// Ordena las fichas del soporte por n�meros, de menor a mayor.

void ordenarPorColor(tSoporte& soporte);	// Ordena las fichas por colores y luego por cada calor ordenar por valor

bool operator==(tFicha izq, tFicha der);	// Devuelve true si dos fichas son iguales a color y valor

int buscar(const tJugada jugada, tFicha ficha);		// Devuelve la posici�n de la ficha en la jugada

void mostrarSeries(tSoporte soporte);	// Muestran las pos�bles series que se puedan crear con las fichas del soporte

void mostrarEscaleras(tSoporte soporte);	// Muestran las pos�bles escaleraas que se puedan crear con las fichas del soporte

bool existeSerie(tSoporte soporte);	// Devuelve true si al menos existe una Serie dentro del soporte

bool existeEscalera(tSoporte soporte);	// Devuelve true si al menos existe una Escalera dentro del soporte

void iniJugada(tJugada &jugada);		// Inicia las fichas de la jugada a -1

void nuevaJugada(tTablero& tablero, tJugada jugada);	// A�ade al tablero la nueva jugada

void eliminaFichas(tSoporte& soporte, const tJugada jugada); // Elimina del soporte las fichas que hay en la jugada.

int nuevaJugada(tSoporte& soporte, tJugada jugada); // Permite al usuario crear una jugada con fichas que haya en su soporte.

bool ponerFicha(tJugada& jugada, tFicha ficha); // Intenta colocar la Ficha en la Jugada

bool puedePonerFicha(tJugada jugada, const tFicha& ficha); // Comprueba si se puede colocar la ficha en la Jugada

bool jugar(tTablero& tablero, tSoporte& soporte); // Permite al usuario colocar fichas en el tablero o hacer nuevas jugadas

int menor(const tSoportes soportes); // Devuelve el �ndice del soporte que acumula el menor n�mero de puntos

void mostrar(tFicha ficha); // Muestra la Ficha

void mostrar(tBolsa bolsa); // Muestra el contenido de la Bolsa

void mostrar(const tJugada jugada); // Muestra la Jugada

void mostrar(tTablero tablero); // Muestra el Tablero

void mostrar(tSoporte soporte); // Muestra las fichas que hay en el soporte

void mostrarIndices(int num);  // Muestra los �ndices debajo de un soporte para facilitar la selecci�n de fichas

bool esSerie(tJugada jugada); // Identifica si la jugada es una serie

bool esEscalera(tJugada jugada); // Identifica si la jugada es una escalera

bool tieneFichas(const tSoporte& soporte); // Comprueba si el soporte de un jugador contiene fichas

bool puedeColocarFicha(tTablero tablero, tSoportes soportes); // Comprueba si se puede colocar una ficha del soporte en el tablero

std::tuple<int, int, int>parametros(); /* leer los par�metros con los que se va a incializar la partida, siendo el primer campo 
	el n�mero de jugadores, el segundo campo el n�mero de fichas por columna que va tener la bolsa, y el �ltimo campo
	el n�mero de fichas iniciales que se van a repartir a cada jugador*/

void colorTexto(tColor color);
