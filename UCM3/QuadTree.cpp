#include "QuadTree.h"

// NODO

bool QuadNodo::contiene(Vector2* v){ 
	if(rec->x < v->getX() && rec->w >= v->getX()
		&& rec->y < v->getY() && rec->h >= v->getY()){
		return true;
	}
	return false;
};

// Metodos del arbol principal

QuadTree::QuadTree(int mix, int miy, int max, int may){
	raiz = new QuadLeaf(mix, miy,max, may);
	minX = mix, minY = miy, maxX= max, maxY = may;
}

void QuadTree::dibuja(){
	raiz->dibuja();
}

void QuadTree::inserta(Selector* p){
	raiz = raiz->inserta(p);
}

Selector** QuadTree::buscar(Vector2* p){
	return raiz->buscar(p);
}

// Metodos del nodo hoja

QuadLeaf::QuadLeaf(int mix, int miy, int max, int may) : QuadNodo(mix, miy,max, may){
	limite = 2;
	cantidad =0;
	Objetos = new Selector*[limite];

}

void QuadLeaf::dibuja(){
		glPushMatrix();
		double r = ((double) rand() / (RAND_MAX));
		double g = ((double) rand() / (RAND_MAX));
		double b = ((double) rand() / (RAND_MAX));

		glColor3f(r,g,b);
		glDisable(GL_TEXTURE_2D);
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
		
		glVertex2d(rec->x,rec->y);
		glVertex2d(rec->w,rec->y);
		glVertex2d(rec->w,rec->h);
		glVertex2d(rec->x,rec->h);

		glEnd();
		glPopMatrix();
}

QuadNodo* QuadLeaf::inserta(Selector* p){
	if(limite == cantidad){
		QuadBranch* rama = new QuadBranch(rec->x,rec->y,rec->w,rec->h);
		for(int i =0 ; i< limite ; i++){
			rama->inserta(Objetos[i]);
		}
		return rama->inserta(p);
	}else{
		Objetos[cantidad++] = p;
		return this;
	}

}

Selector** QuadLeaf::buscar(Vector2* p){
	Selector** resultadoTemp = new Selector*[cantidad];

	int n =0;
	for(int i =0; i< cantidad; i++){
		if(Objetos[i]->estaDentro(p)){
			resultadoTemp[n] = Objetos[i];
			n++;
		}
	}
	Selector** resultado = new Selector*[n];
	// se recorta el array de salida
	for(int i =0; i< n; i++){
		resultado[i] = resultadoTemp[i];
	}

	return resultado;
}

// Metodos de la rama

QuadBranch::QuadBranch(int mix, int miy, int max, int may) : QuadNodo(mix, miy, max, may){
	int wT = (max - mix);
	int hT = (may - miy);
	nodos[NW] = new QuadLeaf(mix, miy + hT/2, wT/2, may);
	nodos[NE] = new QuadLeaf(mix + wT/2, miy + hT/2,max, may);
	nodos[SE] = new QuadLeaf(mix + wT/2, miy, max, miy + hT/2);
	nodos[SW] = new QuadLeaf(mix, miy ,mix+ wT/2, miy +hT/2);
}

QuadNodo* QuadBranch::inserta(Selector* p){
	for(int i =0 ; i < 4 ; i++){
		for(int h = 0 ; h < p->numVertices ; h++){
			if(nodos[i]->contiene(p->vertices[h])){
				QuadNodo* n = nodos[i]->inserta(p);
				nodos[i] = n;
			} 
		}
	}
	return this;
}

Selector** QuadBranch::buscar(Vector2* p){
	Selector** resultados = new Selector*[4];
	int n = 0;

	for(int i = 0; i < 4 ; i++){
		
	}
	return resultados ;
}

void QuadBranch::dibuja(){
	nodos[NW]->dibuja();
	nodos[NE]->dibuja();
	nodos[SE]->dibuja();
	nodos[SW]->dibuja();
}