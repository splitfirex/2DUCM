#include "Objeto2D.h"

Objeto2D:: Objeto2D() { 	 
    matriz = new TAfin();
	numVertices = 0;
	numNormales = 0;
}

 
Objeto2D:: ~Objeto2D() {
    delete matriz;
}

GLfloat* Objeto2D:: dameMatrizAfin() {
	return matriz->dameMatrizModelado();
}

//To do (usando las correspondientes operaciones de TAfin)
void Objeto2D:: traslada(Vector2* punto) {
	matriz->traslada(punto->x, punto->y,0);
}

void Objeto2D:: escala(GLfloat fX,GLfloat fY) {
	matriz->escala(fX, fY,1);
}

void Objeto2D:: rota(GLfloat alfa) {
	matriz->rota(alfa,0, 0,1);
}

void Objeto2D:: setVertices(int nv, Vector2** ve) {
	numVertices = nv;
	vertices = new Vector2*[nv];
	for(int i=0; i< nv; i++){
		vertices[i] = ve[i]->clonar();
	}
}
