#include <stdio.h>
#include <string.h>
#include "reportes.h"

#define ARCHIVO_CITAS "data/citas.txt"
#define ARCHIVO_REPORTE "reportes/resumen.txt"

void generarReporte() {
	FILE *fc = fopen(ARCHIVO_CITAS, "r");
	FILE *fr = fopen(ARCHIVO_REPORTE, "w");
	
	char c[15], m[10], f[15], h[10], st[15];
	char medicos[100][10];
	int conteo[100] = {0};
	int total = 0;
	
	if (!fc || !fr) {
		printf("Error creando reporte (verificar carpeta reportes).\n");
		return;
	}
	
	while (fscanf(fc, "%s %s %s %s %s", c, m, f, h, st) != EOF) {
		int existe = 0;
		for (int i = 0; i < total; i++) {
			if (strcmp(medicos[i], m) == 0) {
				conteo[i]++;
				existe = 1;
				break;
			}
		}
		if (!existe) {
			strcpy(medicos[total], m);
			conteo[total] = 1;
			total++;
		}
	}
	
	fprintf(fr, "=== REPORTE DE ACTIVIDAD ===\n\n");
	for (int i = 0; i < total; i++) {
		fprintf(fr, "Medico %s: %d citas atendidas/programadas.\n", medicos[i], conteo[i]);
	}
	
	fclose(fc);
	fclose(fr);
	printf("Reporte generado en: %s\n", ARCHIVO_REPORTE);
}
