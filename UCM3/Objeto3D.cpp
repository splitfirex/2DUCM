#include "Objeto3D.h"

Objeto3D:: Objeto3D() { 	 
    matriz = new TAfin();
}

 
Objeto3D:: ~Objeto3D() {
    delete matriz;
}

GLfloat* Objeto3D:: dameMatrizAfin() {
	return matriz->dameMatrizModelado();
}

//To do (usando las correspondientes operaciones de TAfin)
void Objeto3D:: traslada(Vector3* punto) {
	matriz->traslada(punto->x, punto->y,punto->z);
}

void Objeto3D:: escala(GLfloat fX,GLfloat fY,GLfloat fZ) {
	matriz->escala(fX, fY,fZ);
}

void Objeto3D:: rota(GLfloat alfa,GLfloat fX,GLfloat fY,GLfloat fZ) {
	matriz->rota(alfa,fX, fY,fZ);
}

