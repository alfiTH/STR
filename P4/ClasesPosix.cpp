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
	this->id = Identificador.ObtenerId();	
	this->manHilo = new pthread_t;	
	this->attrHilo = new pthread_attr_t;	
	pthread_attr_init(this->attrHilo);	
	this->funcHilo = NULL;	
	this->parm = NULL;
}

/**
 * @brief Destroy the hilo_t::hilo_t object
 * Implementación del destructor sin parámetros. Este método destruirá 
 * los atributos de creación del hilo y liberará la memoria de los atributos de la clase
 */
hilo_t::~hilo_t()
{
	delete this->manHilo;
	pthread_attr_destroy(this->attrHilo);
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
	void* aux;
	/*Esperar por el hilo asociado a la clase usando como parámetros el valor del manejador del hilo (como es un puntero, hay que poner el carácter '*' delante del nombre para acceder a su valor)
	y la dirección de memoria de la variable definida en la línea anterior (poner el carácter '&' antes del nombre de la variable para acceder a su dirección de memoria).*/
	pthread_join(*this->manHilo, &aux);
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
	return *this->manHilo;
}


/**
 * @brief Este método devolverá el identificador del hilo.
 * 
 * @return int Identificador del hilo
 */
int hilo_t::ObtenerIdentificador()
{
	return this->id;
}


/*
**********************************************************
********************** Clase mutex_t *********************
**********************************************************
*/

/**
 * @brief Construct a new mutex t::mutex t object
 * 
 */
mutex_t::mutex_t()
{
	this->manMutex = new pthread_mutex_t();
	this->attrMutex = new pthread_mutexattr_t();
	pthread_mutexattr_init(this->attrMutex);	
}

/**
 * @brief Destroy the mutex t::mutex t object
 * 
 */
mutex_t::~mutex_t()
{
    pthread_mutex_destroy(this->manMutex);
	delete this->manMutex;
	pthread_mutexattr_destroy(this->attrMutex);
	delete this->attrMutex;
}

/**
 * @brief Este método se encargará de inicializar el mutex usando los atributos de creación del mutex
 * 
 * @return int valor que devuelva la función pthread_mutex_init
 */
//Implementación del método Inicializar sin parámetros. 
int mutex_t::Inicializar()
{
	return pthread_mutex_init(this->manMutex, this->attrMutex);	
}

/**
 * @brief Este método se encargará de acceder al mutex asociado a la clase usando el manejador del mutex de la clase
 * 
 * @return int valor devuelto por dicha función pthread_mutex_lock
 */
int mutex_t::Lock()
{
	return pthread_mutex_lock (this->manMutex);
}

/**
 * @brief  Este método se encargará de liberar el mutex asociado a la clase usando el manejador del mutex de la clase
 * 
 * @return int valor devuelto por dicha función pthread_mutex_unlock
 */
int mutex_t::Unlock()
{
	return pthread_mutex_unlock(this->manMutex);
}

/**
 * @brief Este método se encargará devolver el manejador del mutex de la clase
 * 
 * @return pthread_mutex_t* manejador del mutex de la clase
 */
pthread_mutex_t* mutex_t::ObtenerManejador()
{
	return this->manMutex;
}


/*
**********************************************************
*************** Clase variable_condicion_t ***************
**********************************************************
*/


/**
 * @brief Construct a new variable_condicion_t object
 * 
 */
variable_condicion_t::variable_condicion_t()
{
	this->manCond = new pthread_cond_t();
	this->attrCond = new pthread_condattr_t();
	pthread_condattr_init(this->attrCond);
}

/**
 * @brief Destroy the variable condicion t::variable condicion t object
 * 
 */
variable_condicion_t::~variable_condicion_t()
{
	pthread_cond_destroy(this->manCond);
	pthread_condattr_destroy(this->attrCond);
	delete this->manCond;
	delete this->attrCond;
}

/**
 * @brief Este método se encargará de inicializar la variable de condición usando los atributos de creación la variable de condición

 * 
 * @return int valor que devuelva dicha función pthread_cond_init
 */
int variable_condicion_t::Inicializar()
{
	return pthread_cond_init(this->manCond, this->attrCond);
}

/**
 * @brief Este método se encargará de asociar el mutex recibido por parámetro a la clase
 *(usar el método AsociarManejadorMutex) así como de inicializar la variable de condición 
 *usando los atributos de creación la variable de condición
 * 
 * @param mutexCond Mutex de la clase
 * @return int valor que devuelva dicha función pthread_cond_init
 */
int variable_condicion_t::Inicializar(pthread_mutex_t* mutexCond)
{
	variable_condicion_t::AsociarManejadorMutex(mutexCond);
	return pthread_cond_init(this->manCond, this->attrCond);
}

/**
 * @brief Este método se encargará de asignar el parámetro de entrada al
 *atributo de la clase que va a almacenar el mutex asociado. No es necesario 
 *reservar memoria para dicho atributo ya que, aunque es un puntero, también lo es el
 *parámetro de entrada. Al ser ambas variables punteros, el mutex asociado y el parámetro de entrada acabarán apuntando a la misma dirección de memoria.
 * 
 * @param mutexCond Mutex a asociar a la clase
 */
void variable_condicion_t::AsociarManejadorMutex(pthread_mutex_t* mutexCond)
{
	this->mutexCond = mutexCond;
}

/**
 * @brief Este método se encargará de bloquear el hilo invocante en la variable de condición de la clase.
 * 
 * @return * int valor que devuelva dicha función pthread_cond_wait
 */
int variable_condicion_t::Wait()
{
	return pthread_cond_wait(this->manCond, this->mutexCond);
}
	
/**
 * @brief Este método se encargará de bloquear el hilo en la variable de condición de la clase
 *como máximo hasta el instante indicado por el parámetro de entrada
 * 
 * @param time tiempo a esperar
 * @return int valor que devuelva dicha función pthread_cond_timedwait
 */
int variable_condicion_t::TimedWait(timespec time)
{
	return pthread_cond_timedwait(this->manCond, this->mutexCond, &time);
}

/**
 * @brief Este método se encargará de liberar (al menos) un hilo bloqueado en la variable de condición de la clase.
 * 
 * @return int valor que devuelva dicha función pthread_cond_signal
 */
int variable_condicion_t::Signal()
{
    return pthread_cond_signal(this->manCond);
}

/**
 * @brief Este método se encargará de liberar todos los hilos bloqueados en la variable de condición de la clase.
 * 
 * @return int valor que devuelva dicha función pthread_cond_broadcast
 */
int variable_condicion_t::Broadcast()
{
    return pthread_cond_broadcast(this->manCond);
}