#pragma once
#include <iostream>
#include <time.h>
#include <iomanip>
#include <tuple>

#include "tSoporte.h"
#include "tTablero.h"

typedef struct {
	tJugada lista_jugadas[MaxJugadas];
	int max_jugadas;
	int cont_jugadas;
}tTablero;

bool jugar(tTablero& tablero, tSoporte& soporte); // Permite al usuario colocar fichas en el tablero o hacer nuevas jugadas


void mostrar(tTablero tablero); // Muestra el Tablero