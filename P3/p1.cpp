/**
 * @file p1.cpp
 * @author Alejandro Torrejon Harto (atorrjo@alumnos.unex.es)
 * @brief 
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "pila_acotada.h"
#include <stdio.h>

#define REPETICIONES 50
#define NUM_HILOS 5


void imprimir_lectura(int hilo, int elem){
	printf("El hilo %d ha leído el valor %d de la pila\n", hilo, elem);
}

void imprimir_escritura(int hilo, int elem){
	printf("El hilo %d ha añadido el valor %d a la pila\n", hilo, elem);
}

/*
Definir un tipo de datos DatosHilos_t que sea una estructura con dos campos:
- Identificador de hilo de puntero a hilo_t: este campo almacenará la dirección de memoria de la clase que almacena los datos del hilo para poder usarlos dentro de la función
- Pila acotada de tipo puntero a PilaAcotada: este campo servirá para que todos los hilos compartan la misma pila acotada (de ahí que sea un puntero)
Para definir un tipo se usa la palabra reservada typedef, mientras que para definir una estructura se usa la palabra reservada struct. Por tanto, para definir un
tipo estructura se deben incluir ambas palabras reservadas de la forma "typedef struct { campos de la estructura } NombreDelTipo;"
*/
typedef struct 
{
	hilo_t* Identificador;
	PilaAcotada* Pila;
}DatosHilos_t;


/**
 * @brief Función para hilo, añade un numero si la pila no esta llena
 * 
 * @param data DatosHilos_t, pila e hilo
 * @return void* 
 */
void * hilo_productor(void *data)
{
	//El parámetro es un dato de tipo DatosHilos_t
	DatosHilos_t productor=*((DatosHilos_t *)data);
	int valEsc;
	for (int i=0; i<REPETICIONES; i++) {
		valEsc = (productor.Identificador->ObtenerIdentificador()*i)+productor.Identificador->ObtenerIdentificador();
		productor.Pila->PilaAniadir(valEsc);
		imprimir_escritura(productor.Identificador->ObtenerIdentificador(), valEsc);
	}
	return nullptr;
}


/**
 * @brief Función para hilo, extrae un numero si la pila no esta vacía
 * 
 * @param data DatosHilos_t, pila e hilo
 * @return void* 
 */
void * hilo_consumidor(void *data)
{
	//Definir una variable de tipo DatosHilos_t
	DatosHilos_t consumidor=*((DatosHilos_t *)data);
    int valLec;
	for (int i=0; i<REPETICIONES; i++) {
		valLec = consumidor.Pila->PilaSacar();
		imprimir_lectura(consumidor.Identificador->ObtenerIdentificador(), valLec);
	}
	return nullptr;
}


/**
 * @brief Se arrancara NUM_HILOS de hilos productores, que añadirán a la pila y la misma cantidad de consumidores, que extraerán de esta
 * 
 * @return int 
 */
int main (void) {
	//Definir una variable PilaAcotada inicializándola a 20
	PilaAcotada pila(20);

	//Definir dos vectores de tipo DatosHilos_t y de tamaño NUM_HILOS para almacenar los datos de los productores y de los consumidores
	DatosHilos_t datosProductores[NUM_HILOS];
	DatosHilos_t datosConsumidores[NUM_HILOS];

	//Crear dos vectores de tipo hilo_t y de tamaño NUM_HILOS para almacenar los objetos para almacenar los manejadores de hilos de los productores y de los consumidores
	hilo_t hilosProductores[NUM_HILOS];
	hilo_t hilosConsumidores[NUM_HILOS];

	//Lanzar los NUM_HILOS productores y consumidores. Para lanzar cada hilo, hay que hacer los siguientes pasos:
	for (int i=0; i<NUM_HILOS; i++) {
		
		//1. Asignar al campo Hilo del productor/consumidor i-ésimo la dirección de memoria del valor i-ésimo del vector de manejadores de productores/consumidores según corresponda
		datosConsumidores[i].Pila = &pila;
		datosConsumidores[i].Identificador = &hilosConsumidores[i];
		datosProductores[i].Pila = &pila;
		datosProductores[i].Identificador = &hilosProductores[i];

		//2. Asignar al campo relativo a la pila acotada del productor/consumidor i-ésimo la dirección de memoria de la variable de tipo PilaAcotada definida al comienzo de la 
		//función (poner & delante de la variable para acceder a su dirección de memoria)
		//3. Asignar al manejador de hilo del productor/consumidor i-ésimo la función hilo_productor/hilo_consumidor y la dirección de memoria del dato i-ésimo del 
		//productor/consumidor
		hilosProductores[i].AsignarFuncionYDato(hilo_productor, &datosProductores[i]);
		hilosConsumidores[i].AsignarFuncionYDato(hilo_consumidor, &datosConsumidores[i]);
		
		//4. Lanzar el hilo productor/consumidor -iésimo
		hilosProductores[i].Lanzar();
		hilosConsumidores[i].Lanzar();

	}

	//Esperar a que terminen todos los productores y los consumidores
	for (int i=0; i<NUM_HILOS; i++) {
		hilosConsumidores[i].Join();
		hilosProductores[i].Join();
	}
	return 0;
}
