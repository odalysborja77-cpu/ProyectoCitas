#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
Creacion de una estructura que nos permitira guardar los 
datos de los estudiantes que ingrese el usuario
*/
struct Estudiantes{
	char Nombre[20];
	int identificacion;
	float calificacion;
};
//Prototipos de las funciones a usarse en este programa
void elimininar(int eliminado);
void recalificar(int nuevanota);
void buscar(int buscado);

int main(){

	struct Estudiantes alumno;
	//Menu de opciones para que el usuario eliga uno
	int opcion, busco, actu, elimi; //variables a usar para realizar las acciones del programa
	printf ("---MENU DE ACCIONES ---");
	printf ("\n1. Agregar estudiante");
	printf ("\n2. Mostrar estudiantes");
	printf ("\n3. Buscar estudiante por ID");
	printf ("\n4. Actualizar nota del estudiante");
	printf ("\n5. Eliminar estudiante");
	printf ("\n6. Guardar en archivo");
	printf ("\n7. Salir");
	//Se valida que la opcion escogida sea entre 1 y 7
	printf ("\nIngrese la accion que desea realizar: ");
	while ((scanf("%i", &opcion) != 1) || (opcion < 1) || (opcion > 7)){
	printf ("\nEl valor debe ser un numero entre 1 y 7: ");
	while (getchar() == '\n'); //Limpiamos basura en el buffer
	}
	switch (opcion){
	case 1:
		//Se pide los datos de los estudiantes: Nombre, ID y calificacion
		printf ("\nIngrese el nombre del estudiante: ");
		scanf("%s", alumno.Nombre);
		fgets(alumno.Nombre, 20, stdin);
		alumno.Nombre[strcspn(alumno.Nombre, "\n")] = '\0';
		printf ("\nIngrese la ID del estudiante: ");
		scanf ("%i", &alumno.identificacion);
		printf ("\nIngrese la calificacion del alumno (0 - 10): ");
		scanf ("%f", &alumno.calificacion);
		while ((alumno.calificacion < 0) || (alumno.calificacion > 10)){
			printf ("Nota fuera del rango(0 - 10), ingrese nuevamente: ");
			scanf ("%f", &alumno.calificacion);
			
		}
		break;
	default: printf ("\nError en ingreso de datos");break;
	
	case 2:
		printf ("\nEstudiantes agregados: ");
		printf ("%s %i %f", alumno.Nombre, alumno.identificacion, alumno.calificacion);
		break;
	case 3: 
	printf ("Ingrese el ID del estudiante que desee buscar: ");
	scanf ("%i", &busco); break;
	case 4:
	printf ("Ingrese el ID del estudiante que quiere actualizar la nota: ");
	scanf ("%i", &actu); break;
	case 5:
		printf ("Ingrese el ID del estudiante que quiere eliminar: ");
		scanf ("%i", &elimi);
		break;
	case 6:
		printf ("Se guardo correctamente los datos en el archivo.");
		break;
	case 7: printf ("Saliendo del sistema, muchas gracias por usar la aplicacion"); break;
		
	}
	return 0;
}
	//Funcion para eliminar estudiante
	void elimininar(int eliminado){
		int deleted;
		if (eliminado == deleted ){
			printf ("Estudiante eliminado con exito.");
			return;
		}
	}
		


