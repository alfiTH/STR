#include "ClasesPosix.h"
#include "Identificador.h"
#include <stdio.h>

Identificador_t Identificador;

/*
**********************************************************
********************** Clase hilo_t **********************
**********************************************************
*/


/**
 * @brief Construct a new hilo_t::hilo_t object
 * Implementación del constructor sin parámetros. 
 * Este método reservará memoria para los atributos de la clase e inicializará los atributos de creación del hilo
 */
hilo_t::hilo_t()
{
	//Guardar el resultado de Identificador.ObtenerId() en el atributo de clase que almacena el identificador del hilo
	this->id = Identificador.ObtenerId();	
	//Reserva de memoria para el manejador del hilo
	this->manHilo = new pthread_t;	
	//Reserva de memoria para los atributos de creación del hilo
	this->attrHilo = new pthread_attr_t;	
	//Inicialización de los atributos de creación del hilo
	pthread_attr_init(this->attrHilo);	
	//Inicialización de la función del hilo a NULL
	this->funcHilo = NULL;	
	//Inicialización de los datos de la función del hilo a NULL
	this->parm = NULL;
}


/**
 * @brief Destroy the hilo_t::hilo_t object
 * Implementación del destructor sin parámetros. Este método destruirá 
 * los atributos de creación del hilo y liberará la memoria de los atributos de la clase
 */
hilo_t::~hilo_t()
{
	//Liberación la memoria del manejador del hilo
	delete this->manHilo;
	//Destrucción de los atributos de creación del hilo
	pthread_attr_destroy(this->attrHilo);
	//Liberación de memoria de los atributos de creación del hilo
	delete this->attrHilo;
}


/**
 * @brief 
*Este método se encargará de lanzar un hilo usando los atributos almacenados en la clase: el manejador de hilo, los atributos de
*creación del hilo, la función asociada y el dato que se usará con la función. Deberá comprobar
*si se ha asociado previamente una función (debe tener valor distinto a NULL), en cuyo caso
*lanzará el hilo y devolverá el valor que retorne la función Posix de creación de hilos. En caso de
*no existir función asociada, devolverá -1
 *
 * @return int 
 */
int hilo_t::Lanzar()
{
	//Si la función asociada no existe
	if(this->funcHilo == NULL)
        return -1;	
	//Si la función asociada existe (no es NULL), Crear un hilo usando como parámetros el manejador
	//del hilo, los atributos de creación del hilo, la función del hilo y los datos del hilo.
	//Se devolverá el resultado de la llamada a pthread_create*/
	else
		pthread_create(this->manHilo, this->attrHilo, this->funcHilo, this->parm);
	return 0;
}


/**
 * @brief Asignará el parámetro recibido al atributo que almacena la función del hilo
 *
 * @param funcHilo Esta función se encargará de asignar el parámetro recibido al atributo de clase que
 *almacena la función asociada al hilo.
 */
void hilo_t::AsignarFuncion(void *(*funcHilo)(void *))
{
	//Asignar el parámetro del método al atributo de la clase que almacena la función asociada
	this->funcHilo = funcHilo;
	return;
}


/**
 * @brief Esta función se encarga de almacenar el parámetro recibido en el atributo de la clase que almacena
 *el dato que se usará con la función asociada al hilo.
 * 
 * @param dato 
 */
void hilo_t::AsignarDato(void* dato)
{
	//Asignar el parámetro del método al atributo de la clase que almacena el parámetro que se usará con la función asociada
	this->parm = dato;
	return;
}


/**
 * @brief 	Esta función es una combinación de las dos anteriores
 *(AsignarFuncion y AsignarDato), por lo que tendrá los parámetros de ambas (primero la
 *función y luego el dato). Simplemente llamará a estas dos funciones con sus respectivos
 *parámetros.
 * 
 * @param funcHilo 
 * @param dato 
 */
void hilo_t::AsignarFuncionYDato (void *(*funcHilo)(void *), void* dato)
{
	//Llamar a AsignarFuncion
	this->AsignarDato(dato);
	this->AsignarFuncion(funcHilo);
	return;
}


/**
 * @brief Este método esperará por el hilo indicado por el manejador de la clase. 
 * 
 * @return * void Valor obtenido por la función Posix de espera por un hilo
 */
void* hilo_t::Join()
{
	//Definir una variable de tipo puntero a void (debe ser puntero a void para permitir que se pueda devolver cualquier tipo de dato). No hay que reservar memoria.
	void* aux;

	/*Esperar por el hilo asociado a la clase usando como parámetros el valor del manejador del hilo (como es un puntero, hay que poner el carácter '*' delante del nombre para acceder a su valor)
	y la dirección de memoria de la variable definida en la línea anterior (poner el carácter '&' antes del nombre de la variable para acceder a su dirección de memoria).*/
	pthread_join(*this->manHilo, &aux);
	//Devolver la variable definida en la primera línea del método.
	return aux;
}



/**
 * @brief  Este método devolverá el valor del manejador del hilo asociado a la clase.
 * Aunque el manejador del hilo se
 *almacena como un puntero, este método no devuelve un puntero, ya que no será necesario
 *usarlo de esa forma fuera de la clase. Por tanto, para acceder al contenido del puntero,
 *debemos poner el carácter ‘*’ delante del nombre del manejador, accediendo así al contenido
 *de la dirección de memoria del mismo.
 * 
 * @return pthread_t* Manejador del hilo
 */
pthread_t hilo_t::ObtenerManejador()
{
	//Devolver el valor del manejador del hilo (como es un puntero, hay que poner el carácter '*' delante del nombre para acceder a su valor)
	return *this->manHilo;
}


/**
 * @brief Este método devolverá el identificador del hilo.
 * 
 * @return int Identificador del hilo
 */
int hilo_t::ObtenerIdentificador()
{
	//Devolver el identificador del hilo
	return this->id;
}

