#include "Selector.h"


Selector::Selector(void)
{
	numNormales =0;
	numVertices =0;
	seleccionado = false;
}


Selector::~Selector(void)
{
}

bool Selector::estaDentro(Vector2 *punto){
	return false;
	//TODO
}

void Selector::calcularBaricentro(){

	Vector2 *a = vertices[0];
	Vector2 *b = vertices[1];
	Vector2 *c = vertices[2];
	baricentro = new Vector2((a->x+b->x+c->x)/3,(a->y+b->y+c->y)/3);
}


void Selector::dibuja(){

	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0,0.0,0.0);
	glPushMatrix();
		glMultMatrixf(matriz->dameMatrizModelado());
		glLineWidth(2.0);
	if(modo == design){
		glBegin(GL_LINE_LOOP);
	}else if(modo == select){
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_TRIANGLES);
	}
	for (int i=0; i< numVertices; i++) {
		glTexCoord2f(vertices[i % numVertices]->x/WIDTH, vertices[i % numVertices]->y/HEIGHT);
		glVertex2d(vertices[i % numVertices]->x,vertices[i % numVertices]->y);
	}
	glEnd();
	glPopMatrix();

	if(modo == select && seleccionado){
	
	glPushMatrix();
		glColor3f(1.0,0.0,0.0);
		glDisable(GL_TEXTURE_2D);
		glMultMatrixf(matriz->dameMatrizModelado());
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
		for (int i=0; i< numVertices; i++) {
			glVertex2d(vertices[i % numVertices]->x,vertices[i % numVertices]->y);
		}
		glEnd();
	glPopMatrix();

	}

	glPointSize(5.0);
	glBegin(GL_POINTS);
		glVertex2f(baricentro->x, baricentro->y);
	glEnd( );



}