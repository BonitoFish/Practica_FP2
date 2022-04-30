#pragma once
#include "main.h"
#include "Fichas.h"
#include "Jugada.h"

// El soporte representa las fichas que tiene un jugador
typedef struct {
	//tFicha lista_ficha[MaxFichas];
	tFicha* lista_ficha; // Array din�mico al tipo tFicha
	int capacidad_maxima_actual; // La capacidad maxima en cada momento 
	int num_fichas;		// N�mero de fichas del soporte
}tSoporte;

void iniSoporte(tSoporte& soporte);

void nuevaFicha(tSoporte& soporte, tFicha ficha);

void ordenarPorNum(tSoporte& soporte);		// Ordena las fichas del soporte por n�meros, de menor a mayor.

void ordenarPorColor(tSoporte& soporte);	// Ordena las fichas por colores y luego por cada calor ordenar por valor

void mostrarSeries(tSoporte soporte);	// Muestran las pos�bles series que se puedan crear con las fichas del soporte

void mostrarEscaleras(tSoporte soporte);	// Muestran las pos�bles escaleraas que se puedan crear con las fichas del soporte

bool existeSerie(tSoporte soporte);	// Devuelve true si al menos existe una Serie dentro del soporte

bool existeEscalera(tSoporte soporte);	// Devuelve true si al menos existe una Escalera dentro del soporte

bool tieneFichas(const tSoporte& soporte); // Comprueba si el soporte de un jugador contiene fichas

void mostrarIndices(int num);  // Muestra los �ndices debajo de un soporte para facilitar la selecci�n de fichas

void eliminaFichas(tSoporte& soporte, const tJugada jugada); // Elimina del soporte las fichas que hay en la jugada.

int nuevaJugada(tSoporte& soporte, tJugada jugada); // Permite al usuario crear una jugada con fichas que haya en su soporte.

void mostrar(tSoporte soporte); // Muestra las fichas que hay en el soporte