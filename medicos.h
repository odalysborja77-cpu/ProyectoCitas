#ifndef MEDICOS_H
#define MEDICOS_H

typedef struct {
	char codigo[10];
	char nombre[50];
	char especialidad[30];
	char horario[20];
} Medico;

void registrarMedico();
void listarMedicos();
int existeMedico(char codigo[]);

#endif
