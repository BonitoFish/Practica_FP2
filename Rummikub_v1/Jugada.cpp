#include "Jugada.h"
#include <iostream>
#include <iomanip>
using namespace std;

int buscar(const tJugada jugada, tFicha ficha) {
	int ret = -1;
	int i = 0;

	while (i < jugada.num_fichas_jugada && ret == -1) {
		if (jugada.lista_jugada[i] == ficha) {
			ret = i;
		}
		++i;
	}
	return ret;
}


void iniJugada(tJugada& jugada) {
	
	jugada.lista_jugada = new tFicha[MAX_NumFichas + 1];
	jugada.num_fichas_jugada = 0;

	for (int i = 0; i < MAX_NumFichas + 1; i++) {
		jugada.lista_jugada[i].valor = -1;
		jugada.lista_jugada[i].color = libre;
	}
}

bool esSerie(tJugada jugada) {

	if (jugada.num_fichas_jugada < 3 || jugada.num_fichas_jugada > 4) {
		return false;
	}

	int i = 0;
	bool esSerie = true;
	while (i < jugada.num_fichas_jugada && esSerie) {
		int j = (i + 1) % jugada.num_fichas_jugada;
		while (j != i && esSerie) {
			if ((jugada.lista_jugada[i].valor != jugada.lista_jugada[j].valor)
				|| (jugada.lista_jugada[i].color == jugada.lista_jugada[j].color)) {
				esSerie = false;
			}
			j = (j + 1) % jugada.num_fichas_jugada;
		}
		i++;
	}

	/*
	while (jugada.lista_jugada[i].valor != -1 && esSerie) {
		int j = (i + 1) % jugada.num_fichas_jugada;
		while (j != i && esSerie) {
			if ((jugada.lista_jugada[i].valor != jugada.lista_jugada[j].valor)
				|| (jugada.lista_jugada[i].color == jugada.lista_jugada[j].color)) {
				esSerie = false;
			}
			j = (j + 1) % jugada.num_fichas_jugada;
		}
		i++;
	}
	*/
	return esSerie;
}

bool esEscalera(tJugada jugada) {

	if (jugada.num_fichas_jugada < 3 || jugada.num_fichas_jugada > 13) {
		return false;
	}

	bool esEscalera = true;
	for (int i = 0; i < jugada.num_fichas_jugada - 1; i++) {
		if ((jugada.lista_jugada[i + 1].valor != (jugada.lista_jugada[i].valor + 1))
			|| (jugada.lista_jugada[i + 1].color != jugada.lista_jugada[i].color)) {
			esEscalera = false;
		}
	}
	return esEscalera;
}

bool ponerFicha(tJugada& jugada, tFicha ficha) {

	tJugada aux;
	iniJugada(aux);
	aux.num_fichas_jugada = jugada.num_fichas_jugada;

	// Copia los valores de la jugada en la jugada auxiliar
	for (int i = 0; i < jugada.num_fichas_jugada; i++) {
		aux.lista_jugada[i] = jugada.lista_jugada[i];
	}

	bool fichaColocada = false;
	if (esSerie(jugada)) {	// Llamo a la función para comprobar si tras insertar la ficha sigue siendo una serie

		if (aux.num_fichas_jugada < MAX_NumFichas) {
			aux.lista_jugada[aux.num_fichas_jugada] = ficha;
			aux.num_fichas_jugada++;
			aux.lista_jugada[aux.num_fichas_jugada] = { -1, libre };

			if (esSerie(aux)) {
				delete[] jugada.lista_jugada;
				jugada = aux;
				fichaColocada = true;
			}
		}
		else {
			fichaColocada = false;
		}
		
	}
	else if (esEscalera(jugada)) {	// Lo mismo para la Escalera, pero se hay que comprobar el extremo a insertar

		if (aux.num_fichas_jugada < MAX_NumFichas) {
			if (aux.lista_jugada[0].valor > ficha.valor) {
				for (int i = aux.num_fichas_jugada; i > 0; i--) {
					aux.lista_jugada[i] = aux.lista_jugada[i - 1];
				}
				aux.lista_jugada[0] = ficha;
				aux.num_fichas_jugada++;
				aux.lista_jugada[aux.num_fichas_jugada] = { -1, libre };
			}
			else {
				aux.lista_jugada[aux.num_fichas_jugada] = ficha;
				aux.num_fichas_jugada++;
				aux.lista_jugada[aux.num_fichas_jugada] = { -1, libre };
			}

			if (esEscalera(aux)) {
				delete[] jugada.lista_jugada;
				jugada = aux;
				fichaColocada = true;
			}
		}
	}
	else if (jugada.num_fichas_jugada == 0) {
		jugada.lista_jugada[0] = ficha;
		jugada.num_fichas_jugada++;
		fichaColocada = true;
	}
	return fichaColocada;
}

bool puedePonerFicha(tJugada jugada, const tFicha& ficha) {
	bool fichaColocada = false;
	if (esSerie(jugada)) {	// Llamo a la función para comprobar si tras insertar la ficha sigue siendo una serie
		if (jugada.num_fichas_jugada < MAX_NumFichas) {
			jugada.lista_jugada[jugada.num_fichas_jugada] = ficha;
			jugada.num_fichas_jugada++;
			jugada.lista_jugada[jugada.num_fichas_jugada] = { -1, libre };

			if (esSerie(jugada)) {
				fichaColocada = true;
			}
		}
	}
	else if (esEscalera(jugada)) {	// Lo mismo para la Escalera, pero se hay que comprobar el extremo a insertar
		if (jugada.num_fichas_jugada < MAX_NumFichas) {
			if (jugada.lista_jugada[0].valor > ficha.valor) {
				for (int i = jugada.num_fichas_jugada; i > 0; i--) {
					jugada.lista_jugada[i] = jugada.lista_jugada[i - 1];
				}
				jugada.lista_jugada[0] = ficha;
				jugada.num_fichas_jugada++;
				jugada.lista_jugada[jugada.num_fichas_jugada] = { -1, libre };
			}
			else {
				jugada.lista_jugada[jugada.num_fichas_jugada] = ficha;
				jugada.num_fichas_jugada++;
				jugada.lista_jugada[jugada.num_fichas_jugada] = { -1, libre };
			}

			if (esEscalera(jugada)) {
				fichaColocada = true;
			}
		}
	}
	else if (jugada.num_fichas_jugada == 0) {
		fichaColocada = true;
	}
	return fichaColocada;
}

void mostrar(const tJugada jugada) {
	for (int i = 0; i < jugada.num_fichas_jugada; i++) {
		colorTexto(jugada.lista_jugada[i].color);
		cout << setw(3) << jugada.lista_jugada[i].valor;
	}
}