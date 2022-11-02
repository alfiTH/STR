#include <stdlib.h>
#include <stdio.h>
#include <ClasesPosix.h>
#include <signal.h>
//Añadir la librería de utilización de señales


void senial_capturada(int capturadas, int max_capturas) {
	printf("Se han capturado %d señales SIGINT de %d.\n", capturadas, max_capturas);
}

/*Definir la función HiloSigInt para la creación de un hilo que capture la señal SIGINT siguiendo el formato específico de este tipo de funciones (ver apuntes del tema 2
o el anexo de la práctica). Tendrá un parámetro de entrada que indicará el número de señales a capturar*/
void * HiloSigInt( void * data)
{
	int maxSig = *((int *)data);
	int sig;
	int counter = 0;
	//Crear un conjunto de señales
	sigset_t set;
		//Inicializar el conjunto de señales a vacío
	sigemptyset(&set);
	//Añadir SIGINT al conjunto de señales
	sigaddset(&set, SIGINT);
	//Añadir el conjunto de señales a la máscara de señales bloqueadas
	pthread_sigmask(SIG_BLOCK, &set, NULL);
	//Mientras no se hayan capturado las señales esperadas
	while (counter < maxSig)
	{
		if (sigwait(&set, &sig)!= 0)pthread_exit((void*)-1);
		if  (sig == SIGINT)
		{
			counter++;
			senial_capturada(counter, maxSig);
		}
	}
	return nullptr;
}



int main (int argc, char *argv[]) {
	if (argc!=2) {
		printf("Error en la ejecución. El formato correcto es %s num_capturas\n", argv[0]);
		return 0;
	}
	int num_capturas=atoi(argv[1]);
	if (num_capturas<1) {
		printf("Error en la ejecución. El número mínimo señales a capturar debe ser 1\n");
		return 0;
	}
	//Crear un conjunto de señales
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	//Inicializar el conjunto de señales a vacío
	
	//Añadir SIGINT al conjunto de señales
	
	//Añadir el conjunto de señales a la máscara de señales bloqueadas
	pthread_sigmask(SIG_BLOCK, &set, NULL);
	//Crear un manejador de hilo usando la clase hilo_t
	hilo_t hilo;
	//Asignar la función HiloSigInt y la dirección de memoria del número de capturas por las que se desea esperar (num_capturas) al manejador definido en el punto anterior
	hilo.AsignarFuncionYDato(HiloSigInt, &num_capturas);
	//Lanzar el hilo
	hilo.Lanzar();
	//Esperar por el hilo
	hilo.Join();
}
