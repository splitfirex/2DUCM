
#ifndef ObjetoCompuesto_H_
#define ObjetoCompuesto_H_

#include "Objeto3D.h"

class ObjetoCompuesto: public ObjetoDibujable {
	protected:
		ObjetoDibujable** hijos;
		int numHijos;
	public:
		ObjetoCompuesto();
		~ObjetoCompuesto();
		void dibuja();
		void introduceObjeto(ObjetoDibujable* objeto);
};
#endif
