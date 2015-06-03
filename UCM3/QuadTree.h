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
	QuadTreeRec(int x1,int y1, int x2,int y2){ 
		x = x1; y =y1; w = x2; h = y2;
		numVertices =4;
		vertices = new Vector2*[4];
		normales = new Vector2*[4];
		Vector2* v1 = new Vector2(x,y);
		Vector2* v2 = new Vector2(x,h);
		Vector2* v3 = new Vector2(w,h);
		Vector2* v4 = new Vector2(w,y);
		normales[0] = ((*v2)-(*v1))->normalIzquierda();
		normales[1] = ((*v3)-(*v2))->normalIzquierda();
		normales[2] = ((*v4)-(*v3))->normalIzquierda();
		normales[3] = ((*v1)-(*v4))->normalIzquierda();
		vertices[0] = v1;
		vertices[1] = v2;
		vertices[2] = v3;
		vertices[3] = v4;
	};
	void dibuja();

	Vector2* proyeccion(Vector2* p){

		double dotProduct = p->dot(this->vertices[0]);
		double min = dotProduct;
		double max = dotProduct;
		for (int i = 0; i < this->numVertices; i++) {
			dotProduct = this->vertices[i]->dot(p);
			if (dotProduct < min) {
				min = dotProduct;
			} else {
				if (dotProduct> max) {
					max = dotProduct;
				}
			}
		}

		Vector2* proj = new Vector2(min,max);
		return proj;
	}


	bool intercepta(Selector* v){
		// compruebo si algun vertice del triangulo se encuentra dentro del cuadrado
		/*for(int i=0; i < 3 ; i++){
		if(x <= v->vertices[i]->getX() && w >= v->vertices[i]->getX()
		&& y <= v->vertices[i]->getY() && h >= v->vertices[i]->getY()){
		return true;
		}
		}*/
		//return false;

		// comparo triangulo vs cuadrado
		for (int i = 0; i < v->numVertices; i ++)
		{
			// projecting both shapes onto the axis
			Vector2* Proj1 = v->proyeccion(v->normales[i]);
			Vector2* Proj2 = this->proyeccion(v->normales[i]);
			// if the overlap will be returned false otherwise continue the loop
			//std::cout << Proj1->getX() << "|" << Proj1->getY() << " : " << Proj2->getX()  << "|" << Proj2->getY()  << '\n';
			if (!Proj1->sobrePone(Proj2))
				return false;
		}

		// comparo cuadrado vs triangulo
		for (int i = 0; i < 4; i ++)
		{
			// projecting both shapes onto the axis
			Vector2* Proj1 = v->proyeccion(this->normales[i]);
			Vector2* Proj2 = this->proyeccion(this->normales[i]);
			// if the overlap will be returned false otherwise continue the loop
			//std::cout << Proj1->getX() << "|" << Proj1->getY() << " : " << Proj2->getX()  << "|" << Proj2->getY()  << '\n';
			if (!Proj1->sobrePone(Proj2))
				return false;
		}
		return true;
	}
	int numVertices;
	Vector2 ** vertices;
	Vector2 ** normales;
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

