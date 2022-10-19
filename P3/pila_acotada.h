#include <vector>
using namespace std;
#include <ClasesPosix.h>

//Definir la clase PilaAcotada
class PilaAcotada
{
//Zona pública
	public:
		//Definir el constructor sin parámetros
		PilaAcotada();
		//Definir el constructor con un parámetro para indicar el tamaño máximo de la pila
		PilaAcotada(int maxSize);
		//Definir el método PilaAniadir con un parámetro de entrada de tipo entero
		void PilaAniadir(int add);
		//Definir el método PilaSacar sin parámetros y que retornará un valor entero
		int PilaSacar();
//Zona privada
	private:
		//Definir el vector pila de tipo entero (usar la case vector, ver el anexo 3 de la práctica)
		std::vector<int> pila;
		//Definir una variable entera para almacenar el tamaño máximo de la pila
		int maxSize;
		//Definir el mutex
		mutex_t mutex;
		//Definir las variables de condición para controlar que la pila esté llena o vacia
		variable_condicion_t llena, vacia;
//Fin de la clase PilaAcotada
};
