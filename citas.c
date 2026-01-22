#include <stdio.h>
#include <string.h>
#include "citas.h"
#include "pacientes.h"
#include "medicos.h"
#include "validaciones.h"

#define ARCHIVO_CITAS "data/citas.txt"

// Función auxiliar para verificar duplicados
int citaDuplicada(char codigo[], char fecha[], char hora[]) {
	FILE *f = fopen(ARCHIVO_CITAS, "r");
	char c[15], m[10], fec[15], hor[10], st[15];
	if (!f) return 0;
	while (fscanf(f, "%s %s %s %s %s", c, m, fec, hor, st) != EOF) {
		if (strcmp(m, codigo) == 0 && strcmp(fec, fecha) == 0 && strcmp(hor, hora) == 0) {
			fclose(f);
			return 1;
		}
	}
	fclose(f);
	return 0;
}

void asignarCita() {
	char cedula[15], codigo[10], fecha[15], hora[10];
	FILE *f = fopen(ARCHIVO_CITAS, "a");
	
	if (!f) return;
	
	printf("Cedula Paciente: ");
	scanf("%s", cedula);
	if (!existePaciente(cedula)) {
		printf("Paciente no existe.\n");
		fclose(f); return;
	}
	
	printf("Codigo Medico: ");
	scanf("%s", codigo);
	if (!existeMedico(codigo)) {
		printf("Medico no existe.\n");
		fclose(f); return;
	}
	
	printf("Fecha (DD/MM/AAAA): ");
	scanf("%s", fecha);
	printf("Hora (HH:MM): ");
	scanf("%s", hora);
	
	if (!validarFecha(fecha) || !validarHora(hora)) {
		printf("Formato de fecha u hora incorrecto.\n");
		fclose(f); return;
	}
	
	if (citaDuplicada(codigo, fecha, hora)) {
		printf("El medico ya tiene cita en ese horario.\n");
		fclose(f); return;
	}
	
	// Guardamos con estado PENDIENTE
	fprintf(f, "%s %s %s %s PENDIENTE\n", cedula, codigo, fecha, hora);
	fclose(f);
	printf("Cita asignada correctamente.\n");
}

void listarCitas() {
	FILE *f = fopen(ARCHIVO_CITAS, "r");
	char c[15], m[10], fec[15], hor[10], st[15];
	if (!f) { printf("No hay citas.\n"); return; }
	
	printf("\n--- TODAS LAS CITAS ---\n");
	while (fscanf(f, "%s %s %s %s %s", c, m, fec, hor, st) != EOF) {
		printf("Pac: %s | Med: %s | %s %s | %s\n", c, m, fec, hor, st);
	}
	fclose(f);
}

void verCitasPaciente(char cedula[]) {
	FILE *f = fopen(ARCHIVO_CITAS, "r");
	char c[15], m[10], fec[15], hor[10], st[15];
	int cont = 0;
	if (!f) return;
	
	printf("\n--- MIS CITAS (Paciente) ---\n");
	while (fscanf(f, "%s %s %s %s %s", c, m, fec, hor, st) != EOF) {
		if (strcmp(c, cedula) == 0) {
			printf("Medico: %s | Fecha: %s %s | Estado: %s\n", m, fec, hor, st);
			cont++;
		}
	}
	if (cont == 0) printf("No tienes citas.\n");
	fclose(f);
}

void verCitasMedico(char codigo[]) {
	FILE *f = fopen(ARCHIVO_CITAS, "r");
	char c[15], m[10], fec[15], hor[10], st[15];
	int cont = 0;
	if (!f) return;
	
	printf("\n--- MIS CITAS (Medico) ---\n");
	while (fscanf(f, "%s %s %s %s %s", c, m, fec, hor, st) != EOF) {
		if (strcmp(m, codigo) == 0) {
			printf("Paciente: %s | Fecha: %s %s | Estado: %s\n", c, fec, hor, st);
			cont++;
		}
	}
	if (cont == 0) printf("No tienes citas programadas.\n");
	fclose(f);
}

void cancelarCita(char idUsuario[]) {
	// Esta funcion busca coincidencias por Paciente O por Medico
	FILE *f = fopen(ARCHIVO_CITAS, "r");
	FILE *temp = fopen("data/temp_citas.txt", "w");
	char c[15], m[10], fec[15], hor[10], st[15];
	char fDel[15], hDel[10];
	int encontrado = 0;
	
	if (!f || !temp) return;
	
	printf("Ingrese Fecha de la cita a cancelar: ");
	scanf("%s", fDel);
	printf("Ingrese Hora de la cita a cancelar: ");
	scanf("%s", hDel);
	
	while (fscanf(f, "%s %s %s %s %s", c, m, fec, hor, st) != EOF) {
		// Verifica si la cita corresponde al usuario (paciente o medico) y coincide fecha/hora
		if ((strcmp(c, idUsuario) == 0 || strcmp(m, idUsuario) == 0) &&
			strcmp(fec, fDel) == 0 && strcmp(hor, hDel) == 0) {
			encontrado = 1;
			// No la escribimos en el temporal (se borra)
		} else {
			fprintf(temp, "%s %s %s %s %s\n", c, m, fec, hor, st);
		}
	}
	
	fclose(f);
	fclose(temp);
	remove(ARCHIVO_CITAS);
	rename("data/temp_citas.txt", ARCHIVO_CITAS);
	
	if (encontrado) printf("Cita cancelada correctamente.\n");
	else printf("No se encontro una cita con esos datos.\n");
}

void registrarAsistencia(char codigo[]) {
	FILE *f = fopen(ARCHIVO_CITAS, "r");
	FILE *temp = fopen("data/temp_asistencia.txt", "w");
	char c[15], m[10], fec[15], hor[10], st[15];
	char fBus[15], hBus[10], nuevoSt[15];
	
	if (!f || !temp) return;
	
	printf("Fecha de la cita: ");
	scanf("%s", fBus);
	printf("Hora de la cita: ");
	scanf("%s", hBus);
	printf("Estado (ASISTIO / NO_ASISTIO): ");
	scanf("%s", nuevoSt);
	
	while (fscanf(f, "%s %s %s %s %s", c, m, fec, hor, st) != EOF) {
		if (strcmp(m, codigo) == 0 && strcmp(fec, fBus) == 0 && strcmp(hor, hBus) == 0) {
			fprintf(temp, "%s %s %s %s %s\n", c, m, fec, hor, nuevoSt);
		} else {
			fprintf(temp, "%s %s %s %s %s\n", c, m, fec, hor, st);
		}
	}
	
	fclose(f);
	fclose(temp);
	remove(ARCHIVO_CITAS);
	rename("data/temp_asistencia.txt", ARCHIVO_CITAS);
	printf("Estado actualizado.\n");
}
