#include <iostream>
<<<<<<< HEAD
#include "main.h"

using namespace std;

int main() {

	std::srand(time(NULL));

	for (int i = 0; i < 100; i++) {
		cout << std::rand() % 8 + 0 << endl;
	}
	
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
	/* TODO, se hay que iniciar los valores de las fichas de la bolsa, pero no se si eso se hará
	con un fichero de entrada o de alguna otra manera*/
}

tFicha robar(tBolsa& bolsa) {
	tFicha ret = { -1, libre };
	std::srand(time(NULL));

	int fila_rand = std::rand() % 8 + 0; // Rango 0 - 7 incluidos
	int col_rand = std::rand() % bolsa.num_fichas + 0; // Rando 0 - bolsa.num_fichas-1 incluidos

	if (bolsa.fichas[fila_rand][col_rand].color != libre) {
		ret = { bolsa.fichas[fila_rand][col_rand].valor, bolsa.fichas[fila_rand][col_rand].color };
		bolsa.fichas[fila_rand][col_rand] = { -1, libre };
	}
	else {
		for (int i = fila_rand; i < 8; i++) {
			for (int j = col_rand; j < bolsa.num_fichas; j++) {
				if (bolsa.fichas[i][j].color != libre) {
					ret = { bolsa.fichas[i][j].valor, bolsa.fichas[i][j].color };
					bolsa.fichas[i][j] = { -1, libre };
					break;
				}
			}
		}

		if (ret.color == libre) {
			for (int i = 0; i < fila_rand; i++) {
				for (int j = 0 ; j < bolsa.num_fichas; j++) {
					if (bolsa.fichas[i][j].color != libre) {
						ret = { bolsa.fichas[i][j].valor, bolsa.fichas[i][j].color };
						bolsa.fichas[i][j] = { -1, libre };
						break;
					}
				}
			}
		}

		if (ret.color == libre) {
			for (int i = fila_rand;;) {
				for (int j = 0; j < col_rand; j++) {
					if (bolsa.fichas[fila_rand][col_rand].color != libre) {
						ret = { bolsa.fichas[i][j].valor, bolsa.fichas[i][j].color };
						bolsa.fichas[i][j] = { -1, libre };
						break;
					}
				}
			}
		}
	}

	return ret;
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
=======
using namespace std;


int main () {
cout << "prueba";


}
>>>>>>> 17b6d2eae08592080ecce8e07267c9a764c1892a
