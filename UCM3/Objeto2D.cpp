#include "Objeto2D.h"

Objeto2D:: Objeto2D() { 	 
    matriz = new TAfin();
}

 
Objeto2D:: ~Objeto2D() {
    delete matriz;
}

GLfloat* Objeto2D:: dameMatrizAfin() {
	return matriz->dameMatrizModelado();
}

//To do (usando las correspondientes operaciones de TAfin)
void Objeto2D:: traslada(Vector3* punto) {
	matriz->traslada(punto->x, punto->y,0);
}

void Objeto2D:: escala(GLfloat fX,GLfloat fY) {
	matriz->escala(fX, fY,1);
}

void Objeto2D:: rota(GLfloat alfa) {
	matriz->rota(alfa,0, 0,1);
}

bool Objeto2D::estaDentro(Vector3 *punto){
	
	for(int i =0; i< numVertices ; i++){
		Vector3 *vectorAlPunto;
		Vector3 *puntoVector = new Vector3(0,0,0);
		vectorAlPunto = punto-*vertices[i];
		if( (*vectorAlPunto|*normales[i]) > 0 ){
			return false;
		}
	}
	return true;
}