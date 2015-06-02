#include "Objeto2D.h"
#include <Gl/glut.h>

enum MODO{ design, select, animate };

#pragma once
class Selector : public Objeto2D
{
public:
	Selector(void);
	Selector(int id, int width, double height);
	~Selector(void);
	void dibuja();
	void moverse();
	bool estaDentro(Vector2* punto);
	void calcularBaricentro();
	Selector* generarEnRango(int x, int y, int w, int h,int width, double height);


	void setTextura(int nv, Vector2** ve);
	Vector2 ** textura;
	Vector2 * aceleracion;
	Vector2 * baricentro;
	void setVertices(int nv, Vector2** ve);
	bool intercepta(Vector2* p1, Vector2* p2);

	void impacta(double width, double height);
	void step();
	MODO modo;

	int id;
	bool seleccionado;
	int WIDTH, HEIGHT;
};

