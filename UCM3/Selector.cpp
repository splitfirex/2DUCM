#include "Selector.h"
#include "stdlib.h"



double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

Selector::Selector(void)
{
	modo = design;
	numNormales =0;
	numVertices =0;
	seleccionado = false;
}

Selector::Selector(int ids, int width, double height){
	modo = design;
	id = ids;
	numVertices =0;
	seleccionado = false;
	WIDTH = width;
	HEIGHT = height;
}


void Selector:: setVertices(int nv, Vector2** ve) {
	Objeto2D::setVertices(nv,ve);
	numVertices = nv;
	if(numVertices == 3){
		textura = new Vector2*[nv];
		for(int i =0 ; i < nv; i++){
			textura[i] = vertices[i]->clonar();
			normales[i] = ((*vertices[i])-(*vertices[(i+1) % numVertices]))->normalIzquierda();
		}

		calcularBaricentro();

		double dd = rand() % 1;
		aceleracion = new Vector2(fRand(-1,1),fRand(-1,1));
		aceleracion->normalizar();
	}
}

Vector2* Selector::proyeccion(Vector2* p){

	 // To project a point on an axis use the dot product
	double dotProduct = p->dot(this->vertices[0]);
    double min = dotProduct;
    double max = dotProduct;
	for (int i = 0; i < this->numVertices; i++) {
		dotProduct = this->vertices[i]->dot(p);
        if (dotProduct < min) {
            min = dotProduct;
        } else {
            if (dotProduct> max) {
                max = dotProduct;
            }
        }
    }

	Vector2* proj = new Vector2(min,max);
	return proj;

	//Vector2* pNormalizado = p->clonar();
	//pNormalizado->normalizar();

	//double min = pNormalizado->dot(normales[0]);
	//double max = min;
	//// looping through the vertices and doing the dot product
	//for (int i = 1; i < numVertices; i++)
	//{
	//	double p = pNormalizado->dot(vertices[i]);
	//	if (p < min)
	//		min = p;
	//	else if (p > max)
	//		max = p;
	//}
	//// creating the vector that will be then returned
	//Vector2* proj = new Vector2(min,max);
	//return proj;
}

void Selector::impacta(double width, double height){
	Vector2 *normal = new Vector2(0,0);
	bool impacto = false;

	if(baricentro->x <= 0 ){
		normal = new Vector2(1,0);
		impacto= true;
	}

	if(baricentro->x >= width ){
		normal = new Vector2(-1,0);
		impacto= true;
	}

	if(baricentro->y <= 0 ){
		normal = new Vector2(0,1);
		impacto= true;
	}

	if(baricentro->y >= height ){
		normal = new Vector2(0,-1);
		impacto= true;
	}

	// Valido por la joda el impacto en los vertices
	//if(!impacto){
	//	for(int i =0 ; i< numVertices ; i++){
	//		Vector2 *vertice = vertices[i];

	//		if(vertice->x <= 0 ){
	//			normal = new Vector2(1,0);
	//			impacto= true;
	//		}

	//		if(vertice->x >= width ){
	//			normal = new Vector2(-1,0);
	//			impacto= true;
	//		}

	//		if(vertice->y <= 0 ){
	//			normal = new Vector2(0,1);
	//			impacto= true;
	//		}

	//		if(vertice->y >= height ){
	//			normal = new Vector2(0,-1);
	//			impacto= true;
	//		}

	//	}

	//}


	if(impacto){
		double a = aceleracion->dot(normal)/ normal->dot(normal);
		normal->escalar(2*a);
		aceleracion = *aceleracion-*normal;
	}

}

Selector::~Selector(void)
{
}

void Selector::step(){
	if(vertices){
		impacta(WIDTH,HEIGHT);
		baricentro = *baricentro+*aceleracion;
		for (int i=0; i< numVertices; i++) {
			vertices[i] = *vertices[i]+*aceleracion;
		}
	}
}

bool Selector::estaDentro(Vector2 *punto){
	if(vertices){
		Vector2 *ca = *vertices[1] - *vertices[0];
		Vector2 *cb = *vertices[2] - *vertices[0];
		Vector2 *cp = *punto - *vertices[0];

		double a = (cp->dot(cb->normalIzquierda()))/(ca->dot(cb->normalIzquierda())); 
		double b = (cp->dot(ca->normalIzquierda()))/(cb->dot(ca->normalIzquierda())); 

		return a >= 0 && b >= 0 && a + b <= 1 ;
	}
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
	}else if(modo == animate){
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_TRIANGLES);
	}
	for (int i=0; i< numVertices; i++) {
		if(textura){
			glTexCoord2f(textura[i % numVertices]->x/WIDTH, textura[i % numVertices]->y/HEIGHT);
		}
		glVertex2d(vertices[i % numVertices]->x,vertices[i % numVertices]->y);
	}
	glEnd();
	glPopMatrix();

	if((modo == select || modo== animate) && seleccionado){

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

	//glPointSize(5.0);
	//glBegin(GL_POINTS);
	//glVertex2f(baricentro->x, baricentro->y);
	//glEnd( );



}


Selector* Selector::generarEnRango(int x, int y, int w, int h,int width, double height){
	Selector *result = new Selector(0, width,height);
	Vector2 **listaVertices =  new Vector2*[3];

	for(int i=0; i< 3 ; i++){
		int nx = rand()%(w-x)+x;
		int ny =rand()%(h-y)+y;
		listaVertices[i] = new Vector2(nx,ny);
	}
	result->setVertices(3,listaVertices);
	return result;
}