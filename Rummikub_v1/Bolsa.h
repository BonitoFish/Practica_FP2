#pragma once
#include "Fichas.h"
#include "main.h"
#include "Soporte.h"
#include "Soportes.h"

typedef tFicha* tFichaptr; // tipo puntero a tFicha
typedef tFichaptr tArrayFichas[8][MAX_NumFichas]; // Array Bidimensional de punteros a tFicha

// La bolsa contiene las fichas a repartir y de donde se tiene que robar 
typedef struct {
	tArrayFichas fichas;
	int num_fichas;	// Representa el tamaño de la columna del array bidimensional	
	int total_ficha; // El número total de fichas de la bolsa
}tBolsa;

void inicializarBolsa(tBolsa& bolsa);	// Inicializa la bolsa con las fichas	

tFicha robar(tBolsa& bolsa);	// Devuelve una ficha obtenida de la bolsa

bool robarFicha(tBolsa& bolsa, tSoporte& soporte); // Roba una ficha para un jugador

void repartir(tBolsa& bolsa, tSoportes& soportes);	// Obtiene IniFichas para cada jugador

void delBolsa(tBolsa& bolsa);

void mostrar(tBolsa bolsa); // Muestra el contenido de la Bolsa