#include <ClasesPosix.h>

//Definir la clase Barrera
class Barrera
{
//Zona pública
public:
	//Definir un constructor sin parámetros
	Barrera();
	//Definir un constructor con un parámetro para indicar el número de hilos que se sincronizarán en la barrera
	Barrera(int numHilos);
	/*Definir el método Sincronizar que bloqueará al hilo invocante en la barrera (no han llegado todos)
	o liberará a todos los hilos bloqueados (es el último hilo en llegar)*/
	void Sincronizar();
	//Definir el método Resetear sin parámetro para resetear la barrera
	void Resetear();
	//Definir el método Resetear con un parámetro entero para resetear la barrera cambiando el número de hilos
	void Resetear(int numHilos);
//Zona privada
private:
	//Definir una variable entera para almacenar el número de hilos que deben llegar a la barrera antes de dejarlos pasar
	int numHilos;
	//Definir una variable entera para almacenar cuántos hilos han llegado ya a la barrera
	int hilosBlock;
	//Definir el mutex (usar la clase mutex_t)
	mutex_t mutex;
	//Definir la variable de condición (usar la clase variable_condicion_t)
	variable_condicion_t cond;
//Fin de la clase
};
