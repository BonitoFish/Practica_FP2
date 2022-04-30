#include "Soporte.h"
#include "Jugada.h"
#include <iostream>
#include <iomanip>
using namespace std;

void iniSoporte(tSoporte& soporte) {
	soporte.lista_ficha = new tFicha[8];
	soporte.capacidad_maxima_actual = 8;
	soporte.num_fichas = 0;
}

void nuevaFicha(tSoporte& soporte, tFicha ficha) {
	if (soporte.num_fichas == soporte.capacidad_maxima_actual) {
		soporte.capacidad_maxima_actual += 8;
		tFicha* aux = new tFicha[soporte.capacidad_maxima_actual]; // Definimos la nueva capacidad

		for (int i = 0; i < soporte.num_fichas; i++) {
			aux[i] = soporte.lista_ficha[i];
		}
		aux[soporte.num_fichas] = ficha;
		soporte.num_fichas++;
		delete[] soporte.lista_ficha;
		soporte.lista_ficha = nullptr;
		soporte.lista_ficha = aux;
	}
	else {
		soporte.lista_ficha[soporte.num_fichas] = ficha;
		soporte.num_fichas++;
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

			if (!duplicado) {	// Si el número no se ha repetido, entonces insertar en num para no repetir la próxima vez
				num[tam_num] = soporte.lista_ficha[i].valor;
				tam_num++;
			}
			else {	// Se pasa a la siguiente iteración si ya se había recorrido
				continue;
			}
		}

		serie[0] = soporte.lista_ficha[i];	// Suponemos que el primer elemento siempre será el del índice i
		tam_serie++;

		for (int j = i + 1; j < soporte.num_fichas; j++) {	// Recorro para buscar elementos de la serie a devolver

			if (soporte.lista_ficha[j].valor == serie[0].valor) {
				bool mismo_color = false;
				for (int k = 0; k < tam_serie; k++) {
					if (serie[k].color == soporte.lista_ficha[j].color) {
						mismo_color = true;
					}
				}

				if (!mismo_color) {	// Comprueba si el color es distinto, por tanto, insertar en la serie a devolver
					serie[tam_serie] = soporte.lista_ficha[j];
					tam_serie++;
				}
			}
		}
		// Imprime la serie si supera el tamaño mínimo
		if (tam_serie >= 3) {
			for (int i = 0; i < tam_serie; i++) {
				colorTexto(serie[i].color);
				cout << setw(4) << serie[i].valor;
			}
			colorTexto(blanco);
			cout << endl;
		}
	}
}

void mostrarEscaleras(tSoporte soporte) {
	int num[13];	// Lista números que ya se ha escogido para no repetir
	int tam_num = 0;

	for (int i = 0; i < soporte.num_fichas; i++) {	// Se itera sobre cada uno de los elementos del soporte

		if (tam_num == 0) {
			num[0] = soporte.lista_ficha[i].valor;
			tam_num++;
		}
		else {
			// Recorro mi lista de números para ver si se ha escogido previamente para formar una Escalera
			bool escogido_prev = false;
			for (int j = 0; j < tam_num; j++) {
				if (num[j] == soporte.lista_ficha[i].valor) {
					escogido_prev = true;
				}
			}

			if (!escogido_prev) {
				num[tam_num] = soporte.lista_ficha[i].valor;
				tam_num++;
			}
			else {
				continue;
			}
		}

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
				cout << setw(4) << escalera[i].valor;
			}
			colorTexto(blanco);
			cout << endl;
		}
	}
}

bool existeSerie(tSoporte soporte) {
	// Prácticamente idéntico que mostrarSeries()
	for (int i = 0; i < soporte.num_fichas; i++) {
		tFicha serie[4];
		serie[0] = soporte.lista_ficha[i];
		int cont_serie = 1; // Número de elementos de la serie a devolver
		for (int j = i + 1; j < soporte.num_fichas; j++) {	// Recorro para buscar elementos de la serie a devolver
			if (soporte.lista_ficha[j].valor == serie[0].valor) {
				bool mismo_color = false;
				for (int k = 0; k < cont_serie; k++) {
					if (serie[k].color == soporte.lista_ficha[j].color) {
						mismo_color = true;
					}
				}

				if (!mismo_color) {	// se comprueba si el color es distinto, por tanto, insertar en la serie a devolver
					serie[cont_serie] = soporte.lista_ficha[j];
					cont_serie++;
				}
			}
		}

		if (cont_serie >= 3) {
			return true;
		}
	}
	return false;
}

bool existeEscalera(tSoporte soporte) {
	// Prácticamente idéntico que mostrarEscaleras()
	for (int i = 0; i < soporte.num_fichas; i++) {
		tFicha escalera[13];
		escalera[0] = soporte.lista_ficha[i];
		int cont_escalera = 1;
		tFicha elem = soporte.lista_ficha[i];	// Variable que utilizaremos como auxiliar

		int k = i;
		int j = (i + 1) % soporte.num_fichas;
		while (j != k) {	// Recorrido circular 
			if (soporte.lista_ficha[j].valor == elem.valor + 1 && soporte.lista_ficha[j].color == elem.color) {
				escalera[cont_escalera] = soporte.lista_ficha[j];
				cont_escalera++;
				elem = soporte.lista_ficha[j];	// Si existe elemento consecutivo empezar la búsqueda desde allí
				k = j;
			}
			j = (j + 1) % soporte.num_fichas;
		}

		if (cont_escalera >= 3) {
			return true;
		}
	}
	return false;
}

bool tieneFichas(const tSoporte& soporte) {
	return (soporte.num_fichas != 0);
}

void mostrarIndices(int num) {
	colorTexto(blanco);
	cout << "         ";
	for (int i = 0; i < num; i++) {
		cout << setw(4) << right << i + 1;
	}
}

void mostrar(tSoporte soporte) {
	colorTexto(blanco);
	cout << "Soporte: ";
	for (int i = 0; i < soporte.num_fichas; i++) {
		colorTexto(soporte.lista_ficha[i].color);
		cout << setw(4) << right << soporte.lista_ficha[i].valor;
	}
	cout << endl;
}

void eliminaFichas(tSoporte& soporte, const tJugada jugada) {

	// Soporte auxiliar donde meter las fichas tras eliminar las de la Jugada
	tSoporte aux;
	aux.lista_ficha = new tFicha[soporte.capacidad_maxima_actual];
	aux.capacidad_maxima_actual = soporte.capacidad_maxima_actual;
	aux.num_fichas = 0;
	int j = 0;
	for (int i = 0; i < soporte.num_fichas; i++) {
		int k = j;
		bool insertar = true;
		while (k < jugada.num_fichas_jugada) {
			if (soporte.lista_ficha[i] == jugada.lista_jugada[j]) {
				insertar = false;
				j++;
			}
			k++;
		}

		if (insertar) {
			aux.lista_ficha[aux.num_fichas] = soporte.lista_ficha[i];
			aux.num_fichas++;
		}

	}

	delete[] soporte.lista_ficha;
	soporte.lista_ficha = nullptr;
	soporte = aux;

	// Disminuye la capacidad maxima del soporte si la diferencia es mayor de o igual que 8
	while (soporte.capacidad_maxima_actual - soporte.num_fichas >= 8) {
		soporte.capacidad_maxima_actual -= 4;
		tFicha* aux = new tFicha[soporte.capacidad_maxima_actual];

		for (int i = 0; i < soporte.num_fichas; i++) {
			aux[i] = soporte.lista_ficha[i];
		}
		delete[] soporte.lista_ficha;
		soporte.lista_ficha = aux;
		
	}
}

int nuevaJugada(tSoporte& soporte, tJugada jugada) {

	int ret = 0; // Si devuelve 0 la nueva jugada es correcta, de lo contrario no es correcta
	if (esSerie(jugada)) {
		eliminaFichas(soporte, jugada);
		colorTexto(blanco);
		cout << "  " << "- Serie correcta!\n";
	}
	else if (esEscalera(jugada)) {
		eliminaFichas(soporte, jugada);
		colorTexto(blanco);
		cout << "  " << "- Escalera correcta!\n";
	}
	else {
		colorTexto(blanco);
		cout << "  " << "- Serie o Escalera incorrecta!\n\n";
		ret = 1;
	}
	return ret;
}