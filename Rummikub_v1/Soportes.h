#pragma once
#include "main.h"
#include "Soporte.h"

// Estructura que mantiene los soportes de los jugadores
typedef struct {
	tSoporte soporte_jug[MAX_NumJugadores];
	int ini_fichas;	// N�mero de fichas que se hay que repartir a cada jugador (entre 6 y 14)
	int num_jug; // N�mero de jugadores 
}tSoportes;

int menor(const tSoportes soportes); // Devuelve el �ndice del soporte que acumula el menor n�mero de puntos

void delSoportes(tSoportes& soportes); // Libera la memoria dinamica de todos los soportes