#include <iostream>
#include "main.h"

using namespace std;

int main() {
	/*
	tSoporte lista;
	lista.lista_ficha[0] = { 7, azul };
	lista.lista_ficha[1] = { 3, azul };
	lista.lista_ficha[2] = { 9, amarillo };
	lista.lista_ficha[3] = { 6, azul };
	lista.lista_ficha[4] = { 5, azul };
	lista.lista_ficha[5] = { 6, verde };
	lista.lista_ficha[6] = { 9, rojo };
	lista.lista_ficha[7] = { 7, rojo };
	lista.lista_ficha[8] = { 1, verde };
	lista.lista_ficha[9] = { 2, verde };
	lista.lista_ficha[10] = { 6, amarillo };
	lista.lista_ficha[11] = { 6, rojo };
	lista.lista_ficha[12] = { 7, verde };
	lista.num_fichas = 13;
	*/

	tBolsa bolsa;
	bolsa.num_fichas = 13;
	inicializarBolsa(bolsa);
	mostrar(bolsa);

	tSoporte j1, j2;
	j1.num_fichas = 0;
	
	for (int i = 0; i < 20; i++) {
		j1.lista_ficha[i] = robar(bolsa);
		j1.num_fichas++;
	}

	mostrar(bolsa);
	mostrar(j1);

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
	tFicha tmp;
	for (int i = 0; i < soporte.num_fichas - 1; i++) {
		for (int j = soporte.num_fichas - 1; j > i; j--) {
			if (soporte.lista_ficha[j].color < soporte.lista_ficha[j - 1].color) {
				tmp = soporte.lista_ficha[j];
				soporte.lista_ficha[j] = soporte.lista_ficha[j - 1];
				soporte.lista_ficha[j - 1] = tmp;
			}
		}
	}
}


bool operator==(tFicha izq, tFicha der) {
	return (izq.color == der.color && izq.valor == der.valor);
}


int buscar(const tJugada jugada, tFicha ficha) {
	int ret = -1;
	int i = 0;

	while (i < jugada.num_fichas_jugada && ret == -1 ) {
		if (jugada.lista_jugada[i] == ficha) {
			ret = i;
		}
		++i;
	}
	return ret;
}


void mostrarSeries(tSoporte soporte) {
	int num[13];	// Lista números que ya se ha escogido para no repetir
	int tam_num = 0;

	// Recorrido de las fichas del soporte
	for (int i = 0; i < soporte.num_fichas; i++) {

		tFicha serie[4];	// La serie que voy a devolver al final si existe
		int tam_serie = 0;

		if (tam_num == 0) {	// Este es primer caso para un primer valor (solo se evalúa una vez)
			num[0] = soporte.lista_ficha[i].valor;
			tam_num++;	
		}
		else {
			bool duplicado = false;
			for (int j = 0; j < tam_num; j++) {	
				if (num[j] == soporte.lista_ficha[i].valor) {
					duplicado = true;
				}
			}

			if (duplicado) {	// Si se trata de un número ya recorrido anteriormente se pasa a la siguiente iteración
				continue;
			}
			else {	// De lo contrario guardamos ese valor para no repetir en las siguientes iteraciones
				num[tam_num] = soporte.lista_ficha[i].valor;
				tam_num++;
			}
		}

		serie[0] = soporte.lista_ficha[i];	// Suponemos que el primer elemento siempre será el del índice i
		tam_serie++;

		for (int j = i + 1; j < soporte.num_fichas; j++) {	// Recorro para buscar elementos de la serie a devolver

			if (soporte.lista_ficha[j].valor == serie[0].valor ) {
				bool mismo_color = false;
				for (int k = 0; k < tam_serie; k++) {
					if (serie[k].color == soporte.lista_ficha[j].color) {
						mismo_color = true;
					}
				}

				if (mismo_color) {	// Lo mismo que arriba, se comprueba si tiene el mismo color
					continue;
				}
				else {	// De lo contrario se introduce en la serie a devolver
					serie[tam_serie] = soporte.lista_ficha[j];
					tam_serie++;
				}
			}

		}

		// Devuelve la serie si supera el tamaño mínimo
		if (tam_serie >= 3) {
			for (int i = 0; i < tam_serie; i++) {
				colorTexto(serie[i].color);
				cout << serie[i].valor << " ";
			}
			colorTexto(blanco);
			cout << endl;
		}
	}
}


void mostrarEscaleras(tSoporte soporte) {

	for (int i = 0; i < soporte.num_fichas; i++) {	// Se itera sobre cada uno de los elementos del soporte

		tFicha escalera[13];	// La escalera a devolver si existe
		escalera[0] = soporte.lista_ficha[i];	// Se supone que en cada iteración el primer elem es el del índice i
		int tam_escalera = 1;

		tFicha elem = soporte.lista_ficha[i];	// Variable que utilizaremos como auxiliar

		int k = i;
		int j = (i + 1) % soporte.num_fichas;
		while (j != k) {	// Recorrido circular 
			if (soporte.lista_ficha[j].valor == elem.valor + 1 && soporte.lista_ficha[j].color == elem.color) {
				escalera[tam_escalera] = soporte.lista_ficha[j];
				tam_escalera++;
				elem = soporte.lista_ficha[j];	// Si existe elemento consecutivo empezar la búsqueda desde allí
				k = j;
			}
			j = (j + 1) % soporte.num_fichas;
		}

		// Igual que en mostrarSerie()
		if (tam_escalera >= 3) {
			for (int i = 0; i < tam_escalera; i++) {
				colorTexto(escalera[i].color);
				cout << escalera[i].valor << " ";
			}
			colorTexto(blanco);
			cout << endl;
		}
	}
}

// Hay que ver
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


void eliminaFichas(tSoporte& soporte, const tJugada jugada) {

	int i = 0;
	while (jugada.lista_jugada[i].valor != -1) {
		for (int j = 0; j < soporte.num_fichas; j++) {
			if (soporte.lista_ficha[j] == jugada.lista_jugada[i]) {

				for (int k = j; k < soporte.num_fichas-1; k++) {
					soporte.lista_ficha[k] = soporte.lista_ficha[k + 1];
				}
				soporte.lista_ficha[soporte.num_fichas] = { -1, libre };
				--soporte.num_fichas;
			}
		}
		++i;
	}
}


int nuevaJugada(tSoporte soporte, tJugada jugada) {

	mostrar(soporte);
	mostrarIndices(soporte.num_fichas);

	return 1;
}

bool ponerFicha(tJugada jugada, tFicha ficha) {

	return true;
}


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


void mostrar(tFicha ficha) {
	colorTexto(ficha.color);
	cout << "  " << ficha.valor << "  ";
}


void mostrar(tBolsa bolsa) {

	cout << "Bolsa:" << endl;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < bolsa.num_fichas; j++) {
			colorTexto(bolsa.fichas[i][j].color);
			cout << bolsa.fichas[i][j].valor << "  ";
		}
		cout << endl;
	}
}

void mostrar(const tJugada jugada) {
	for (int i = 0; i < jugada.num_fichas_jugada; i++) {
		colorTexto(jugada.lista_jugada[i].color);
		cout << "  " << jugada.lista_jugada[i].valor;
	}
}


void mostrar(tTablero tablero) {
	for (int i = 0; i < tablero.cont_jugadas; i++) {
		cout << i + 1 << ":";
		mostrar(tablero.lista_jugadas[i]);
		cout << endl;
	}
}


void mostrar(tSoporte soporte) {
	cout << "Soporte:";
	for (int i = 0; i < soporte.num_fichas; i++) {
		colorTexto(soporte.lista_ficha[i].color);
		cout << "  " << soporte.lista_ficha[i].valor;
	}
	cout << endl;
}


void mostrarIndices(int num) {
	colorTexto(blanco);
	cout << "          ";
	for (int i = 0; i < num; i++) {
		cout << "  " << i + 1;
	}
}


void colorTexto(tColor color) {
	switch (color) {
	case amarillo:
		cout << "\033[1;40;33m";
		break;
	case azul:
		cout << "\033[40;34m";
		break;
	case rojo:
		cout << "\033[40;31m";
		break;
	case verde:
		cout << "\033[40;32m";
		break;
	case blanco:
		cout << "\033[40;37m";
		break;
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



