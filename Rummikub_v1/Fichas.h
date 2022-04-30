#pragma once
#include "Colores.h"

// Cada ficha tiene un número y color
typedef struct {
	int valor;
	tColor color;
}tFicha;

bool operator==(tFicha izq, tFicha der);	// Devuelve true si dos fichas son iguales a color y valor

void mostrar(tFicha ficha); // Muestra la Ficha