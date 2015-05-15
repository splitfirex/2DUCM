#include "Objeto2D.h"
#include <Gl/glut.h>

enum MODO{ design, select, animate };

#pragma once
class Selector : public Objeto2D
{
public:
	Selector(void);
	~Selector(void);
	void dibuja();
	void moverse();
	bool estaDentro(Vector2* punto);
	void calcularBaricentro();

	void setTextura(int nv, Vector2** ve);
	Vector2 ** textura;
	Vector2 * aceleracion;
	Vector2 * baricentro;
	void setVertices(int nv, Vector2** ve);

	void impacta(double width, double height);

	void step();
	MODO modo;
	bool seleccionado;
	int WIDTH, HEIGHT;
};

