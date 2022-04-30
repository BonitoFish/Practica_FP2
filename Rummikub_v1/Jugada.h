#pragma once
#include "main.h"
#include "Fichas.h"

typedef struct {
	//tFicha lista_jugada[MAX_NumFichas + 1];
	tFicha* lista_jugada;		// Array dinámico de fichas
	int num_fichas_jugada;		// Número de fichas jugadas
}tJugada;

void iniJugada(tJugada& jugada);		// Inicia las fichas de la jugada a -1

bool ponerFicha(tJugada& jugada, tFicha ficha); // Intenta colocar la Ficha en la Jugada

bool puedePonerFicha(tJugada jugada, const tFicha& ficha); // Comprueba si se puede colocar la ficha en la Jugada

void mostrar(const tJugada jugada); // Muestra la Jugada

bool esSerie(tJugada jugada); // Identifica si la jugada es una serie

bool esEscalera(tJugada jugada); // Identifica si la jugada es una escalera

int buscar(const tJugada jugada, tFicha ficha);		// Devuelve la posición de la ficha en la jugada