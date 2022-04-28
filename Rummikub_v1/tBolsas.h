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

const int MIN_NumJugadores = 2;
const int MAX_NumJugadores = 4;

const int MIN_NumFichas = 8;
const int MAX_NumFichas = 13;

const int MIN_IniFichas = 6;
const int MAX_IniFichas = 14;

const int MaxJugadas = MAX_NumFichas * 2;
const int MaxFichas = 50;

typedef struct {
	tFicha fichas[8][MAX_NumFichas];
	int num_fichas;	// Representa el tamaño de la columna del array bidimensional	
	int total_ficha; // El número total de fichas de la bolsa
}tBolsa;

void inicializarBolsa(tBolsa& bolsa);	// Inicializa la bolsa con las fichas	

bool robarFicha(tBolsa& bolsa, tSoporte& soporte); // Roba una ficha para un jugador

void repartir(tBolsa& bolsa, tSoportes& soportes);	// Obtiene IniFichas para cada jugador

void mostrar(tBolsa bolsa); // Muestra el contenido de la Bolsa