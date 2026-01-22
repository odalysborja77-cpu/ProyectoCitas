#include <string.h>
#include <ctype.h>
#include "validaciones.h"

int esNumero(char texto[]) {
	for (int i = 0; texto[i] != '\0'; i++) {
		if (!isdigit(texto[i])) return 0;
	}
	return 1;
}

int validarFecha(char fecha[]) {
	// Formato simple DD/MM/AAAA (longitud 10)
	if (strlen(fecha) != 10) return 0;
	if (fecha[2] != '/' || fecha[5] != '/') return 0;
	return 1;
}

int validarHora(char hora[]) {
	// Formato HH:MM (longitud 5)
	if (strlen(hora) != 5) return 0;
	if (hora[2] != ':') return 0;
	return 1;
}
