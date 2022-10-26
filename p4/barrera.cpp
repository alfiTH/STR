#include "barrera.h"

//Implementación del constructor sin parámetros
Barrera::Barrera()
{
	Barrera(10);
}
	//Inicializar el tamaño máximo de la barrera a 10 (llamar al constructor con un parámetro usando 10 como parámetro)
	
//Fin del constructor sin parámetros


//Implementación del constructor con un parámetro para indicar el tamaño máximo de la barrera
Barrera::Barrera(int numHilos)
{
	this->numHilos = numHilos;
	this->hilosBlock = 0;
	this->mutex.Inicializar();
	this->cond.Inicializar(this->mutex.ObtenerManejador());
}
	//Inicializar el tamaño máximo de la barrera al valor introducido por parámetro
	
	//Inicializar el número de hilos actuales en la barrera a 0
	
	//Inicializar el mutex de la clase
	
	//Inicializar la variable de condición de la clase asociándole el manejador del mutex de la clase
	
//Fin del constructor con un parámetro


/*Implementación del método Sincronizar. Este método bloqueará el hilo invocante en la barrera si no se ha alcanzado el número indicado
o liberará a todos los hilos si es el último hilo en llegar. Reseteará también la barrera, dejándola lista para  volver a utilizarla
*/
void Barrera::Sincronizar()
{
	this->mutex.Lock();
	this->hilosBlock++;
	if (this->numHilos>this->hilosBlock)
		this->cond.Wait();
	else
	{
		this->cond.Broadcast();
		this->Resetear();
	}

	this->mutex.Unlock();

}

//Entrar en el mutex
	
	//Incrementar el número de hilos en la barrera
	
	//Si han llegado todos los hilos esperados
	
		//Liberar a todos los hilos de la variable de condición
		
		//Resetear la barrera
			
	//Si no
	
		//Bloquearse en la variable de condición
		
	//Liberar el mutex
	
//Fin del método Sincronizar


/*Implementación del método Resetear sin parámetros. Este método pondrá a cero el número de hilos que han llegado a la barrera.
Si no han llegado todos los hilos esperados a la barrera, no se realizará el reseteo de la misma (esto previene que se resetee la barrera antes de que lleguen todos los hilos)*/
void Barrera::Resetear()
{
	if (this->hilosBlock >=this->numHilos)
		this->hilosBlock = 0;
}
	//Si han llegado a la barrera todos los hilos esperados
	
		//Poner a cero el contador de los hilos
		
//Fin del método Resetear sin parámetros

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
	//Si han llegado a la barrera todos los hilos esperados
	
		//Poner a cero el contador de los hilos
		
		//Cambiar el número de hilos por los que se esperará usando el parámetro de entrada del método
		
//Fin del método Resetear sin parámetros
