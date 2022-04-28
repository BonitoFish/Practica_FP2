#pragma once
#include <iostream>
#include <time.h>
#include <iomanip>
#include <tuple>

#include "tBolsas.h"
#include "tColor.h"
#include "tFicha.h"
#include "tSoporte.h"
#include "tSoportes.h"
#include "tTablero.h"
#include "tJugada.h"

typedef struct {
	tSoporte soporte_jug[MAX_NumJugadores];
	int ini_fichas;	// Número de fichas que se hay que repartir a cada jugador (entre 6 y 14)
	int num_jug; // Número de jugadores 
}tSoportes;