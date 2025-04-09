#include "archivo.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const* argv[])
{
	if (argc < 2) {
		printf("Error de invocación, debe incluir un archivo\n");
		return -1;
	}

	const char* nombre = argv[1];
	Archivo* archivo = archivo_abrir(nombre);

	if (!archivo) {
		printf("Error al abrir el archivo\n");
		return -1;
	}

	int i = 0;
	while (archivo_hay_mas_lineas(archivo)) {
		const char* linea = archivo_leer_linea(archivo);
		if (linea && *linea != '\0')
			printf("Línea %d: %s\n", i++, linea);
	}

	printf("Total de líneas leídas: %d\n", archivo_lineas_leidas(archivo));

	archivo_cerrar(archivo);
	return 0;
}
