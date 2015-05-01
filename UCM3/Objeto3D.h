
#ifndef Objeto3D_H_
#define Objeto3D_H_

#include "ObjetoDibujable.h"
  
class Objeto3D : public virtual ObjetoDibujable{
   public:	  	   
	    Objeto3D();    
		~Objeto3D();
		void traslada(Vector3* punto);
		void escala(GLfloat fX,GLfloat fY,GLfloat fZ);
		void rota(GLfloat alfa,GLfloat fX,GLfloat fY,GLfloat fZ);
		GLfloat* dameMatrizAfin();
};

#endif
