#include "ObjetoConvexo.h"
#include "Math.h"


#define PI 3.14159265359

static double aRadianes(double angulo){
	return angulo*(PI/180);
}

ObjetoConvexo::ObjetoConvexo(int n, double l)
{
	lados=n;
	tamano = l;
	vertices = new Vector2*[lados];

	//Inicializo los vertices y las normales
	numVertices = n;
	for(int i = 0 ; i < n ; i++){
		double theta= i*360/(double)n;
		double c= cosf(aRadianes(theta));
		double s= sinf(aRadianes(theta));

		double x= c*tamano + s*tamano;
		double y= -s*tamano + c*tamano;
		Vector2* p= new Vector2(x, y);
		vertices[i]= p;
	}
}


ObjetoConvexo::~ObjetoConvexo(void)
{
}

void ObjetoConvexo::dibuja(){

	glPushMatrix();
	glMultMatrixf(matriz->dameMatrizModelado());
	glLineWidth(2.0);
	glBegin(GL_TRIANGLE_FAN);
	for (int i=0; i<= numVertices; i++) {
		glVertex2d(vertices[i % numVertices]->x,vertices[i % numVertices]->y);
	}
	glEnd();
	glPopMatrix();

}