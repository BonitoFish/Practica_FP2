#pragma once

// Variables globales
const int MIN_NumJugadores = 2;
const int MAX_NumJugadores = 4;

const int MIN_NumFichas = 8;
const int MAX_NumFichas = 13;

const int MIN_IniFichas = 6;
const int MAX_IniFichas = 14;

const int MaxJugadas = MAX_NumFichas * 2;
const int MaxFichas = 50;

typedef enum { rojo, verde, azul, amarillo, blanco, libre } tColor;

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
	int num_jug;
}tSoportes;

// La bolsa contiene las fichas a repartir y de donde se tiene que robar 
typedef struct {
	tFicha fichas[8][MAX_NumFichas];
	int num_fichas;	// Representa el tama�o de la columna del array bidimensional
	int fichas_disponibles;		
}tBolsa;

typedef struct {
	tFicha lista_jugada[MAX_NumFichas + 1];
	int num_fichas;		// N�mero m�ximo de fichas de la jugada
	int num_fichas_jugada;		// N�mero de fichas jugadas
}tJugada;

// El tablero es donde contiene las jugadas 
typedef struct {
	tJugada lista_jugadas[MaxJugadas];
	int num_fichas;
	int cont_jugadas;
}tTablero;


// Funciones 
int menu();		// Gestiona las opciones que puede seleccionar cada usuario

void inicializarBolsa(tBolsa& bolsa);	// Inicializa la bolsa con las fichas	

tFicha robar(tBolsa& bolsa);	// Devuelve una ficha obtenida de la bolsa

void repartir(tBolsa& bolsa, tSoportes soportes);	// Obtiene IniFichas para cada jugador

void ordenarPorNum(tSoporte& soporte);		// Ordena las fichas del soporte por n�meros, de menor a mayor.

void ordenarPorColor(tSoporte& soporte);	// Ordena las fichas por colores y luego por cada calor ordenar por valor

bool operator==(tFicha izq, tFicha der);	// Devuelve true si dos fichas son iguales a color y valor

int buscar(const tJugada jugada, tFicha ficha);		// Devuelve la posici�n de la ficha en la jugada

void mostrarSeries(tSoporte soporte);	// Muestran las pos�bles series que se puedan crear con las fichas del soporte

void mostrarEscaleras(tSoporte soporte);	// Muestran las pos�bles escaleraas que se puedan crear con las fichas del soporte

void iniJugada(tJugada &jugada);		// Inicia las fichas de la jugada a -1

void nuevaJugada(tTablero& tablero, tJugada jugada);	// A�ade al tablero la nueva jugada

void eliminaFichas(tSoporte& soporte, const tJugada jugada); // Elimina del soporte las fichas que hay en la jugada.

int nuevaJugada(tSoporte soporte, tJugada jugada); // Permite al usuario crear una jugada con fichas que haya en su soporte.

bool ponerFicha(tJugada jugada, tFicha ficha); // Intenta colocar la Ficha en la Jugada

int menor(const tSoportes soportes); // Devuelve el �ndice del soporte que acumula el menor n�mero de puntos

void mostrar(tFicha ficha); // Muestra la Ficha

void mostrar(tBolsa bolsa); // Muestra el contenido de la Bolsa

void mostrar(const tJugada jugada); // Muestra la Jugada

void mostrar(tTablero tablero); // Muestra el Tablero

void mostrar(tSoporte soporte); // Muestra las fichas que hay en el soporte

void mostrarIndices(int num);  // Muestra los �ndices debajo de un soporte para facilitar la selecci�n de fichas

void parametros(int& numero_jugador, int& numero_fichas);


void colorTexto(tColor color);
