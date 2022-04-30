#include "Bolsa.h"
#include <iostream>
#include <iomanip>
using namespace std;

void inicializarBolsa(tBolsa& bolsa) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < bolsa.num_fichas; j++) {
			bolsa.fichas[i][j] = new tFicha();
			bolsa.fichas[i][j]->valor = j + 1;

			switch (i) {
			case 0:
			case 4: bolsa.fichas[i][j]->color = rojo;
				break;
			case 1:
			case 5: bolsa.fichas[i][j]->color = verde;
				break;
			case 2:
			case 6: bolsa.fichas[i][j]->color = azul;
				break;
			default: bolsa.fichas[i][j]->color = amarillo;
			}
		}
	}
	bolsa.total_ficha = 8 * bolsa.num_fichas;
}

void delBolsa(tBolsa& bolsa) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < bolsa.num_fichas; j++) {
			if (bolsa.fichas[i][j] != nullptr) {
				delete bolsa.fichas[i][j];
				bolsa.fichas[i][j] = nullptr;
			}
		}
	}
	bolsa.total_ficha = 0;
}

bool robarFicha(tBolsa& bolsa, tSoporte& soporte) {
	bool ret = false;
	tFicha ficha = robar(bolsa);

	if (ficha.valor != -1 && soporte.num_fichas < MaxFichas) {
		nuevaFicha(soporte, ficha); // Función que añade nueva ficha al soporte y se redimensiona
		ret = true;
	}
	return ret;
}

tFicha robar(tBolsa& bolsa) {
	tFicha ret = { -1, libre };
	int fila_rand = std::rand() % 8 + 0; // Rango 0 - 7 incluidos
	int col_rand = std::rand() % bolsa.num_fichas + 0; // Rando 0 - bolsa.num_fichas-1 incluidos

	if (bolsa.fichas[fila_rand][col_rand] != nullptr) {	// Devuelve la ficha si la encuentra en una posición random
		ret.valor = bolsa.fichas[fila_rand][col_rand]->valor;
		ret.color = bolsa.fichas[fila_rand][col_rand]->color;
		delete bolsa.fichas[fila_rand][col_rand]; // Eliminamos el puntero de la Bolsa
		bolsa.fichas[fila_rand][col_rand] = nullptr;
	}
	else {
		int i = (col_rand == bolsa.num_fichas - 1 && fila_rand != 7) ? fila_rand + 1 :
			(col_rand == bolsa.num_fichas - 1 && fila_rand == 7) ? 0 : fila_rand;
		int j = (col_rand + 1) % bolsa.num_fichas;

		// Implementación mediante búsqueda circular
		for (int k = 0; k < (8 * bolsa.num_fichas) - 1; k++) {
			if (bolsa.fichas[i][j] != nullptr) {
				ret.valor = bolsa.fichas[i][j]->valor;
				ret.color = bolsa.fichas[i][j]->color;
				delete bolsa.fichas[fila_rand][col_rand];
				bolsa.fichas[fila_rand][col_rand] = nullptr;
				--bolsa.total_ficha;
				return ret;
			}
			i = (j == bolsa.num_fichas - 1 && i != 7) ? i + 1 :
				(j == bolsa.num_fichas - 1 && i == 7) ? 0 : i;
			j = (j + 1) % bolsa.num_fichas;
		}
	}

	if (!(ret == tFicha{ -1, libre })) {
		--bolsa.total_ficha;
	}
	return ret;
}

void repartir(tBolsa& bolsa, tSoportes& soportes) {
	for (int i = 0; i < soportes.num_jug; i++) {
		for (int j = 0; j < soportes.ini_fichas; j++) {
			robarFicha(bolsa, soportes.soporte_jug[i]);
		}
	}
}

void mostrar(tBolsa bolsa) {
	colorTexto(blanco);
	cout << "Bolsa:" << endl;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < bolsa.num_fichas; j++) {
			if (bolsa.fichas[i][j] != nullptr) {
				int color = bolsa.fichas[i][j]->color;
				colorTexto((tColor)color);
				cout << setw(2) << bolsa.fichas[i][j]->valor << "  ";
			}
			else {
				colorTexto(tColor::blanco);
				cout << setw(2) << "-1" << "  ";
			}		
		}
		cout << endl;
	}
}