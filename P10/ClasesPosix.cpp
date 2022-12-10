
#include "ClasesPosix.h"


Identificador_t Identificador;

/*
**********************************************************
********************** Clase hilo_t **********************
**********************************************************
*/
//Los métodos implementados para esta clase en la Práctica Posix 0 hay que mantenerlos sin modificar

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


/*
***************************************************************************************************************
*********************** Implementación de los nuevos métodos para la prática de posix 4 ***********************
***************************************************************************************************************
*/

/*Implementación del método EstablecerAtributos. Este método se encargará de guardar los datos pasados como parámetros a sus atributos correspondientes (hay que transformar el
periodo, que se recibe en milisegundos, a struct timespec, ver funciones_time.h). Además, establecerá la herencia, la política y la prioridad del hilo*/
int hilo_t::EstablecerAtributos(int prioridad, int politica, int herencia, int periodo, int ejecucion, timespec instanteComienzo)
{
	//Guardar los parámetros recibidos en los atributos correspondientes, transformando el periodo de milisegundos a struct timespec (usar la función ms2timespec de funciones_time)
	this->repe = ms2timespec(periodo);
	this->prioridad = prioridad;
	this->politica = politica;
	this->critico = instanteComienzo;
	this->ejecucion = ejecucion;
	//Establecer la herencia recibida por parámetros en los atributos de creación del hilo de la clase (función pthread_attr_setinheritsched)
	pthread_attr_setinheritsched(this->attrHilo, herencia);
	//Establecer la política recibida por parámetros en los atributos de creación del hilo de la clase (función pthread_attr_setschedpolicy)
	pthread_attr_setschedpolicy(this->attrHilo, this->politica);
	//Definir una variable de tipo struct sched_param
	struct sched_param scheduler; 
	//Asignar la prioridad al campo sched_priority de la variable anterior
	scheduler.sched_priority = this->prioridad;
	//Asignar la variable anterior a los atributos de creación del hilo de la clase (función pthread_attr_setschedparam)
	pthread_attr_setschedparam(this->attrHilo, &scheduler);
//Fin EstablecerAtributos
	return 0;
}


//Implementación de la función ObtenerPeriodo. Esta función lo único que hace es devolver el periodo del hilo
struct timespec hilo_t::ObtenerPeriodo()
{
	return this->repe;
}

//Implementación de la función ObtenerInstanteDeComienzo. Esta función lo único que hace es devolver el instante de comienzo del hilo
struct timespec hilo_t::ObtenerInstanteDeComienzo()
{
	return this->critico;
}

//Implementación de la función ObtenerTiempoEjecucion. Esta función lo único que hace es devolver el tiempo de ejecución del hilo
int hilo_t::ObtenerTiempoEjecucion()
{
	return this->ejecucion;
}

//Implementación de la función ObtenerPrioridad. Esta función lo único que hace es devolver la prioridad del hilo
int hilo_t::ObtenerPrioridad()
{
	return this->prioridad;
}

//Implementación de la función ObtenerPolitica. Esta función lo único que hace es devolver la política del hilo
int hilo_t::ObtenerPolitica()
{
	return this->politica;
}
/*
***************************************************************************************************************
************************ Implementación de los nuevos métodos para la Prática Posix 5 *************************
***************************************************************************************************************
*/

/*Implementación del método EstablecerAtributos. Este método se encargará de guardar los datos pasados como parámetros a sus atributos correspondientes y de establecer la herencia,
la política y la prioridad del hilo. Para ello, se puede utilizar el método EstablecerAtributos definido en la Práctica Posix 4. Por otra parte, guardará la lista de acciones,
la lista de recursos y la lista de mutex pasados como últimos parámetros del método*/
int hilo_t::EstablecerAtributos(int prioridad, int politica, int herencia, int periodo, int ejecucion, struct timespec instanteComienzo, std::vector<int> acciones, std::vector<int> recursos, std::vector<mutex_t*> mutexs){
	/*Llamar al método EstablecerAtributos definido en la Práctica Posix 4 con la prioridad, la política, la herencia, el periodo de repetición, el tiempo de ejecución de la tarea
	periódica y el tiempo de comienzo del hilo*/
	int ret = this->EstablecerAtributos(prioridad, politica, herencia, periodo, ejecucion, instanteComienzo);
	/*Guardar el resto de los parámetros recibidos en los atributos correspondientes. La clase vector tiene definido el operador de asignación, por lo que se pueden hacer
	asignaciones de vectores sin ningún problema*/
	this->acciones = acciones;
	this->recursos = recursos;
	this->mutexs = mutexs;
//Fin del método EstablecerAtributos
	return ret;
}
	

//Implementar el método ObtenerNumAcciones. Esta función lo único que hace es devolver el tamaño del vector de la lista de acciones
int hilo_t::ObtenerNumAcciones(){
	return this->acciones.size();
}

//Implementar el método ObtenerAccion. Esta función lo único que hace es devolver el valor de la lista de acciones indicado por el parámetro de entrada
int hilo_t::ObtenerAccion(int accion){
	return this->acciones.at(accion);
}

//Implementar el método ObtenerRecurso. Esta función lo único que hace es devolver el valor de la lista de recursos indicado por el parámetro de entrada
int hilo_t::ObtenerRecurso(int recurso){
	return this->recursos.at(recurso);
}

/*Implementar el método ObtenerMutex. Esta función lo único que hace es devolver el valor de la lista de mutex indicado por el parámetro de entrada. En caso de que el parámetro
tenga un valor menor que cero o mayor o igual que el número de mutex, devolverá NULL*/
mutex_t* hilo_t::ObtenerMutex(int mutex){
	if (mutex<0 or mutex>=mutexs.size())
		return NULL;
	else
		return this->mutexs.at(mutex);
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
***************************************************************************************************************
************************ Implementación de los nuevos métodos para la Prática Posix 5 *************************
***************************************************************************************************************
*/

//Implementar el método AsignarProtocolo que establezca el protocolo del mutex al valor indicado por el parámetro recibido
int  mutex_t::AsignarProtocolo(int protocol){
	//Establecer el protocolo de los atributos de creación del mutex al valor indicado por el parámetro recibido (usar la función pthread_mutexattr_setprotocol)
	return pthread_mutexattr_setprotocol(this->attrMutex, protocol);
//Fin del método AsignarProtocolo
}

/*Implementar el método AsignarTecho que establezca el techo de prioridad del mutex al valor indicado por los
parámetros recibidos*/
int mutex_t::AsignarTecho(int techo){
	//Establecer el techo de prioridad de los atributos de creación del mutex usando el valor del techo de prioridad recibido por parámetro
	return pthread_mutexattr_setprioceiling(this->attrMutex, techo);
//Fin del método AsignarTecho
}

/*Implementar el método AsignarProtocoloYTecho con dos parámetros que establezca el protocolo y el techo de prioridad del mutex al valor indicado por los
parámetros recibidos*/
int mutex_t::AsignarProtocoloYTecho(int protocolo, int techo){
	//Llamar al método AsignarProtocolo pasándole el valor del protocolo recibido
	int ret = AsignarProtocolo(protocolo);
	//Llamar al método AsignarTecho pasándole el valor del techo de prioridad recibido
	return ret + AsignarTecho(techo);
//Fin del método AsignarProtocoloYTecho
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