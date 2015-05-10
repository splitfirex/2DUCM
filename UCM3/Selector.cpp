#include "Selector.h"


Selector::Selector(void)
{
	numNormales =0;
	numVertices =0;
}


Selector::~Selector(void)
{
}

void Selector::dibuja(){

	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0,0.0,0.0);
	glPushMatrix();
	glMultMatrixf(matriz->dameMatrizModelado());
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	for (int i=0; i< numVertices; i++) {
		glVertex2d(vertices[i % numVertices]->x,vertices[i % numVertices]->y);
	}
	glEnd();
	glPopMatrix();

}