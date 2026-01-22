#include <stdio.h>
#include "pacientes.h"
#include "medicos.h"
#include "citas.h"
#include "auth.h"
#include "reportes.h"

// --- MENUS ---

void menuPaciente(char cedula[]) {
	int op;
	do {
		printf("\n=== MENU PACIENTE (%s) ===\n", cedula);
		printf("1. Agendar cita\n");
		printf("2. Ver mis citas\n");
		printf("3. Cancelar cita\n");
		printf("0. Salir\n");
		printf("Opcion: ");
		scanf("%d", &op);
		
		switch (op) {
		case 1: asignarCita(); break;
		case 2: verCitasPaciente(cedula); break;
		case 3: cancelarCita(cedula); break;
		}
	} while (op != 0);
}

void menuMedico(char codigo[]) {
	int op;
	do {
		printf("\n=== MENU MEDICO (%s) ===\n", codigo);
		printf("1. Ver mis citas\n");
		printf("2. Cancelar cita\n");
		printf("3. Registrar asistencia\n");
		printf("0. Salir\n");
		printf("Opcion: ");
		scanf("%d", &op);
		
		switch (op) {
		case 1: verCitasMedico(codigo); break;
		case 2: cancelarCita(codigo); break;
		case 3: registrarAsistencia(codigo); break;
		}
	} while (op != 0);
}

void menuAdmin() {
	int op;
	do {
		printf("\n=== MENU ADMINISTRATIVO ===\n");
		printf("1. Registrar Paciente\n");
		printf("2. Registrar Medico\n");
		printf("3. Listar Pacientes\n");
		printf("4. Listar Medicos\n");
		printf("5. Listar Todas las Citas\n");
		printf("6. Generar Reportes\n");
		printf("7. Eliminar Paciente\n"); // <--- NUEVA OPCION
		printf("0. Salir\n");
		printf("Opcion: ");
		scanf("%d", &op);
		
		switch (op) {
		case 1: registrarPaciente(); break;
		case 2: registrarMedico(); break;
		case 3: listarPacientes(); break;
		case 4: listarMedicos(); break;
		case 5: listarCitas(); break;
		case 6: generarReporte(); break;
		case 7: eliminarPacienteAdmin(); break; // <--- LLAMADA A LA FUNCION
		}
	} while (op != 0);
}
// --- MAIN PRINCIPAL ---

int main() {
	int op;
	char idSesion[15];
	
	do {
		printf("\n=== SISTEMA HOSPITALARIO ===\n");
		printf("1. Acceso Paciente\n");
		printf("2. Acceso Medico\n");
		printf("3. Acceso Administrativo\n");
		printf("4. Registrarse como Nuevo Paciente\n");
		printf("0. Salir\n");
		printf("Opcion: ");
		scanf("%d", &op);
		
		switch (op) {
		case 1:
			if (loginPaciente(idSesion)) {
				printf("Bienvenido Paciente.\n");
				menuPaciente(idSesion);
			} else {
				printf("Credenciales incorrectas.\n");
			}
			break;
		case 2:
			if (loginMedico(idSesion)) {
				printf("Bienvenido Doctor.\n");
				menuMedico(idSesion);
			} else {
				printf("Credenciales incorrectas.\n");
			}
			break;
		case 3:
			if (loginAdmin()) {
				printf("Bienvenido Admin.\n");
				menuAdmin();
			} else {
				printf("Credenciales incorrectas.\n");
			}
			break;
		case 4:
			registrarPaciente();
			break;
		case 0:
			printf("Saliendo del sistema...\n");
			break;
		default:
			printf("Opcion no valida.\n");
		}
	} while (op != 0);
	
	return 0;
}
