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
	Vector2 * getCentro();

	Vector2 ** textura;
	Vector2 * aceleracion;
	MODO modo;
	int WIDTH, HEIGHT;
};

