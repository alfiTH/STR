#include "pila_acotada.h"

//Implementación del constructor sin parámetros
PilaAcotada::PilaAcotada()
{
	PilaAcotada(10);
}
	//Llamar al constructor con un parámetro usando 10 como parámetro

//Fin del constructor sin parámetros


//Implementación del constructor con un parámetro para indicar el tamaño máximo de la pila

PilaAcotada::PilaAcotada(int maxSize)
{
	this->maxSize =maxSize;
	this->mutex.Inicializar();
	this->llena.Inicializar(mutex.ObtenerManejador());
	this->vacia.Inicializar(mutex.ObtenerManejador());
}
	//Asociar el mutex de la clase a las dos variables de condición de la clase. Para ello, hay que pasar el manejador del mutex al método AsociarManejadorMutex de las variables de condición

//fin del constructor con un parámetro


//Implementación del método PilaAniadir con un parámetro de entrada de tipo entero
void PilaAcotada::PilaAniadir(int add)
{
	this->mutex.Lock();

	while(this->pila.size() == maxSize)
		this->llena.Wait();
	this->pila.push_back(add);
	this->mutex.Unlock();
	this->vacia.Signal();
}

	//Acceder a la región crítica a través del mutex

	//Mientras la pila esté llena, bloquearse en la variable de condición de la pila llena

	//Añadir elem en la cima de la pila

	//Liberar el mutex

	//Liberar, al menos, un hilo de la variable de condición de la pila vacia

//Fin del método PilaAniadir


//Implementación del método PilaSacar sin parámetros y que retorna un entero
int PilaAcotada::PilaSacar()
{
	this->mutex.Lock();
	while(this->pila.size() == 0)
		this->vacia.Wait();
	int aux = this->pila.back();
	this->pila.pop_back();
	this->mutex.Unlock();
	this->llena.Signal();
	return aux;
}
	//Acceder a la región crítica a través del mutex

	//Mientras la pila esté vacía, bloquearse en la variable de condición de la pila vacia

	//Definir una variable entera y guardar ahí el valor contenido en la cima de la pila

	//Eliminar el elemento contenido en la cima de la pila

	//Liberar el mutex

	//Hacer un signal en la variable de condición de la pila llena

	//Devolver el elemento leído

//Fin del método PilaSacar

