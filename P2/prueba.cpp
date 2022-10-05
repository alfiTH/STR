#include "ClasesPosix.h"
#include <stdio.h>

typedef struct {
	hilo_t *h;
	int *dato;
	mutex_t *m;
	variable_condicion_t *v;
	bool *pueden_restar;
} DatosHilo_t;

#define ITER_PER_HILO 6
#define NUM_HILOS 5
#define MAX_VAL (1<<(ITER_PER_HILO*NUM_HILOS))
bool debug=false;

void *hiloSumador(void *aux) {
	DatosHilo_t datos=*((DatosHilo_t*)aux);
	for (int i=0; i<ITER_PER_HILO; i++) {
		datos.m->Lock();
		(*(datos.dato))*=2;
		if (debug) printf("hilo %d incrementando dato hasta %d\n", datos.h->ObtenerIdentificador(), *datos.dato);
		if (*datos.dato == MAX_VAL) {
			(*datos.pueden_restar)=true;
			datos.v->Broadcast();
		}
		datos.m->Unlock();
	}
}

void *hiloRestador(void *aux) {
	DatosHilo_t datos=*((DatosHilo_t*)aux);
	for (int i=0; i<ITER_PER_HILO; i++) {
		datos.m->Lock();
		while (!(*datos.pueden_restar)) {
			if (debug) printf("Hilo %d bloqueado porque dato vale %d\n", datos.h->ObtenerIdentificador(), *datos.dato);
			datos.v->Wait();
		}
		if (debug) printf("hilo %d decrementando dato hasta %d\n", datos.h->ObtenerIdentificador(), *datos.dato);
		(*datos.dato)--;
		datos.m->Unlock();
	}
}

int main(int argc, char* argv[]) {
	if (argc>2) {
		printf("Error de ejecución. El formato correcto es %s [d]\n", argv[0]);
		return 0;
	}
	else if (argc==2 && argv[1][0]!='d') {
		printf("Error de ejecución. El formato correcto es %s [d]\n", argv[0]);
		return 0;
	}
	debug=argc==2 && argv[1][0]=='d';
	hilo_t hilos[2][10];
	DatosHilo_t datos[2][10];
	int dato=1;
	bool pueden_restar=false;
	mutex_t m;
	variable_condicion_t v;
	m.Inicializar();
	v.Inicializar(m.ObtenerManejador());
	for (int j=0; j<NUM_HILOS; j++) {
		datos[0][j].h=&hilos[0][j];
		datos[0][j].dato=&dato;
		datos[0][j].pueden_restar=&pueden_restar;
		datos[0][j].m=&m;
		datos[0][j].v=&v;
		datos[0][j].h->AsignarFuncionYDato(hiloSumador, &datos[0][j]);
		datos[0][j].h->Lanzar();
		
		datos[1][j].h=&hilos[1][j];
		datos[1][j].dato=&dato;
		datos[1][j].pueden_restar=&pueden_restar;
		datos[1][j].m=&m;
		datos[1][j].v=&v;
		datos[0][j].h->AsignarFuncionYDato(hiloRestador, &datos[1][j]);
		datos[0][j].h->Lanzar();
	}
	for (int i=0; i<2; i++) {
		for (int j=0; j<NUM_HILOS; j++) {
			datos[i][j].h->Join();
		}
	}
	
	if (dato==MAX_VAL-ITER_PER_HILO*NUM_HILOS)
		printf("La ejecución es correcta\n");
	else
		printf("Datos tiene el valor %d y debería ser %d\n", dato, MAX_VAL-ITER_PER_HILO*NUM_HILOS);
}