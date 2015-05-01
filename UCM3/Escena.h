#pragma once
#include <Gl/glut.h>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

class Escena
{
public:
	int WIDTH, HEIGHT;

	virtual void dibujar() = 0;
	virtual void keyboard(unsigned char key, int mX, int mY) = 0;
	virtual void keyboardSP(int key, int mX, int mY) = 0;
	virtual void mouse(int button, int state, int x, int y) =0 ;
	virtual void reshape(int w, int h) = 0;
};

