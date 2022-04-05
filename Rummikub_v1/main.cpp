#include "main.h"
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
		soportes.soporte_jug[i].num_fichas = 0;
	}

	srand(time(NULL));

	// Reparte las fichas a cada jugador según los parámetros introducidos anteriormente
	repartir(bolsa, soportes);	
	
	// Bucle Principal
	bool win = false;
	int i = 0;
	while (i < soportes.num_jug && !win) {
		bool robar = true; // Booleano que determina cuando se roba una Ficha 
		int op = -1;
		cout << "Turno para el jugador " << i + 1 << " ..." << endl;
		mostrar(tablero);

		while (op != 0) {
			mostrar(soportes.soporte_jug[i]);
			colorTexto(blanco);
			op = menu();

			switch (op) {
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

		if (robar && bolsa.total_ficha != 0) {
			robarFicha(bolsa, soportes.soporte_jug[i]);
		}

		if (!tieneFichas(soportes.soporte_jug[i])) {
			cout << "Gana el Jugador " << i + 1 << endl;
			win = true;
		}
		else if (bolsa.total_ficha == 0) {
			if (!puedeColocarFicha(tablero, soportes)) {
				int ganador = menor(soportes);
				cout << "****Gana el Jugador " << ganador + 1 <<"!****"<< endl;
				win = true;
			}
		}
		i = (i + 1) % soportes.num_jug;
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
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < bolsa.num_fichas; j++) {
			bolsa.fichas[i][j].valor = j + 1;

			switch (i) {
			case 0:
			case 4: bolsa.fichas[i][j].color = rojo;
				break;
			case 1:
			case 5: bolsa.fichas[i][j].color = verde;
				break;
			case 2:
			case 6: bolsa.fichas[i][j].color = azul;
				break;
			default: bolsa.fichas[i][j].color = amarillo;
			}
		}
	}
	bolsa.total_ficha = 8 * bolsa.num_fichas; 
}

bool robarFicha(tBolsa& bolsa, tSoporte& soporte) {	
	bool ret = false;
	tFicha ficha = robar(bolsa);

	if (ficha.valor != -1 && soporte.num_fichas < MaxFichas) {
		soporte.lista_ficha[soporte.num_fichas] = ficha;
		soporte.num_fichas++;
		ret = true;
	}
	return ret;
}

tFicha robar(tBolsa& bolsa) {
	tFicha ret = { -1, libre };
	int fila_rand = std::rand() % 8 + 0; // Rango 0 - 7 incluidos
	int col_rand = std::rand() % bolsa.num_fichas + 0; // Rando 0 - bolsa.num_fichas-1 incluidos

	if (bolsa.fichas[fila_rand][col_rand].valor != -1) {	// Devuelve la ficha si la encuentra en una posición random
		ret = bolsa.fichas[fila_rand][col_rand];
		bolsa.fichas[fila_rand][col_rand] = { -1, libre };
	}
	else {
		int i = (col_rand == bolsa.num_fichas - 1 && fila_rand != 7) ? fila_rand + 1 :
			(col_rand == bolsa.num_fichas - 1 && fila_rand == 7) ? 0 : fila_rand;
		int j = (col_rand + 1) % bolsa.num_fichas;
		
		// Implementación mediante búsqueda circular
		for (int k = 0; k < (8 * bolsa.num_fichas)-1; k++) {
			if (bolsa.fichas[i][j].valor != -1) {	
				ret = bolsa.fichas[i][j];
				bolsa.fichas[i][j] = { -1, libre };
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
			tFicha ficha = robar(bolsa);
			if (!(ficha == tFicha{ -1, libre })) {
				soportes.soporte_jug[i].lista_ficha[j] = ficha;
				soportes.soporte_jug[i].num_fichas++;
			}
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

void iniJugada(tJugada& jugada) {
	for (int i = 0; i < MAX_NumFichas + 1; i++) {
		jugada.lista_jugada[i] = { -1, libre };
	}
	jugada.num_fichas_jugada = 0;
}

void nuevaJugada(tTablero& tablero, tJugada jugada) {
	if (tablero.cont_jugadas < tablero.max_jugadas) {
		tablero.lista_jugadas[tablero.cont_jugadas] = jugada;
		tablero.cont_jugadas++;
	}
	else {
		cout << "****Limite de jugadas posibles!****" << endl;
	}
}

void eliminaFichas(tSoporte& soporte,  const tJugada jugada) {

	// Soporte auxiliar donde meter las fichas tras eliminar las de la Jugada
	tSoporte aux;
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
	soporte = aux;
}

int nuevaJugada(tSoporte& soporte, tJugada jugada) {

	int ret = 0; // Si devuelve 0 la nueva jugada es correcta, de lo contrario no es correcta
	if (esSerie(jugada)) {
		eliminaFichas(soporte, jugada);
		colorTexto(blanco);
		cout << "  " << "- Serie correcta!\n";
	}
	else if(esEscalera(jugada)) {
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

bool esSerie(tJugada jugada) {

	if (jugada.num_fichas_jugada < 3 || jugada.num_fichas_jugada > 4) {
		return false;
	}

	int i = 0;
	bool esSerie = true;
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
	return esSerie;
}

bool esEscalera(tJugada jugada) {

	if (jugada.num_fichas_jugada < 3 || jugada.num_fichas_jugada > 13) {
		return false;
	}

	bool esEscalera = true;
	for (int i = 0; i < jugada.num_fichas_jugada-1; i++) {
		if ((jugada.lista_jugada[i + 1].valor != (jugada.lista_jugada[i].valor + 1))
			|| (jugada.lista_jugada[i + 1].color != jugada.lista_jugada[i].color)) {
			esEscalera = false;
		}
	}
	return esEscalera;
}

bool ponerFicha(tJugada& jugada, tFicha ficha) {

	tJugada aux = jugada;
	bool fichaColocada = false;
	if (esSerie(jugada)) {	// Llamo a la función para comprobar si tras insertar la ficha sigue siendo una serie
		aux.lista_jugada[aux.num_fichas_jugada] = ficha;
		aux.num_fichas_jugada++;
		aux.lista_jugada[aux.num_fichas_jugada] = { -1, libre };

		if (esSerie(aux)) {
			jugada = aux;
			fichaColocada = true;
		}
	}
	else if (esEscalera(jugada)) {	// Lo mismo para la Escalera, pero se hay que comprobar el extremo a insertar

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

		if (esEscalera(aux)){
			jugada = aux;
			fichaColocada = true;
		}	
	}
	else if(jugada.num_fichas_jugada == 0){
		jugada.lista_jugada[0] = ficha;
		jugada.num_fichas_jugada++;
		fichaColocada = true;
	}
	return fichaColocada;
}

bool puedePonerFicha(tJugada jugada, const tFicha& ficha) {
	bool fichaColocada = false;
	if (esSerie(jugada)) {	// Llamo a la función para comprobar si tras insertar la ficha sigue siendo una serie
		jugada.lista_jugada[jugada.num_fichas_jugada] = ficha;
		jugada.num_fichas_jugada++;
		jugada.lista_jugada[jugada.num_fichas_jugada] = { -1, libre };

		if (esSerie(jugada)) {
			fichaColocada = true;
		}
	}
	else if (esEscalera(jugada)) {	// Lo mismo para la Escalera, pero se hay que comprobar el extremo a insertar
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
	else if (jugada.num_fichas_jugada == 0) {
		fichaColocada = true;
	}
	return fichaColocada;
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
	else if(jugada.num_fichas_jugada == 1){

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

		bool ficha_colocada = ponerFicha(tablero.lista_jugadas[aux - 1], ficha);

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
					if (puedePonerFicha(tablero.lista_jugadas[j], soportes.soporte_jug[i].lista_ficha[k])) {
						ret = true;
					}
				}
			}
		}
	}
	return ret;
}

void mostrar(tFicha ficha) {
	colorTexto(ficha.color);
	cout << "  " << ficha.valor << "  ";
}

void mostrar(tBolsa bolsa) {
	colorTexto(blanco);
	cout << "Bolsa:" << endl;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < bolsa.num_fichas; j++) {		
			int color = (bolsa.fichas[i][j].color) != libre ? bolsa.fichas[i][j].color : blanco;
			colorTexto((tColor)color);
			cout << setw(2) << bolsa.fichas[i][j].valor << "  ";
		}
		cout << endl;
	}
}

void mostrar(const tJugada jugada) {
	for (int i = 0; i < jugada.num_fichas_jugada; i++) {
		colorTexto(jugada.lista_jugada[i].color);
		cout << setw(3) << jugada.lista_jugada[i].valor;
	}
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
		mostrar(tablero.lista_jugadas[i]);
		cout << endl;
	}
	cout << "\n\n";
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

void mostrarIndices(int num) {
	colorTexto(blanco);
	cout << "         ";
	for (int i = 0; i < num; i++) {
		cout << setw(4) << right << i + 1;
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

bool tieneFichas(const tSoporte& soporte) {
	return (soporte.num_fichas != 0);
}



