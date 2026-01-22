#include <stdio.h>
#include <string.h>
#include "auth.h"

// Función interna para revisar credenciales en cualquier archivo
int loginGenerico(char archivo[], char id[]) {
	char fid[15], user[20], pass[20];
	char u[20], p[20];
	FILE *f = fopen(archivo, "r");
	
	if (!f) return 0; // Si no hay archivo, no hay login
	
	printf("Usuario: ");
	scanf("%s", u);
	printf("Contrasena: ");
	scanf("%s", p);
	
	while (fscanf(f, "%s %s %s", fid, user, pass) != EOF) {
		if (strcmp(user, u) == 0 && strcmp(pass, p) == 0) {
			if (id != NULL) strcpy(id, fid); // Guardamos la cédula/código
			fclose(f);
			return 1;
		}
	}
	fclose(f);
	return 0;
}

int loginPaciente(char id[]) {
	return loginGenerico("data/usuarios_pacientes.txt", id);
}

int loginMedico(char id[]) {
	return loginGenerico("data/usuarios_medicos.txt", id);
}

int loginAdmin() {
	return loginGenerico("data/usuarios_admin.txt", NULL);
}
