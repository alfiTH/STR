#include <ClasesPosix.h>

//Definir la clase Barrera
class Barrera
{
	public:
		Barrera();
		Barrera(int numHilos);
		void Sincronizar();
		void Resetear();
		void Resetear(int numHilos);

	private:
		int numHilos;
		int hilosBlock;
		mutex_t mutex;
		variable_condicion_t cond;
};
