#include "ClasesPosix.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define NUMHILOS 15

int r[NUMHILOS];

typedef struct {
	hilo_t *h;
	int dato;
} datos_hilos_t;

void *func_hilo(void* aux) {
	datos_hilos_t x=*((datos_hilos_t *)aux);
	printf("Ejecutando hilo %d con parámetro %d\n", x.h->ObtenerIdentificador(), x.dato);
	r[x.h->ObtenerIdentificador()]=x.dato*100;
	pthread_exit((void*)&r[x.h->ObtenerIdentificador()]);
}

int main(void) {
	hilo_t hilos[NUMHILOS];
	datos_hilos_t datos[NUMHILOS];
	int resultados[NUMHILOS];

	for (int i=0; i<NUMHILOS; i++) {
		datos[i].dato=i;
		datos[i].h=&hilos[i];
		hilos[i].AsignarFuncionYDato(func_hilo, &datos[i]);
		hilos[i].Lanzar();
	}
	for (int i=0; i<NUMHILOS; i++) {
		resultados[i]=*((int*)hilos[i].Join());
		if (resultados[i]==datos[i].dato*100) printf("El hilo %d ha dado el resultado correcto (%d)\n", hilos[i].ObtenerIdentificador(), resultados[i]);
		else printf("El hilo %d no ha dado el resultado correcto (%d)\n", hilos[i].ObtenerIdentificador(), resultados[i]);
	}
	printf("Todos los hilos han terminado\n");
	return 0;
}