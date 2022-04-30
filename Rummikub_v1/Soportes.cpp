#include "Soportes.h"
#include <iostream>
using namespace std;

int menor(const tSoportes soportes) {

	int ret = -1;
	int menor = -1;
	for (int i = 0; i < soportes.num_jug; i++) {
		int acum = 0;	// Variable acumulador que suma todos los valores del soporte de un jugador
		for (int j = 0; j < soportes.soporte_jug[i].num_fichas; j++) {
			acum += soportes.soporte_jug[i].lista_ficha[j].valor;
		}

		if (menor == -1) {	// Solo entra una vez al if para establecer un valor inicial válido
			menor = acum;
			ret = i;
		}
		else if (acum < menor) {
			menor = acum;
			ret = i;
		}
	}

	if (ret == -1) {
		cout << "Error en funcion menor()";
	}
	return ret;
}

void delSoportes(tSoportes& soportes) {

	for (int i = 0; i < soportes.num_jug; i++) {
		delete [] soportes.soporte_jug[i].lista_ficha;
		soportes.soporte_jug[i].lista_ficha = nullptr;
		soportes.soporte_jug[i].num_fichas = 0;
	}

}

