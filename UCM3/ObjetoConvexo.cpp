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
	vertices = new Vector3*[lados];
	normales = new Vector3*[lados];

	//Inicializo los vertices 
	numVertices = n;
	double incremento = 360/(double)n;
	for(int i = 0 ; i < n ; i++){
		double theta= i*incremento;
		double c= cosf(aRadianes(theta));
		double s= sinf(aRadianes(theta));

		double x= c*tamano;
		double y=  s*tamano;
		Vector3* p= new Vector3(x, y, 0);
		vertices[i]= p;
	}
	// Inicializacion de las normales
	for(int i = 0 ; i < n ; i++){
		Vector3 *norm;
		norm = *(vertices[(i+1) % n])-*(vertices[i % n]);
		norm->y = norm->y*-1;
		norm = norm->normalizarPuntero();
		normales[i] = norm;
	}
}


ObjetoConvexo::~ObjetoConvexo(void)
{
	delete normales;
	delete vertices;
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