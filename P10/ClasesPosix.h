//Incluir la librería de utilización de hilos posix
#include "Identificador.h"
#include "funciones_time.h"
#include <pthread.h>
#include <vector>
#include <iostream>


class mutex_t {
	private:
		pthread_mutex_t* manMutex;// Este atributo será el manejador del mutex asociado a la clase
		pthread_mutexattr_t* attrMutex;//Atributos del mutex
		

	public:
		mutex_t();
		~mutex_t();
		int Inicializar();
		int Lock();
		int Unlock();
		pthread_mutex_t* ObtenerManejador();
		/*
		************************************************************************************************
		**************************** Nuevos métodos para la Prática Posix 5 ****************************
		************************************************************************************************/
		//Definir el método AsignarProtocolo que retorne un entero y reciba un entero para indicar el protocolo de prioridades dinámicas
		int AsignarProtocolo(int protocolo);
		//Definir el método AsignarTecho que retorne un entero y reciba un entero para indicar el techo de prioridad del mutex
		int AsignarTecho(int  techo);
		//Definir el método AsignarProtocoloYTecho que retorne un entero y reciba un entero para indicar el protocolo de prioridades dinámicas y otro entero para indicar el techo de prioridad del mutex
		int AsignarProtocoloYTecho(int protocolo, int techo);
};

/*
**********************************************************
********************** Clase hilo_t **********************
**********************************************************
*/


//Definir la clase hilo_t
class hilo_t {
	//Parte privada
	private:
		int id; //Identificador del hilo único para cada uno de los hilos.
		pthread_t *manHilo; //Manejador qu almacenará el manejador del hilo que está asociado a la clase.
		pthread_attr_t * attrHilo; //Atributos del hilo 
		void *(*funcHilo)(void *); //Función asociada al hilo, dirección de memoria de la función que se usará para lanzar el hilo.
		void *parm; //Almacenará diercción de parámetro de la función asociada al hilo.
		//Definir cuatro variables enteras para almacenar el tiempo de ejecución, la prioridad y la política del hilo
		int ejecucion, prioridad, politica;
		//Definir dos variables de tipo struct timespec para almacenar el periodo de repetición y el instante crítico del hilo
		struct timespec repe, critico;
		/*
		************************************************************************************************
		*************************** Nuevos atributos para la Prática Posix 5 ***************************
		************************************************************************************************/
		//Definir un atributo de tipo vector de enteros (usar la clase vector) para guardar la lista de acciones que ejecutará la tarea periódica del hilo
		std::vector<int> acciones;
		//Definir un atributo de tipo vector de enteros (usar la clase vector) para guardar la lista de recursos que usará la tarea periódica del hilo
		std::vector<int> recursos;
		/*Definir un atributo de tipo vector de puntero a mutex_t (usar la clase vector) para guardar la lista de mutex de la aplicación (un mutex por cada recurso).
		Usamos punteros para que los mutex sean compartidos por todos los hilos*/
		std::vector<mutex_t*> mutexs;

	//Parte pública
	public:
		hilo_t();
		~hilo_t();
		int Lanzar();
		void AsignarFuncion(void *(*funcHilo)(void *));
		void AsignarDato(void* dato); 
		void AsignarFuncionYDato (void *(*funcHilo)(void *), void* dato);
		void* Join(); 
		pthread_t ObtenerManejador();
		int ObtenerIdentificador();
		/*Definir el método EstablecerAtributos que devolverá un valor entero y que recibirá los siguientes atributos (mantener el orden descrito): prioridad, política,
		herencia, periodo de repetición (vendrá dado en milisegundos, se transformará a struct timespec dentro del método), tiempo de ejecución de la tarea periódica del hilo
		y el instante de comienzo. Todos los parámetros son de tipo entero excepto el último, que es de tipo struct timespec*/
		int EstablecerAtributos(int prioridad, int politica, int herencia, int periodo, int ejecucion, struct timespec instanteComienzo);
		//Definir el método ObtenerPeriodo sin parámetros y que devuelva un struct timespec
		struct timespec ObtenerPeriodo();
		//Definir el método ObtenerInstanteDeComienzo sin parámetros y que devuelva un struct timespec
		struct timespec ObtenerInstanteDeComienzo();
		//Definir el método ObtenerTiempoEjecucion sin parámetros y que devuelva un entero
		int ObtenerTiempoEjecucion();
		//Definir el método ObtenerPrioridad sin parámetros y que devuelva un entero
		int ObtenerPrioridad();
		//Definir el método ObtenerPolitica sin parámetros y que devuelva un entero
		int ObtenerPolitica();
		/*
		************************************************************************************************
		**************************** Nuevos métodos para la Prática Posix 5 ****************************
		************************************************************************************************
		
		/*Definir el método EstablecerAtributos que devolverá un valor entero y que recibirá los siguientes atributos (mantener el orden descrito):
			- Prioridad, política, herencia, periodo de repetición (vendrá dado en milisegundos, se transformará a struct timespec dentro del método), tiempo de ejecución de la
				tarea periódica del hilo e identificador del hilo (todos de tipo entero)
			- Instante de comienzo (de tipo struct timespec)
			- Vector de acciones del hilo y vector de recursos del hilo (de tipo vector de enteros, usar la clase vector)
			- Vector de mutex de la aplicación (de tipo vector de punteros a mutex_t, usar la clase vector)*/
		int EstablecerAtributos(int prioridad, int politica, int herencia, int periodo,
		int ejecucion, struct timespec instanteComienzo, std::vector<int> acciones, std::vector<int> recursos, std::vector<mutex_t*> mutexs);

		//Definir el método ObtenerNumAcciones sin parámetros que retorne un valor entero que será el número de acciones del vector de acciones del hilo.
		int ObtenerNumAcciones();
		/*Definir el método ObtenerAccion con un parámetro entero que indicará la acción que se desea obtener y que retorne un valor entero que será la acción de la lista de
		acciones indicada por el parámetro de entrada*/
		int ObtenerAccion(int accion);
		/*Definir el método ObtenerRecurso con un parámetro entero que indicará el recurso que se desea obtener y que retorne un valor entero que será el recurso de la lista de
		recursos indicado por el parámetro de entrada*/
		int ObtenerRecurso(int recurso);
		/*Definir el método ObtenerMutex con un parámetro entero que indicará el mutex que se desea obtener y que retorne un puntero a mutex_t que será el mutex de la lista de
		mutex indicado por el parámetro de entrada*/
		mutex_t* ObtenerMutex(int mutex);
};


/*
**********************************************************
*************** Clase variable_condicion_t ***************
**********************************************************
*/
class variable_condicion_t {
	private:
		pthread_cond_t *manCond;// Este atributo será el manejador de la variable de condición asociada a la clase.
		pthread_condattr_t* attrCond;// Atributos de la variable de condición.
		pthread_mutex_t* mutexCond; //Mutex asociado a  la variable de condición.

	public:
		variable_condicion_t();
		~variable_condicion_t();
		int Inicializar();
		int Inicializar(pthread_mutex_t* mutexCond);
		void AsociarManejadorMutex(pthread_mutex_t* mutexCond);
		int Wait();
		int TimedWait(timespec time);
		int Signal();
		int Broadcast();
};