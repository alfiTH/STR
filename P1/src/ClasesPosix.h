//Incluir la librería de utilización de hilos posix
#include <pthread.h>


/*
**********************************************************
********************** Clase hilo_t **********************
**********************************************************
*/

//Definir la clase hilo_t
class hilo_t 
{
	//Parte privada
	private:
		int id; //Identificador del hilo único para cada uno de los hilos.
		pthread_t *manHilo; //Manejador qu almacenará el manejador del hilo que está asociado a la clase.
		pthread_attr_t * attrHilo; //Atributos del hilo 
		void *(*funcHilo)(void *); //Función asociada al hilo, dirección de memoria de la función que se usará para lanzar el hilo.
		void *parm; //Almacenará diercción de parámetro de la función asociada al hilo.

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
};
