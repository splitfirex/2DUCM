
#include "TAfin.h"
#include <math.h>

TAfin:: TAfin() {
	m = new GLfloat[16];
	//To do: hacer que m sea la identidad
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);	
		glLoadIdentity();	
		glGetFloatv(GL_MODELVIEW_MATRIX, m); 
	glPopMatrix();

}

TAfin:: ~TAfin() {
	delete[] m;
}

GLfloat* TAfin::dameMatrizModelado() {
	return m;
}

void TAfin:: traslada(GLfloat X, GLfloat Y, GLfloat Z) {   
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);	
		glLoadMatrixf(m);	
		glTranslatef(X,Y,Z);
		glGetFloatv(GL_MODELVIEW_MATRIX, m); 
	glPopMatrix();
}

void TAfin:: escala(GLfloat fX, GLfloat fY, GLfloat fZ) {
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);	
		glLoadMatrixf(m);	
		glScalef(fX,fY,fZ);
		glGetFloatv(GL_MODELVIEW_MATRIX, m); 
	glPopMatrix();
}

void TAfin:: rota(GLfloat alfa, GLfloat fX, GLfloat fY, GLfloat fZ) {
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);	
		glLoadMatrixf(m);	
		glRotatef(alfa,fX,fY,fZ);
		glGetFloatv(GL_MODELVIEW_MATRIX, m); 
	glPopMatrix();
}


