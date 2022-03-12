#include <iostream>
#include "main.h"

using namespace std;

int main() {
	
	return 0;
}

int menu() {
	int op;
	do {
		cout << "1: Ordenar por num, 2: Ordenar por color, 3: Sugerir, 4: Poner, 0: Fin >>> ";
		cin >> op;
	} while (op > 4 || op < 0);
	return op;
}

void inicializarBolsa(tBolsa& bolsa) {	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < bolsa.num_fichas; j++) {
			bolsa.fichas[i][j].valor = j + 1;
			bolsa.fichas[i][j].color = (i == 0 || i == 4) ? rojo : (i == 1 || i == 5) ? verde :
				(i == 2 || i == 6) ? azul : amarillo;
		}
	}
}

tFicha robar(tBolsa& bolsa) {
	tFicha ret = { -1, libre };
	std::srand(time(NULL));

	int fila_rand = std::rand() % 8 + 0; // Rango 0 - 7 incluidos
	int col_rand = std::rand() % bolsa.num_fichas + 0; // Rando 0 - bolsa.num_fichas-1 incluidos

	if (bolsa.fichas[fila_rand][col_rand].color != libre) {
		ret = { bolsa.fichas[fila_rand][col_rand].valor, bolsa.fichas[fila_rand][col_rand].color };
		bolsa.fichas[fila_rand][col_rand] = { -1, libre };
		return ret;
	}
	else {
		for (int i = fila_rand; i < 8; i++) {
			for (int j = col_rand; j < bolsa.num_fichas; j++) {
				if (bolsa.fichas[i][j].color != libre) {
					ret = { bolsa.fichas[i][j].valor, bolsa.fichas[i][j].color };
					bolsa.fichas[i][j] = { -1, libre };
					return ret;
				}
			}
		}

		for (int i = 0; i <= fila_rand; i++) {
			for (int j = 0; j < bolsa.num_fichas; j++) {
				if (bolsa.fichas[i][j].color != libre) {
					ret = { bolsa.fichas[i][j].valor, bolsa.fichas[i][j].color };
					bolsa.fichas[i][j] = { -1, libre };
					return ret;
				}
			}
		}
	}
	return ret;
}


void repartir(tBolsa& bolsa, tSoportes& soportes) {
	for (int i = 0; i < soportes.num_jug; i++) {
		for (int j = 0; j < bolsa.num_fichas; j++) {
			soportes.soporte_jug[i].lista_ficha[j] = robar(bolsa);
			soportes.soporte_jug[i].num_fichas++;
		}
	}
}


void ordenarPorNum(tSoporte& soporte) {
	tFicha tmp;
	for (int i = 0; i < soporte.num_fichas - 1; i++) {
		for (int j = soporte.num_fichas - 1; j > i; j--) {
			if (soporte.lista_ficha[j].valor < soporte.lista_ficha[j - 1].valor) {
				tmp = soporte.lista_ficha[j];
				soporte.lista_ficha[j] = soporte.lista_ficha[j - 1];
				soporte.lista_ficha[j - 1] = tmp;
			}
		}
	}
}

void ordenarPorColor(tSoporte& soporte) {



}


bool operator==(tFicha izq, tFicha der) {
	return (izq.color == der.color && izq.valor == der.valor);
}


int buscar(const tJugada jugada, tFicha ficha) {
	int ret = -1;
	int i = 0;

	while (i < jugada.num_fichas_jugadas && ret == -1 ) {
		if (jugada.lista_jugada[i] == ficha) {
			ret = i;
		}
		++i;
	}
	return ret;
}


void mostrarSeries(tSoporte soporte) {
	tFicha serie[4];


}

void mostrarEscaleras(tSoporte soporte) {


}


void iniJugada(tJugada &jugada) {
	for (int i = 0; i < jugada.num_fichas; i++) {
		jugada.lista_jugada[i] = { -1, libre };
	}
}

void nuevaJugada(tTablero& tablero, tJugada jugada) {
	if (tablero.cont_jugadas < tablero.num_fichas * 2) {
		tablero.lista_jugadas[tablero.cont_jugadas] = jugada;
		tablero.cont_jugadas++;
	}
	else {
		cout << "\t\t[Limite de jugadas posibles]" << endl;
	}
}















































void parametros(int& numero_j, int& numero_fichas) {
	char aux;
	cout << " introduce parametros: " << endl;

	do {
		cout << " introduce numeros de jugadores: ";
		cin >> aux;
		cout << endl;
		if (!isdigit(aux)) {
			cout << "valor no aceptado, introduce de nuevo:  ";
			cin.ignore();
		}
		else
		{
			numero_j = aux - '0';
			if (numero_j >= MIN_NumJugadores && numero_j <= MAX_NumJugadores) {
				cout << "numero de jugadores es: " << numero_j;
			}
			else
			{
				cout << "VALOR FUERA DEL RANGO INTRODUCE DE NUEVO" << endl;
				cout << "------------------------------------------" << endl;
				cin.ignore();
			}

		}
	} while (numero_j < MIN_NumJugadores || numero_j > MAX_NumJugadores);

	cout << endl;
}



