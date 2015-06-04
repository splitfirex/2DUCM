#include "Selector.h"
#include <iostream>
#include <vector>
#define NW 0
#define NE 1
#define SE 2
#define SW 3

#pragma once
class QuadTreeRec
{
public:
	QuadTreeRec(int x1,int y1, int x2,int y2);
	Vector2* proyeccion(Vector2* p);
	bool intercepta(Selector* v);
	Vector2** vertices;
	Vector2 normales[4];
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

