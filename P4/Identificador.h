#include <pthread.h>

class Identificador_t {
private:
	int cont;
	pthread_mutex_t *manejador;
public:
	Identificador_t();
	int ObtenerId();
};