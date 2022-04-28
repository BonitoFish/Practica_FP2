#pragma once
#include <iostream>
#include <time.h>
#include <iomanip>
#include <tuple>

#include "tBolsas.h"
#include "tSoportes.h"
#include "tTablero.h"
#include "tColor.h"
// Variables globales


// Cada ficha tiene un número y color
 typedef struct {
	int valor;
	tColor color;
}tFicha; 


typedef tFicha* lista_jugadaptr[MAX_NumFichas + 1];
// Funciones 
int menu();		// Gestiona las opciones que puede seleccionar cada usuario


bool operator==(tFicha izq, tFicha der);	// Devuelve true si dos fichas son iguales a color y valor

int menor(const tSoportes soportes); // Devuelve el índice del soporte que acumula el menor número de puntos

tFicha robar(tBolsa& bolsa);	// Devuelve una ficha obtenida de la bolsa

void mostrarIndices(int num);  // Muestra los índices debajo de un soporte para facilitar la selección de fichas

bool puedeColocarFicha(tTablero tablero, tSoportes soportes); // Comprueba si se puede colocar una ficha del soporte en el tablero

std::tuple<int, int, int>parametros(); /* leer los parámetros con los que se va a incializar la partida, siendo el primer campo
	el número de jugadores, el segundo campo el número de fichas por columna que va tener la bolsa, y el último campo
	el número de fichas iniciales que se van a repartir a cada jugador*/

