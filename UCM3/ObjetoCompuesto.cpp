 
#include "ObjetoCompuesto.h"

ObjetoCompuesto:: ObjetoCompuesto() {
	hijos = new ObjetoDibujable*[10];
	numHijos = 0;
}

ObjetoCompuesto:: ~ObjetoCompuesto() {
	for(int i =0; i < numHijos; i++) {     
		delete hijos[i];
    }  
}

void ObjetoCompuesto:: dibuja() {
	glPushMatrix();
		glMultMatrixf(matriz->dameMatrizModelado());
		for(int i =0; i< numHijos ; i ++){
			hijos[i]->dibuja();
		}
	glPopMatrix();
}

void ObjetoCompuesto:: introduceObjeto(ObjetoDibujable* objeto) {
	hijos[numHijos] = objeto;
	numHijos++;
}




