/**
 * @file pila_acotada.h
 * @author Alejandro Torrejon Harto (atorrjo@alumnos.unex.es)
 * @brief 
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <vector>
using namespace std;
#include <ClasesPosix.h>

class PilaAcotada
{
	public:
		PilaAcotada();
		PilaAcotada(int maxSize);
		void PilaAniadir(int add);
		int PilaSacar();
	private:
		std::vector<int> pila;
		int maxSize;
		mutex_t mutex;
		variable_condicion_t llena, vacia;

};
