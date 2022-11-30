#include <time.h>
#include <stdio.h>
struct timespec RestaTimeSpec(struct timespec src1, struct timespec src2); 	// retorna src1-src2
struct timespec SumaTimeSpec(struct timespec src1, struct timespec src2);  	// retorna src1+src2
void AcumTimeSpec(struct timespec &dst, struct timespec src);	// dst=dst+src
void ClearTimeSpec(struct timespec &dst);						// dst=0
void ImprimirTimeSpec(struct timespec dst);						// Imprime un timespect
struct timespec segundos2timespec(double src);							  	// Transforma un valor real a un timespect de la siguiente forma:
																			// - la parte entera representa segundos
																			// - la parte decimal representa nanosegundos
double timespec2segundos(struct timespec src);								// Transforma un valor timespect a un valor en segundos de la siguiente forma:
																			// - la parte entera representa segundos
																			// - la parte decimal representa nanosegundos
struct timespec ms2timespec(int src);										// Transforma un valor entero representando milisegundos a timespec
int timespec2ms(struct timespec src);										// Transforma un valor timespec a un entero representando milisegundos
