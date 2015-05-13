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



	Vector2 ** textura;
	Vector2 * aceleracion;
	Vector2 * baricentro;

	MODO modo;
	bool seleccionado;
	int WIDTH, HEIGHT;
};

