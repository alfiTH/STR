/**
 * @file pila_acotada.cpp
 * @author Alejandro Torrejon Harto (atorrjo@alumnos.unex.es)
 * @brief 
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "pila_acotada.h"


/**
 * @brief Construct a new Pila Acotada:: Pila Acotada object
 * 
 */
PilaAcotada::PilaAcotada()
{
	PilaAcotada(10);
}

/**
 * @brief Construct a new Pila Acotada:: Pila Acotada object
 * 
 * @param maxSize Maximo tamaño de la pila
 */
PilaAcotada::PilaAcotada(int maxSize)
{
	this->maxSize =maxSize;
	this->mutex.Inicializar();
	this->llena.Inicializar(mutex.ObtenerManejador());
	this->vacia.Inicializar(mutex.ObtenerManejador());
}

/**
 * @brief Añade a la pila acotada el parámetro de entrada
 * 
 * @param add int a añadir en la pila_acotada
 */
void PilaAcotada::PilaAniadir(int add)
{
	this->mutex.Lock(); 				//bloqueamos mutex

	while(this->pila.size() == maxSize)	//hasta que no haya espacio para meter nos esperamos
		this->llena.Wait();				//desbloqueamos mutex a la espera
	this->pila.push_back(add);			//metemos en pila

	this->mutex.Unlock();				//desbloqueamos mutex
	this->vacia.Signal();				//avisamos si alguien esta esperando en caso de haber estado vacia
}

/**
 * @brief  Saca un elemento de la pila acotada
 * 
 * @return int parámetro extraído de la pila
 */
int PilaAcotada::PilaSacar()
{
	this->mutex.Lock();					//bloqueamos mutex

	while(this->pila.size() == 0)	//hasta que no haya elementos para sacar nos esperamos
		this->vacia.Wait();			//desbloqueamos mutex a la espera
	int aux = this->pila.back();	//obtenemos dato de pila
	this->pila.pop_back();			//eliminamos dato de pila
	this->mutex.Unlock();			//desbloqueamos mutex
	this->llena.Signal();			//avisamos si alguien esta esperando  en caso de haber estado llena
	return aux;						//retornamos el dato extraído de la pila
}


