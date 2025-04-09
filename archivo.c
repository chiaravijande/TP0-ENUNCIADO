#include "archivo.h"
#include <string.h>

#define BUFFER_INICIAL 10
#define FACTOR_AUMENTO 2

Archivo* archivo_abrir(const char* nombre)
{
	Archivo* archivo = malloc(sizeof(Archivo));
	if (!archivo)
		return NULL;

	archivo->fp = fopen(nombre, "r");
	if (!archivo->fp) {
		free(archivo);
		return NULL;
	}

	archivo->buffer = NULL;
	archivo->buffer_size = 0;
	archivo->lineas_leidas = 0;

	return archivo;
}

const char* archivo_leer_linea(Archivo* archivo)
{
	if (!archivo || !archivo->fp)
		return NULL;

	size_t capacidad = BUFFER_INICIAL;
	size_t longitud = 0;
	int c;

	char* nuevo_buffer = realloc(archivo->buffer, capacidad);
	if (!nuevo_buffer)
		return NULL;

	archivo->buffer = nuevo_buffer;
	archivo->buffer_size = capacidad;

	while ((c = fgetc(archivo->fp)) != EOF) {
		if (longitud + 1 >= archivo->buffer_size) {
			size_t nueva_capacidad =
			    archivo->buffer_size * FACTOR_AUMENTO;
			nuevo_buffer =
			    realloc(archivo->buffer, nueva_capacidad);
			if (!nuevo_buffer)
				return NULL;

			archivo->buffer = nuevo_buffer;
			archivo->buffer_size = nueva_capacidad;
		}

		archivo->buffer[longitud++] = (char)c;
		if (c == '\n')
			break;
	}

	if (longitud == 0)
		return NULL;

	archivo->buffer[longitud] = '\0';
	archivo->lineas_leidas++;
	return archivo->buffer;
}

bool archivo_hay_mas_lineas(Archivo* archivo)
{
	if (!archivo || !archivo->fp)
		return false;

	int c = fgetc(archivo->fp);
	if (c == EOF)
		return false;

	ungetc(c, archivo->fp);
	return true;
}

int archivo_lineas_leidas(Archivo* archivo)
{
	return archivo ? archivo->lineas_leidas : 0;
}

void archivo_cerrar(Archivo* archivo)
{
	if (!archivo)
		return;

	if (archivo->fp)
		fclose(archivo->fp);
	free(archivo->buffer);
	free(archivo);
}
