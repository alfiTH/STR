#include "barrera.h"

/**
 * @brief Construct a new Barrera:: Barrera object
 * 
 */
Barrera::Barrera()
{
	Barrera(10);
}

/**
 * @brief Construct a new Barrera:: Barrera object
 * 
 * @param numHilos 
 */
Barrera::Barrera(int numHilos)
{
	this->numHilos = numHilos;
	this->hilosBlock = 0;
	this->mutex.Inicializar();
	this->cond.Inicializar(this->mutex.ObtenerManejador());
}


/**
 * @brief Este método bloqueará el hilo invocante en la barrera si no se ha alcanzado el número indicado
 * o liberará a todos los hilos si es el último hilo en llegar. Reseteará también la barrera, dejándola lista para  volver a utilizarla
 */
void Barrera::Sincronizar()
{
	this->mutex.Lock();
	this->hilosBlock++;
	//Liberar a todos los hilos de la variable de condición y resetea
	if (this->numHilos>this->hilosBlock)
		this->cond.Wait();
	//Bloquearse
	else
	{
		this->cond.Broadcast();
		this->Resetear();
	}

	this->mutex.Unlock();
}

/**
 * @brief Este método pondrá a cero el número de hilos que han llegado a la barrera, Si han llegado todos los hilos 
 * 
 */
void Barrera::Resetear()
{
	if (this->hilosBlock >=this->numHilos)
		this->hilosBlock = 0;
}

/**
 * @brief Este método pondrá a cero el número de hilos que han llegado a la barrera, Si han llegado todos los hilos 
 * @param numHilos numero de hilos nuevos para la barrera
 */
/*Implementación del método Resetear con un parámetro. Este método pondrá a cero el número de hilos que han llegado a la barrera.
Si no han llegado todos los hilos esperados a la barrera, no se realizará el reseteo de la misma (esto previene que se resetee la barrera antes de que lleguen todos los hilos).
por último, cambiará el número de hilos por los que se esperará en la barrera*/
void Barrera::Resetear(int numHilos)
{
	if (this->hilosBlock >=this->numHilos)
	{
		this->hilosBlock = 0;
		this->numHilos = numHilos;
	}
		
}