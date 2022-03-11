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

// Cada ficha tiene un número y color
typedef struct {
	int valor;
	tColor color;
}tFicha;

// El soporte representa las fichas que tiene un jugador
typedef struct {
	tFicha lista_ficha[MAX_IniFichas*2];
	int num_fichas;
}tSoporte;

tSoporte tSoportes[MAX_NumJugadores];

// La bolsa contiene las fichas a repartir y de donde se tiene que robar 
typedef struct {
	tFicha fichas[8][MAX_NumFichas];
	int num_fichas;
	int fichas_disponibles;
}tBolsa;

typedef tFicha tJugada[MAX_NumFichas + 1];

// El tablero es donde contiene las jugadas 
typedef struct {
	tJugada lista_jugadas[MaxJugadas];
	int cont_jugadas;
}tTablero;


// Funciones 
int menu();	// Gestiona las opciones que puede seleccionar cada usuario

void inicializarBolsa(tBolsa& bolsa);	// Inicializa la bolsa con las fichas	

tFicha robar(tBolsa& bolsa);	// Devuelve una ficha obtenida de la bolsa


void parametros(int& numero_jugador, int& numero_fichas);
