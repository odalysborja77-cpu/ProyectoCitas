#include <stdio.h>
#include <string.h>
#include "pacientes.h"
#include "validaciones.h" // Asegúrate de tener este archivo, si no, comenta esta línea

#define ARCHIVO_PACIENTES "data/pacientes.txt"
#define ARCHIVO_USUARIOS_P "data/usuarios_pacientes.txt"

// --- FUNCION AUXILIAR: Verificar si existe ---
int existePaciente(char cedula[]) {
	FILE *f = fopen(ARCHIVO_PACIENTES, "r");
	Paciente p;
	
	if (!f) return 0; // Si no existe el archivo, no existe el paciente
	
	// Lee línea por línea buscando la cédula
	while (fscanf(f, "%s %[^;]; %d %s %s", p.cedula, p.nombre, &p.edad, p.telefono, p.correo) != EOF) {
		if (strcmp(p.cedula, cedula) == 0) {
			fclose(f);
			return 1; // Encontrado
		}
	}
	
	fclose(f);
	return 0; // No encontrado
}

// --- FUNCION PRINCIPAL: Registrar ---
void registrarPaciente() {
	Paciente p;
	char usuario[20], clave[20];
	
	FILE *f = fopen(ARCHIVO_PACIENTES, "a");
	FILE *fu = fopen(ARCHIVO_USUARIOS_P, "a");
	
	if (!f || !fu) {
		printf("Error: No se pudo abrir la carpeta 'data'. Verifica que exista.\n");
		return;
	}
	
	printf("\n--- REGISTRO DE NUEVO PACIENTE ---\n");
	printf("Cedula: ");
	scanf("%s", p.cedula);
	
	// Validaciones (si tienes validaciones.h, usa esNumero, si no, comenta este if)
	/* if (!esNumero(p.cedula)) {
	printf("ERROR: La cedula debe contener solo numeros.\n");
	fclose(f); fclose(fu); return;
	}
	*/
	
	if (existePaciente(p.cedula)) {
		printf("ERROR: Ya existe un paciente con esa cedula.\n");
		fclose(f); fclose(fu); return;
	}
	
	// Pedir resto de datos personales
	printf("Nombre: ");
	scanf(" %[^\n]", p.nombre); 
	
	printf("Edad: ");
	scanf("%d", &p.edad);
	
	printf("Telefono (SIN ESPACIOS): ");
	scanf("%s", p.telefono);
	
	printf("Correo (SIN ESPACIOS): ");
	scanf("%s", p.correo);
	
	// --- CREACION DE USUARIO (Con limpieza de buffer) ---
	printf("\n--- CREACION DE USUARIO PARA LOGIN ---\n");
	
	fflush(stdin); // Limpia el teclado para evitar saltos
	
	printf("Ingrese un Usuario: ");
	scanf("%s", usuario);
	
	printf("Ingrese una Contrasena: ");
	scanf("%s", clave);
	
	// Guardar en ambos archivos
	fprintf(f, "%s %s; %d %s %s\n", p.cedula, p.nombre, p.edad, p.telefono, p.correo);
	fprintf(fu, "%s %s %s\n", p.cedula, usuario, clave);
	
	fclose(f);
	fclose(fu);
	
	printf("\n[OK] REGISTRO COMPLETADO. Ahora puede iniciar sesion.\n");
}

// --- FUNCION LISTAR ---
void listarPacientes() {
	FILE *f = fopen(ARCHIVO_PACIENTES, "r");
	Paciente p;
	
	if (!f) {
		printf("No hay pacientes registrados.\n");
		return;
	}
	
	printf("\n--- LISTA DE PACIENTES ---\n");
	while (fscanf(f, "%s %[^;]; %d %s %s", p.cedula, p.nombre, &p.edad, p.telefono, p.correo) != EOF) {
		printf("Cedula: %s | Nombre: %s | Edad: %d\n", p.cedula, p.nombre, p.edad);
	}
	
	fclose(f);
}

// --- FUNCION ELIMINAR (ADMIN) ---
void eliminarPacienteAdmin() {
	char cedula[15];
	int encontrado = 0;
	
	printf("\n--- ELIMINAR PACIENTE ---\n");
	printf("Ingrese la Cedula del paciente a eliminar: ");
	scanf("%s", cedula);
	
	// 1. ELIMINAR DE DATOS PERSONALES (pacientes.txt)
	FILE *f = fopen(ARCHIVO_PACIENTES, "r");
	FILE *temp = fopen("data/temp_pacientes.txt", "w");
	Paciente p;
	
	if (!f || !temp) {
		printf("Error al abrir archivos. Verifica la carpeta 'data'.\n");
		return;
	}
	
	while (fscanf(f, "%s %[^;]; %d %s %s", p.cedula, p.nombre, &p.edad, p.telefono, p.correo) != EOF) {
		if (strcmp(p.cedula, cedula) == 0) {
			encontrado = 1;
			// No lo escribimos en el temporal (así se borra)
		} else {
			fprintf(temp, "%s %s; %d %s %s\n", p.cedula, p.nombre, p.edad, p.telefono, p.correo);
		}
	}
	fclose(f);
	fclose(temp);
	
	// Solo si encontramos al paciente hacemos el reemplazo
	if (encontrado) {
		remove(ARCHIVO_PACIENTES);
		rename("data/temp_pacientes.txt", ARCHIVO_PACIENTES);
	} else {
		remove("data/temp_pacientes.txt"); // Borramos el temporal si no sirvió
	}
	
	// 2. ELIMINAR DE USUARIOS (usuarios_pacientes.txt)
	// Esto es para que ya no pueda iniciar sesión
	FILE *fu = fopen(ARCHIVO_USUARIOS_P, "r");
	FILE *tempU = fopen("data/temp_usuarios.txt", "w");
	char c[15], u[20], pass[20];
	
	if (fu && tempU) {
		while (fscanf(fu, "%s %s %s", c, u, pass) != EOF) {
			if (strcmp(c, cedula) != 0) { // Si NO es la cédula a borrar, lo guardamos
				fprintf(tempU, "%s %s %s\n", c, u, pass);
			}
		}
		fclose(fu);
		fclose(tempU);
		
		if (encontrado) {
			remove(ARCHIVO_USUARIOS_P);
			rename("data/temp_usuarios.txt", ARCHIVO_USUARIOS_P);
		} else {
			remove("data/temp_usuarios.txt");
		}
	}
	
	if (encontrado) {
		printf("? Paciente y su usuario eliminados correctamente.\n");
	} else {
		printf("? No se encontro ningun paciente con esa cedula.\n");
	}
}
