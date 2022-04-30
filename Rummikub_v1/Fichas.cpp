#include "Fichas.h"
#include <iostream>
using namespace std;

bool operator==(tFicha izq, tFicha der) {
	return (izq.color == der.color && izq.valor == der.valor);


}

void mostrar(tFicha ficha) {
	colorTexto(ficha.color);
	cout << "  " << ficha.valor << "  ";
}