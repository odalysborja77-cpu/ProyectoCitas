#ifndef PACIENTES_H
#define PACIENTES_H

typedef struct {
	char cedula[15];
	char nombre[50];
	int edad;
	char telefono[15];
	char correo[50];
} Paciente;

void registrarPaciente();
void listarPacientes();
int existePaciente(char cedula[]);
void eliminarPacienteAdmin();

#endif
