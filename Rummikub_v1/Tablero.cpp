#include <iostream>
#include "Tablero.h"
using namespace std;


void nuevaJugada(tTablero& tablero, tJugada jugada) {
	if (tablero.cont_jugadas < tablero.max_jugadas) {
		tablero.lista_jugadas[tablero.cont_jugadas] = new tJugada(jugada);
		tablero.cont_jugadas++;
	}
	else {
		cout << "****Limite de jugadas posibles!****" << endl;
	}
}

bool jugar(tTablero& tablero, tSoporte& soporte) {

	tJugada jugada;
	bool ret = false;

	iniJugada(jugada);
	mostrar(soporte);
	mostrarIndices(soporte.num_fichas);
	cout << '\n';
	cout << "Fichas (0 al final): ";

	int pos;
	cin >> pos;
	while (pos != 0) {
		// Comprueba si la Ficha escogida se encuentra dentro del rango
		if (pos <= soporte.num_fichas && pos > 0) {
			jugada.lista_jugada[jugada.num_fichas_jugada] = soporte.lista_ficha[pos - 1];
			jugada.num_fichas_jugada++;
		}
		else {
			cout << "****Ninguna Ficha tiene el indice " << pos << "!****" << endl;
			cout << "Continue (0 al final): ";
		}
		cin >> pos;
	}

	// Si ha metido más de una Ficha en la Jugada
	if (jugada.num_fichas_jugada > 1) {
		cout << "Jugada:  ";
		mostrar(jugada);

		// si la jugada es válida (= 0), añadir la nueva Jugada en el Tablero
		int nueva_jugada = nuevaJugada(soporte, jugada);

		if (nueva_jugada == 0) {
			nuevaJugada(tablero, jugada);
			ret = true;
		}
	}
	// Si solo ha seleccionado una Ficha para la Jugada
	else if (jugada.num_fichas_jugada == 1) {

		int aux = -1;
		// Si no hay jugadas en el tablero no se hace nada
		if (tablero.cont_jugadas == 0) {
			cout << "****No hay Jugadas en el Tablero para introducir una Ficha!****" << endl;
			return ret;
		}

		// Bucle para seleccionar la Jugada donde introducir la nueva Ficha
		while (aux > tablero.cont_jugadas || aux <= 0) {
			cout << "Jugadas del tablero donde poner la ficha: ";
			cin >> aux;
		}

		cout << "Jugada:  ";
		tFicha ficha = jugada.lista_jugada[0];	// Ficha de la jugada que vamos a insertar
		mostrar(ficha);

		bool ficha_colocada = ponerFicha(*(tablero.lista_jugadas[aux - 1]), ficha);

		if (ficha_colocada) {
			eliminaFichas(soporte, jugada);
			colorTexto(blanco);
			cout << "  -> Colocada!" << endl;
			ret = true;
		}
		else {
			colorTexto(blanco);
			cout << "  -> No Colocada!" << endl;
			mostrar(tablero);
		}
	}
	return ret;
}


bool puedeColocarFicha(tTablero tablero, tSoportes soportes) {
	bool ret = false;

	for (int i = 0; i < soportes.num_jug; i++) {
		// Comprueba si existen Series o Escaleras dentro del soporte de cualquier Jugador
		if (existeSerie(soportes.soporte_jug[i]) || existeEscalera(soportes.soporte_jug[i])) {
			ret = true;
		}
		else {
			// Prueba con todas las fichas de un Jugador para colocar en todas las jugadas del Tablero
			for (int j = 0; j < tablero.cont_jugadas; j++) {
				for (int k = 0; k < soportes.soporte_jug[i].num_fichas; k++) {
					if (puedePonerFicha(*(tablero.lista_jugadas[j]), soportes.soporte_jug[i].lista_ficha[k])) {
						ret = true;
					}
				}
			}
		}
	}
	return ret;
}

void mostrar(tTablero tablero) {
	colorTexto(blanco);
	cout << "\n";
	if (tablero.cont_jugadas == 0) {
		cout << "Tablero: No hay jugadas\n\n";
		return;
	}
	else {
		cout << "Tablero: " << endl;
	}

	for (int i = 0; i < tablero.cont_jugadas; i++) {
		colorTexto(blanco);
		cout << i + 1 << ":";
		mostrar(*(tablero.lista_jugadas[i]));
		cout << endl;
	}
	cout << "\n\n";
}

void delTablero(tTablero& tablero) {

	for (int i = 0; i < tablero.cont_jugadas; i++) {
		delete tablero.lista_jugadas[i];
		tablero.lista_jugadas[i] = nullptr;
	}
}