#pragma once

#include <iostream>
#include <time.h>
#include <iomanip>
#include <tuple>

#include "tFicha.h"
#include "tJugada.h"
#include "tTablero.h"

typedef struct {
	lista_jugadaptr lista_jugada;
	int num_fichas_jugada;		// Número de fichas jugadas
}tJugada;

int buscar(const tJugada jugada, tFicha ficha);		// Devuelve la posición de la ficha en la jugada

void iniJugada(tJugada& jugada);		// Inicia las fichas de la jugada a -1

void nuevaJugada(tTablero& tablero, tJugada jugada);	// Añade al tablero la nueva jugada

bool puedePonerFicha(tJugada jugada, const tFicha& ficha); // Comprueba si se puede colocar la ficha en la Jugada

void mostrar(const tJugada jugada); // Muestra la Jugada

bool esSerie(tJugada jugada); // Identifica si la jugada es una serie

bool esEscalera(tJugada jugada); // Identifica si la jugada es una escalera