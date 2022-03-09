#include <iostream>

using namespace std;

// Parámetros globales
const int MIN_NumJugadores = 2;
const int MAX_NumJugadores = 4;

const int MIN_NumFichas = 8;
const int MAX_NumFichas = 13;

const int MIN_IniFichas = 6;
const int MAX_IniFichas = 14;

const int MIN_MaxFichas = 50;

typedef enum tColor { rojo, verde, azul, amarillo, blanco, libre } tColor;

typedef struct {
	int valor;
	tColor color;
}tFicha;

typedef struct {
	tFicha lista_ficha[MIN_MaxFichas];

}tSoporte;

tSoporte lista_soporte[MAX_NumJugadores];

typedef struct {
	tFicha bolsa[8][MAX_NumFichas];
	int fichas_disp;
}tBolsa;



void parametros(int& numero_jugador, int& numero_fichas);


int main() {
	int numero_j = 0;
	int numero_fichas = 0;

	parametros(numero_j, numero_fichas);


	return 0;
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
