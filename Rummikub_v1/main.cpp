#include <iostream>
#include <time.h>
#include <iomanip>
#include "Colores.h"
#include "main.h"
#include "Fichas.h"
#include "Soporte.h"
#include "Soportes.h"
#include "Jugada.h"
#include "Bolsa.h"
#include "Tablero.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>
using namespace std;

/*
	Componentes del Grupo:
	- Daixiang Chen
	- Xu Zheng
*/

int main() {

	tBolsa bolsa;
	tTablero tablero;
	tSoportes soportes;

	// Se realiza la lectura de datos para la posterior inicialización de los parámetros de juego
	auto [num_jugadores, num_fichas, num_iniFichas] = parametros();

	// Inicialización de las estructuras de datos
	bolsa.num_fichas = num_fichas;
	inicializarBolsa(bolsa);

	tablero.max_jugadas = num_fichas * 2;
	tablero.cont_jugadas = 0;

	soportes.num_jug = num_jugadores;
	soportes.ini_fichas = num_iniFichas;

	// Inicializamos el soporte de cada uno de los jugadores
	for (int i = 0; i < soportes.num_jug; i++) {
		iniSoporte(soportes.soporte_jug[i]);
	}

	srand(time(NULL));

	// Reparte las fichas a cada jugador según los parámetros introducidos anteriormente
	repartir(bolsa, soportes);

	// Bucle Principal
	bool win = false;
	bool salir = false;
	int i = 0;
	while (i < soportes.num_jug && !win && !salir) {
		bool robar = true; // Booleano que determina cuando se roba una Ficha 
		int op = -1;
		cout << "Turno para el jugador " << i + 1 << " ..." << endl;
		mostrar(tablero);

		while (op != 5 && op != 0) {
			mostrar(soportes.soporte_jug[i]);
			colorTexto(blanco);
			op = menu();

			switch (op) {
			case 0: salir = true; cout << "Has salido del Juego!" << endl;
				break;
			case 1: ordenarPorNum(soportes.soporte_jug[i]);
				break;

			case 2: ordenarPorColor(soportes.soporte_jug[i]);
				break;

			case 3: mostrarSeries(soportes.soporte_jug[i]);
				mostrarEscaleras(soportes.soporte_jug[i]);
				break;

			case 4: if (jugar(tablero, soportes.soporte_jug[i])) mostrar(tablero); robar = false;
				break;
			}
		}

		if (robar && bolsa.total_ficha != 0 && !salir) {
			robarFicha(bolsa, soportes.soporte_jug[i]);
		}

		if (!tieneFichas(soportes.soporte_jug[i]) && !salir) {
			cout << "Gana el Jugador " << i + 1 << endl;
			win = true;
		}
		else if (bolsa.total_ficha == 0 && !salir) {
			if (!puedeColocarFicha(tablero, soportes)) {
				int ganador = menor(soportes);
				cout << "****Gana el Jugador " << ganador + 1 << "!****" << endl;
				win = true;
			}
		}
		i = (i + 1) % soportes.num_jug;
	}

	delBolsa(bolsa);
	delSoportes(soportes);
	delTablero(tablero);

	_CrtDumpMemoryLeaks();
	return 0;
}

int menu() {
	int op;
	do {
		cout << "1: Ordenar por num, 2: Ordenar por color, 3: Sugerir, 4: Poner, 5: Sig., 0: Fin >>> ";
		cin >> op;
	} while (op > 5 || op < 0);
	return op;
}

std::tuple<int, int, int>parametros() {

	int num_jugadores;
	int num_fichas;
	int num_fichas_ini;

	cout << "Introduce el Numero de Jugadores para comenzar la partida (2-4): ";
	cin >> num_jugadores;
	while (num_jugadores > 4 || num_jugadores < 2) {
		cout << "Introduce un numero entre 2 y 4 (inclusive): ";
		cin >> num_jugadores;
	}

	cout << "Introduce el Numero de Fichas con las que va a jugar durante la partida (8-13): ";
	cin >> num_fichas;
	while (num_fichas > 13 || num_fichas < 8) {
		cout << "Introduce un numero entre 8 y 13 (inclusive): ";
		cin >> num_fichas;
	}

	cout << "Introduce el Numero de Fichas que se van a repartir para cada jugador (6-14): ";
	cin >> num_fichas_ini;

	while (num_fichas > 14 || num_fichas < 6) {
		cout << "Introduce un numero entre 6 y 14 (inclusive): ";
		cin >> num_fichas_ini;
	}
	return { num_jugadores, num_fichas, num_fichas_ini };
}



//test

