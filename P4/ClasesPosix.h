//Incluir la librería de utilización de hilos posix
#include <pthread.h>

/*
**********************************************************
********************** Clase hilo_t **********************
**********************************************************
*/
class hilo_t 
{
	private:
		int id; //Identificador del hilo único para cada uno de los hilos.
		pthread_t *manHilo; //Manejador qu almacenará el manejador del hilo que está asociado a la clase.
		pthread_attr_t * attrHilo; //Atributos del hilo 
		void *(*funcHilo)(void *); //Función asociada al hilo, dirección de memoria de la función que se usará para lanzar el hilo.
		void *parm; //Almacenará diercción de parámetro de la función asociada al hilo.

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
};

/*
**********************************************************
********************** Clase mutex_t *********************
**********************************************************
*/
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