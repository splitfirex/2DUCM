#pragma once
#include "GL\freeglut.h"

class Vector3
{
public:
	Vector3(GLdouble ax, GLdouble ay,  GLdouble az);
	Vector3(void);
	~Vector3(void);

	friend  Vector3 operator+ (Vector3 v, Vector3 u);
	friend  Vector3 operator- (Vector3 v, Vector3 u);
	friend  Vector3 operator* (Vector3 v, float r);
	friend  Vector3 operator& (Vector3 v, Vector3 u); // Producto cruz
	friend  GLfloat operator| (Vector3 v, Vector3 u); // Producto punto
	Vector3 normalizar();
	Vector3* normalizarPuntero();
	Vector3* clone();
	GLfloat longitud(Vector3 v);


	GLdouble x,y,z;
};

