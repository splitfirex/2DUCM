
#ifndef Objeto2D_H_
#define Objeto2D_H_

#include "ObjetoDibujable.h"

enum MODO{ BOXING, MODO2, MODO3 };

class Objeto2D : public virtual ObjetoDibujable{
   public:	  	   
	    Objeto2D();    
		~Objeto2D();
		void traslada(Vector3* punto);
		void escala(GLfloat fX,GLfloat fY);
		void rota(GLfloat alfa);
		GLfloat* dameMatrizAfin();

		bool estaDentro(Vector3* punto, MODO modo );
   
   protected:
		int numVertices, numNormales;
		Vector3** vertices;
		Vector3** normales;
};

#endif
