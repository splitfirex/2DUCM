#include "Textura.h"


Textura::Textura(void)
{
}


Textura::~Textura(void)
{
}


void Textura::dibuja(){

	glPushMatrix();
	glBegin(GL_TRIANGLE_FAN);

	glTexCoord2f(0, 0);
	glVertex2f(vertices[0]->x, vertices[0]->y);

	glTexCoord2f(1, 0);
	glVertex2f(vertices[1]->x, vertices[1]->y);

	glTexCoord2f(1, 1);
	glVertex2f(vertices[2]->x, vertices[2]->y);

	glTexCoord2f(0, 1.0);
	glVertex2f(vertices[3]->x, vertices[3]->y);

	glEnd();
	glPopMatrix();
}