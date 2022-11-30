// Ejecución: para poder modificar los atributos del hilo, debemos ejecutar como superusuario: sudo ./p4 fichero_tareas
#include <stdio.h>
#include <stdlib.h>
#include "funciones_time.h"
#include <ClasesPosix.h>

void ImprimirInicio(int id, int prioridad) {
	printf("Hilo %d con prioridad %d comienza su acción periódica\n", id, prioridad);
}

void ImprimirFinal(int id) {
	printf("Hilo %d termina su acción periódica\n", id);
}

void ImprimirFranjaMS(int x) {
	printf("************************* %d ms *************************\n", x);
}

//La función Ejecutar mantiene la ejecución durante n milisegundos
void Ejecutar(int n)
{
    int i;
	struct timespec ini, fin, dif;
	int finb=0;
	double y=n/1000.0;
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ini);
	while (!finb) {
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &fin);
		dif=RestaTimeSpec(fin, ini);
		if (timespec2segundos(dif)>=y)
			finb=1;
	}
}

//Definir la función TareaPeriodicaGenerica que reciba un parámetro de tipo puntero a hilo_t (recordemos que el tipo de la función debe ser puntero a void y luego convertimos)
void * TareaPeriodicaGenerica(void *data)
{
	//El parámetro es un dato de tipo hilo_t
	hilo_t hilo=*((hilo_t *)data);
	
	//Definir tres variables de tipo struct timespec para almacenar el instante de comienzo, el instante siguiente y el periodo de repetición
	struct timespec comienzo, siguiente, repeticion;
	//Obtener el periodo de repetición del hilo actual mediante el método ObtenerPeriodo de la clase hilo_t
	repeticion = hilo.ObtenerPeriodo();
	//Obtener el instante de comienzo del hilo actual mediante el método ObtenerInstanteDeComienzo de la clase hilo_t
	comienzo = hilo.ObtenerInstanteDeComienzo();
	//Calcular el siguiente instante sumando el instante de comienzo y el periodo
	siguiente = SumaTimeSpec(comienzo, repeticion);
	//Dormir el hilo hasta el instante de comienzo
	if (clock_nanosleep (CLOCK_MONOTONIC, TIMER_ABSTIME, &comienzo, NULL)) pthread_exit((void*)-1);
	//Definir un bucle infinito
	while (true)
	{
		/*Imprimir el mensaje "Hilo id con prioridad P comienza su acción periódica", siendo "id" y "P" el identificador y la prioridad del hilo respectivamente (usar la función
		ImprimirInicio y los métodos ObtenerIdentificador y ObtenerPrioridad de la clase hilo_t para obtener los valores a mostrar)*/
		ImprimirInicio(hilo.ObtenerIdentificador(),hilo.ObtenerPrioridad());
		//Ejecutar la función Ejecutar usando como parámetro el tiempo de ejecución del hilo (método ObtenerTiempoEjecucion de la clase hilo_t)
		Ejecutar(hilo.ObtenerTiempoEjecucion());
		//Imprimir el mensaje "Hilo id termina su acción periódica", siendo "id" el identificador del hilo (usar la función ImprimirFinal y el método ObtenerIdentificador de la clase hilo_t)
		ImprimirFinal(hilo.ObtenerIdentificador());
		//Dormir el hilo hasta el siguiente instante de repetición
		if (clock_nanosleep (CLOCK_MONOTONIC, TIMER_ABSTIME, &siguiente, NULL)) pthread_exit((void*)-1);
		//Incrementar el siguiente instante de repetición con el periodo
		siguiente = SumaTimeSpec(siguiente, repeticion);
	//Fin bucle
	}
//Fin TareaPeriodicaGenerica
	return nullptr;
}

//Definir la función TareaMostrarTiempos que reciba un parámetro de tipo puntero a hilo_t (recordemos que el tipo de la función debe ser puntero a void y luego convertimos)
void * TareaMostrarTiempos(void *data)
{
	//El parámetro es un dato de tipo hilo_t
	hilo_t hilo=*((hilo_t *)data);
	//Definir tres variables de tipo struct timespec para almacenar el instante de comienzo, el instante siguiente y el periodo de repetición
	struct timespec comienzo, siguiente, repeticion;
	//Obtener el periodo de repetición del hilo actual mediante el método ObtenerPeriodo de la clase hilo_t
	repeticion = hilo.ObtenerPeriodo();
	//Obtener el instante de comienzo del hilo actual mediante el método ObtenerInstanteDeComienzo de la clase hilo_t
	comienzo = hilo.ObtenerInstanteDeComienzo();
	//Calcular el siguiente instante sumando el instante de comienzo y el periodo
	siguiente = SumaTimeSpec(comienzo, repeticion);
	//Dormir el hilo hasta el instante de comienzo
	if (clock_nanosleep (CLOCK_MONOTONIC, TIMER_ABSTIME, &comienzo, NULL)) pthread_exit((void*)-1);
	//Para i desde 0 hasta 100
	for (int i = 0; i <100; i++)
	{
	//Imprimir "************************* x ms *************************\n" (usar ImprimirFranjaMS), siendo x=i*10 los milisegundos actuales
	ImprimirFranjaMS(i*10);
	if (clock_nanosleep (CLOCK_MONOTONIC, TIMER_ABSTIME, &siguiente, NULL)) pthread_exit((void*)-1);
	//Incrementar el siguiente instante de repetición con el periodo
	siguiente = SumaTimeSpec(siguiente, repeticion);
	//Fin Para
	}
		

//Fin TareaMostrarTiempos
	return nullptr;
}
	

int main(int argc, char *argv[]) {
	int num_tareas, i, C, T, P;
	FILE *f;
	if (argc!=2) {
		printf("El formato de ejecución correcto es %s fichero_tareas\n", argv[0]);
		return 0;
	}
	f=fopen(argv[1], "r");
	if(f==NULL) {
		printf("Error al abrir el fichero %s\n", argv[3]);
		return 0;
	}
	fscanf(f, "%d\n", &num_tareas);

	//Definir una variable de tipo timespec para almacenar el instante de comienzo
	struct timespec comienzo;
	//Leer la hora actual y almacenarla en la variable anterior
	clock_gettime(CLOCK_MONOTONIC, &comienzo);
	//Sumar 2 segundos al tiempo de comienzo (se puede sumar 2 directamente al campo tv_sec de la variable)
	comienzo.tv_sec +=2;
	//Definir un vector de tamaño num_tareas de tipo hilo_t (no usar la clase vector). Este vector permitirá manejar los hilos que ejecutarán las tareas periódicas.
	hilo_t tareas[num_tareas];
	//Definir una variable de tipo hilo_t para manejar el hilo que mostrará las franjas de tiempo
	hilo_t manejador;

	for (i=0; i<num_tareas; i++) {
		fscanf(f, "%d %d %d\n", &C, &T, &P);
		printf("t%d: %d %d %d\n", i+1, C, T, P);

		//Asignar al hilo i-ésimo la función TareaPeriodicaGenerica y el propio hilo i-ésimo como parámetro (será necesario dentro de la función para poder obtener los datos del hilo)
		tareas[i].AsignarFuncionYDato(TareaPeriodicaGenerica, &tareas[i]);
		/*Asignar al hilo i-ésimo la prioridad (P), la política FIFO (SCHED_FIFO), la no herencia de atributos (PTHREAD_EXPLICIT_SCHED), el periodo (T), el tiempo de ejecución (C)
		y el instante de comienzo. Para ello, usar el método EstablecerAtributos de la clase hilo_t*/
		tareas[i].EstablecerAtributos(P, SCHED_FIFO, PTHREAD_EXPLICIT_SCHED, T, C, comienzo );
		//Lanzar el hilo i-ésimo
		tareas[i].Lanzar();

	}
	
	//Asignar al hilo que mostrará las franjas de tiempo la función TareaMostrarTiempos y el propio hilo como parámetro (será necesario dentro de la función para poder obtener los datos del hilo)
	manejador.AsignarFuncionYDato(TareaMostrarTiempos, &manejador);
	/*Asignar al hilo que mostrará las franjas de tiempo la prioridad máxima para la política FIFO (usar la función sched_get_priority_max), la política FIFO (SCHED_FIFO),
	la no herencia de atributos (PTHREAD_EXPLICIT_SCHED), el periodo (10), el tiempo de ejecución (0, no es necesario para este hilo pero hay que darle un valor)
	y el instante de comienzo. Para ello, usar el método EstablecerAtributos de la clase hilo_t*/
	manejador.EstablecerAtributos(sched_get_priority_max(SCHED_FIFO), SCHED_FIFO, PTHREAD_EXPLICIT_SCHED, 10, 0, comienzo );
	//Lanzar el hilo que mostrará las franjas de tiempo
	manejador.Lanzar();
	//Esperar únicamente por la finalización del hilo que mostrará las franjas de tiempo
	manejador.Join();
	return 0;
}
