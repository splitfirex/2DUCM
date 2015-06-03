#include "Selector.h"
#include <vector>
#define NW 0
#define NE 1
#define SE 2
#define SW 3

#pragma once
class QuadTreeRec
{
public:
	QuadTreeRec(int x1,int y1, int x2,int y2){ x = x1; y =y1; w = x2; h = y2; };
	void dibuja();
	bool intercepta(Selector* v){
		// compruebo si algun vertice del triangulo se encuentra dentro del cuadrado
		for(int i=0; i < 3 ; i++){
			if(x <= v->vertices[i]->getX() && w >= v->vertices[i]->getX()
				&& y <= v->vertices[i]->getY() && h >= v->vertices[i]->getY()){
					return true;
			}
		}

		// compruebo intercepcion de los vertices del triangulo con el cuadrado
		if( v->intercepta(new Vector2(x,y), new Vector2(w,y))
			|| v->intercepta(new Vector2(w,y), new Vector2(w,h))
			|| v->intercepta(new Vector2(w,h), new Vector2(x,h))
			|| v->intercepta(new Vector2(x,h), new Vector2(x,y))){
				return true;
		}


		return false;
	}
	int x,y,w,h;
};

class QuadNodo
{
public:
	QuadNodo(int miX,int miY, int maX,int maY){ rec = new QuadTreeRec(miX,miY,maX,maY); };
	QuadNodo(){};
	~QuadNodo(void){};

	virtual QuadNodo* inserta(Selector* p) =0;
	virtual std::vector<Selector*> buscar(Vector2* v) =0;
	virtual void dibuja() =0;
	bool contiene(Vector2* v);

	QuadTreeRec* rec;

};

class QuadBranch : public QuadNodo
{
public:
	QuadNodo* nodos[4];

	QuadBranch(int miX,int miY, int maX,int maY);
	QuadNodo* inserta(Selector* p);
	std::vector<Selector*> buscar(Vector2* v);
	void dibuja();

	~QuadBranch(void);
};

class QuadLeaf : public QuadNodo
{
public:

	QuadLeaf(int miX,int miY, int maX,int maY);
	QuadNodo* inserta(Selector* p);
	std::vector<Selector*> buscar(Vector2* v);
	void dibuja();
	QuadNodo* inserta(std::vector<Selector*>* p);

	QuadLeaf(void);
	~QuadLeaf(void);

	int limite;
	int cantidad;
	std::vector<Selector*> Objetos;
};

class QuadTree
{
public:
	QuadTree(int minX,int minY, int maxX,int maxY, std::vector<Selector*> lista);
	void inserta(Selector* p);
	std::vector<Selector*> buscar(Vector2* v);
	~QuadTree(void);
	void dibuja();
	QuadNodo* topDownConstructor(std::vector<Selector*> *lista, int x, int y, int w, int h, int prof, int profmax);

private:

	QuadNodo *raiz;
	int minX,minY,maxX,maxY;
};

