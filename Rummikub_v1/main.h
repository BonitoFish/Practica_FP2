#pragma once
#include <tuple>

// Variables globales
const int MIN_NumJugadores = 2;
const int MAX_NumJugadores = 4;

const int MIN_NumFichas = 8;
const int MAX_NumFichas = 13;

const int MIN_IniFichas = 6;
const int MAX_IniFichas = 14;

const int MaxJugadas = MAX_NumFichas * 2;
const int MaxFichas = 50;

int menu();		// Gestiona las opciones que puede seleccionar cada usuario

std::tuple<int, int, int>parametros(); /* leer los par�metros con los que se va a incializar la partida, siendo el primer campo
	el n�mero de jugadores, el segundo campo el n�mero de fichas por columna que va tener la bolsa, y el �ltimo campo
	el n�mero de fichas iniciales que se van a repartir a cada jugador*/