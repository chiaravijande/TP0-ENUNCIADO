#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Archivo {
	FILE* fp;
	char* buffer;
	size_t buffer_size;
	int lineas_leidas;
} Archivo;

Archivo* archivo_abrir(const char* nombre);
const char* archivo_leer_linea(Archivo* archivo);
bool archivo_hay_mas_lineas(Archivo* archivo);
int archivo_lineas_leidas(Archivo* archivo);
void archivo_cerrar(Archivo* archivo);

#endif
