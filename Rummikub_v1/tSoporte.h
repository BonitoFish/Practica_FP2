#pragma once
#include <iostream>
#include <time.h>
#include <iomanip>
#include <tuple>

#include "tJugada.h"

typedef struct {
	tFicha lista_ficha[MaxFichas];
	int num_fichas;		// Número de fichas del soporte
}tSoporte;

void ordenarPorNum(tSoporte& soporte);		// Ordena las fichas del soporte por números, de menor a mayor.

void ordenarPorColor(tSoporte& soporte);	// Ordena las fichas por colores y luego por cada calor ordenar por valor

void mostrarSeries(tSoporte soporte);	// Muestran las posíbles series que se puedan crear con las fichas del soporte

void mostrarEscaleras(tSoporte soporte);	// Muestran las posíbles escaleraas que se puedan crear con las fichas del soporte

bool existeSerie(tSoporte soporte);	// Devuelve true si al menos existe una Serie dentro del soporte

bool existeEscalera(tSoporte soporte);	// Devuelve true si al menos existe una Escalera dentro del soporte

void eliminaFichas(tSoporte& soporte, const tJugada jugada); // Elimina doel soporte las fichas que hay en la jugada.

void mostrar(tSoporte soporte); // Muestra las fichas que hay en el soporte

bool tieneFichas(const tSoporte& soporte); // Comprueba si el soporte de un jugador contiene fichasl

