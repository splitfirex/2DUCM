#include "Escena.h"

#pragma once
class Practica3 : public virtual Escena
{
public:

	void dibujar();
	void keyboard(unsigned char key, int mX, int mY);
	void keyboardSP(int key, int mX, int mY);
	void reshape(int w, int h);
	void mouse(int button, int state, int x, int y);

	Practica3(void);
	~Practica3(void);
};

