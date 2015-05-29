#include "Selector.h"
#include <vector>
#define NW 0
#define NE 1
#define SE 2
#define SW 3

#pragma once
class QuadNodo
{
public:
	QuadNodo(int miX,int miY, int maX,int maY){ minX = miX; minY =miY; maxX = maX; maxY = maY; };
	QuadNodo(){};
	~QuadNodo(void){};
	
	virtual QuadNodo* inserta(Selector* p){  return NULL;};
	virtual Selector** buscar(Vector2* v){  return NULL; };
	bool contiene(Vector2* v);
	int minX,minY,maxX,maxY;
};

class QuadBranch : public QuadNodo
{
public:
	QuadNodo* nodos[4];
	
	QuadBranch(int miX,int miY, int maX,int maY);
	QuadNodo* inserta(Selector* p);
	Selector** buscar(Vector2* v);

	~QuadBranch(void);
};

class QuadLeaf : public QuadNodo
{
public:

	QuadLeaf(int miX,int miY, int maX,int maY);
	QuadNodo* inserta(Selector* p);
	Selector** buscar(Vector2* v);

	QuadLeaf(void);
	~QuadLeaf(void);

	int limite;
	int cantidad;
	Selector **Objetos;
};

class QuadTree
{
public:
	QuadTree(int minX,int minY, int maxX,int maxY);
	void inserta(Selector* p);
	Selector** buscar(Vector2* v);
	~QuadTree(void);

private:

	QuadNodo *raiz;
	int minX,minY,maxX,maxY;
};