#include "Identificador.h"
#include <stdlib.h>

Identificador_t::Identificador_t() {
	cont=1;
	manejador=(pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(manejador, NULL);
}

int Identificador_t::ObtenerId() {
	int c;
	pthread_mutex_lock(manejador);
	c=cont;
	cont++;
	pthread_mutex_unlock(manejador);
	return c;
}
