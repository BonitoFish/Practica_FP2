#pragma once
#include "main.h"
#include "Jugada.h"
#include "Soporte.h"
#include "Soportes.h"

typedef tJugada* tJugadaptr;
typedef tJugadaptr tListaJugadas[MaxJugadas];

// El tablero es donde contiene las jugadas 
typedef struct {
	tListaJugadas lista_jugadas; // Array de punteros a tipo tJugada
	int max_jugadas;
	int cont_jugadas;
}tTablero;


void nuevaJugada(tTablero& tablero, tJugada jugada);	// Añade al tablero la nueva jugada

bool jugar(tTablero& tablero, tSoporte& soporte); // Permite al usuario colocar fichas en el tablero o hacer nuevas jugadas

void mostrar(tTablero tablero); // Muestra el Tablero

bool puedeColocarFicha(tTablero tablero, tSoportes soportes); // Comprueba si se puede colocar una ficha del soporte en el tablero

void delTablero(tTablero& tablero);