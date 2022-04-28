#pragma once
#include <iostream>
#include <time.h>
#include <iomanip>
#include <tuple>

#include "tBolsas.h"
#include "tColor.h"
#include "tFicha.h"
#include "tSoporte.h"
#include "tSoportes.h"
#include "tTablero.h"
#include "tJugada.h"

typedef enum { rojo, verde, azul, amarillo, blanco, libre }tColor;

void colorTexto(tColor color);