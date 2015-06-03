#include "QuadTree.h"

// NODO

bool QuadNodo::contiene(Vector2* v){ 
	if(rec->x <= v->getX() && rec->w >= v->getX()
		&& rec->y <= v->getY() && rec->h >= v->getY()){
			return true;
	}
	return false;
};



QuadNodo* QuadTree::topDownConstructor(std::vector<Selector*>* lista, int x, int y, int w, int h, int prof, int maxprof){

	if(lista->size() < 3 || prof == maxprof){
		QuadLeaf* nodo = new QuadLeaf(x, y, w, h);
		nodo->inserta(lista);
		return nodo;
	}else if(lista->size() == 0){
		QuadLeaf* nodo = new QuadLeaf(x, y, w, h);
		return nodo;
	}
	else{
		int wT = (w - x);
		int hT = (h - y);
		std::vector<Selector*>* nwList = new std::vector<Selector*>();
		std::vector<Selector*>* neList = new std::vector<Selector*>();
		std::vector<Selector*>* seList = new std::vector<Selector*>();
		std::vector<Selector*>* swList = new std::vector<Selector*>();

		for(std::vector<Selector*>::iterator it = lista->begin(); it != lista->end(); ++it) {
			if(!(*it)->vertices || (*it)->numVertices !=3){ continue; } 
			QuadTreeRec* recNW  = new QuadTreeRec(x, (y + hT/2)+1, x + wT/2, h);
			QuadTreeRec* recNE  = new QuadTreeRec((x + wT/2)+1, y + hT/2,w, h);
			QuadTreeRec* recSE  = new QuadTreeRec(x + wT/2, y, w, (y + hT/2) -1);
			QuadTreeRec* recSW  = new QuadTreeRec(x, y ,(x+ wT/2)-1, y +hT/2);
			if(recNW->intercepta(*it)) nwList->push_back(*it);
			if(recNE->intercepta(*it)) neList->push_back(*it);
			if(recSW->intercepta(*it)) swList->push_back(*it);
			if(recSE->intercepta(*it)) seList->push_back(*it);
		}

		QuadNodo* nwQuadNode= topDownConstructor(nwList,x, (y + hT/2)+1, x + wT/2, h, prof+1, maxprof);
		QuadNodo* neQuadNode= topDownConstructor(neList,(x + wT/2)+1, y + hT/2,w, h, prof +1, maxprof);
		QuadNodo* seQuadNode= topDownConstructor(seList,x + wT/2, y, w, (y + hT/2) -1, prof +1, maxprof);
		QuadNodo* swQuadNode= topDownConstructor(swList,x, y ,(x+ wT/2)-1, y +hT/2,  prof +1, maxprof);

		QuadBranch* qb= new QuadBranch(x, y, w, h);
		qb->nodos[NW] = nwQuadNode;
		qb->nodos[NE] = neQuadNode;
		qb->nodos[SE] = seQuadNode;
		qb->nodos[SW] = swQuadNode;

		return qb;
	}

}

// Metodos del arbol principal

QuadTree::QuadTree(int mix, int miy, int max, int may, std::vector<Selector*> lista){
	//std::vector<Selector*>* listaNueva = new std::vector<Selector*>();
	//for(std::vector<Selector*>::iterator it = lista.begin(); it != lista.end(); ++it) {
	//	listaNueva->push_back(*(it));
//	}

	raiz = topDownConstructor(&lista,mix,miy,max,may,0,7);//new QuadLeaf(mix, miy,max, may);
	minX = mix, minY = miy, maxX= max, maxY = may;
}

void QuadTree::dibuja(){
	raiz->dibuja();
}

void QuadTree::inserta(Selector* p){
	raiz = raiz->inserta(p);
}

std::vector<Selector*> QuadTree::buscar(Vector2* p){
	return raiz->buscar(p);
}

// Metodos del nodo hoja

QuadLeaf::QuadLeaf(int mix, int miy, int max, int may) : QuadNodo(mix, miy,max, may){
	limite = 1;
	cantidad =0;
}

void QuadLeaf::dibuja(){
	glPushMatrix();
	double r = ((double) rand() / (RAND_MAX));
	double g = ((double) rand() / (RAND_MAX));
	double b = ((double) rand() / (RAND_MAX));

	glColor3f(r,g,b);
	glDisable(GL_TEXTURE_2D);
	glLineWidth(1.0);
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
		Objetos.push_back(p);
		cantidad++;
		return this;
	}

}

QuadNodo* QuadLeaf::inserta(std::vector<Selector*>* p){
	cantidad = p->size();
	Objetos = *p;
	return this;
}


std::vector<Selector*> QuadLeaf::buscar(Vector2* p){
	std::vector<Selector*> resultado;
	int n =0;
	for(int i =0; i< cantidad; i++){
		if(Objetos[i]->estaDentro(p)){
			resultado.push_back(Objetos[i]);
		}
	}
	return resultado;
}

// Metodos de la rama

QuadBranch::QuadBranch(int mix, int miy, int max, int may) : QuadNodo(mix, miy, max, may){
	int wT = (max - mix);
	int hT = (may - miy);
	nodos[NW] = new QuadLeaf(mix, (miy + hT/2)+1, mix + wT/2, may);
	nodos[NE] = new QuadLeaf((mix + wT/2)+1, miy + hT/2,max, may);
	nodos[SE] = new QuadLeaf(mix + wT/2, miy, max, (miy + hT/2) -1);
	nodos[SW] = new QuadLeaf(mix, miy ,(mix+ wT/2)-1, miy +hT/2);
}

QuadNodo* QuadBranch::inserta(Selector* p){
	for(int i =0 ; i < 4 ; i++){
		if(nodos[i]->rec->intercepta(p)
			|| p->intercepta(new Vector2(nodos[i]->rec->x,nodos[i]->rec->y), new Vector2(nodos[i]->rec->w,nodos[i]->rec->y))
			|| p->intercepta(new Vector2(nodos[i]->rec->w,nodos[i]->rec->y), new Vector2(nodos[i]->rec->w,nodos[i]->rec->h))
			|| p->intercepta(new Vector2(nodos[i]->rec->w,nodos[i]->rec->h), new Vector2(nodos[i]->rec->x,nodos[i]->rec->h))
			|| p->intercepta(new Vector2(nodos[i]->rec->x,nodos[i]->rec->h), new Vector2(nodos[i]->rec->x,nodos[i]->rec->y))
			){
				QuadNodo* n = nodos[i]->inserta(p);
				nodos[i] = n;
		}
	}
	return this;
}

std::vector<Selector*> QuadBranch::buscar(Vector2* p){
	std::vector<Selector*> resultados;
	int n = 0;

	for(int i = 0; i < 4 ; i++){
		if(nodos[i]->contiene(p)){
			std::vector<Selector*> vectorContenido = nodos[i]->buscar(p);
			resultados.insert(resultados.end(), vectorContenido.begin(), vectorContenido.end());
		}
	}
	return resultados;
}

void QuadBranch::dibuja(){
	nodos[NW]->dibuja();
	nodos[NE]->dibuja();
	nodos[SE]->dibuja();
	nodos[SW]->dibuja();
}