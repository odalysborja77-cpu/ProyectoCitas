#ifndef CITAS_H
#define CITAS_H

void asignarCita();
void listarCitas();
void verCitasPaciente(char cedula[]);
void verCitasMedico(char codigo[]);
void cancelarCita(char idUsuario[]); // Sirve para médico y paciente
void registrarAsistencia(char codigo[]);

#endif
