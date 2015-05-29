#include "QuadTree.h"

// NODO

bool QuadNodo::contiene(Vector2* v){ 
	if(minX <= v->getX() && maxX >= v->getX() &&
		minY <= v->getY() && maxY >= v->getY() ){
		return true;
	}
	return false;
};

// Metodos del arbol principal

QuadTree::QuadTree(int mix, int miy, int max, int may){
	raiz = new QuadLeaf(mix, miy,max, may);
	minX = mix, minY = miy, maxX= max, maxY = may;
}

void QuadTree::inserta(Selector* p){
	raiz->inserta(p);
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

QuadNodo* QuadLeaf::inserta(Selector* p){
	if(limite == cantidad){
		QuadBranch* rama = new QuadBranch(minX,minY,maxX,maxY);
		for(int i =0 ; i< limite ; i++){
			rama->inserta(Objetos[i]);
		}
		rama->inserta(p);
		return rama;
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
	int mitadX = max/2;
	int mitadY = may/2;
	nodos[NW] = new QuadLeaf(mix, miy,mitadX, mitadY);
	nodos[NE] = new QuadLeaf(mix + mitadX, max,mitadX, mitadY);
	nodos[SE] = new QuadLeaf(mix + mitadX, miy + mitadY, mitadX, mitadY);
	nodos[SW] = new QuadLeaf(mix, miy + mitadY,mitadX, mitadY);
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