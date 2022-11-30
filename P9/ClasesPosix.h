//Incluir la librería de utilización de hilos posix
#include <pthread.h>

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
};

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