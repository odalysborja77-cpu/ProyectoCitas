#include <stdio.h>
#include <string.h>
#include "medicos.h"
#include "validaciones.h"

#define ARCHIVO_MEDICOS "data/medicos.txt"
#define ARCHIVO_USUARIOS_M "data/usuarios_medicos.txt"

int existeMedico(char codigo[]) {
	FILE *f = fopen(ARCHIVO_MEDICOS, "r");
	Medico m;
	if (!f) return 0;
	while (fscanf(f, "%s %[^;]; %s %s", m.codigo, m.nombre, m.especialidad, m.horario) != EOF) {
		if (strcmp(m.codigo, codigo) == 0) {
			fclose(f);
			return 1;
		}
	}
	fclose(f);
	return 0;
}

void registrarMedico() {
	Medico m;
	char usuario[20], clave[20];
	
	FILE *f = fopen(ARCHIVO_MEDICOS, "a");
	FILE *fu = fopen(ARCHIVO_USUARIOS_M, "a");
	
	if (!f || !fu) {
		printf("Error de archivos.\n");
		return;
	}
	
	printf("Codigo Medico: ");
	scanf("%s", m.codigo);
	
	if (existeMedico(m.codigo)) {
		printf("ERROR: Medico ya registrado.\n");
		fclose(f); fclose(fu); return;
	}
	
	printf("Nombre: ");
	scanf(" %[^\n]", m.nombre);
	printf("Especialidad: ");
	scanf("%s", m.especialidad);
	printf("Horario: ");
	scanf("%s", m.horario);
	
	printf("--- Creacion de Usuario Medico ---\n");
	printf("Usuario: ");
	scanf("%s", usuario);
	printf("Contrasena: ");
	scanf("%s", clave);
	
	fprintf(f, "%s %s; %s %s\n", m.codigo, m.nombre, m.especialidad, m.horario);
	fprintf(fu, "%s %s %s\n", m.codigo, usuario, clave);
	
	fclose(f);
	fclose(fu);
	printf("Medico registrado exitosamente.\n");
}

void listarMedicos() {
	FILE *f = fopen(ARCHIVO_MEDICOS, "r");
	Medico m;
	if (!f) {
		printf("No hay medicos.\n");
		return;
	}
	printf("\n--- LISTA DE MEDICOS ---\n");
	while (fscanf(f, "%s %[^;]; %s %s", m.codigo, m.nombre, m.especialidad, m.horario) != EOF) {
		printf("Codigo: %s | Nombre: %s | Esp: %s\n", m.codigo, m.nombre, m.especialidad);
	}
	fclose(f);
}
