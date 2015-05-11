
#ifndef Objeto2D_H_
#define Objeto2D_H_

#include "ObjetoDibujable.h"

class Objeto2D : public virtual ObjetoDibujable{
   public:	  	   
	    Objeto2D();    
		~Objeto2D();
		void traslada(Vector2* punto);
		void escala(GLfloat fX,GLfloat fY);
		void rota(GLfloat alfa);
		GLfloat* dameMatrizAfin();
		void setVertices(int numVertices, Vector2**);
  
   protected:
		int numVertices, numNormales;
		Vector2** vertices;
		Vector2** normales;
};

#endif
