
#include "Vector2.h"
#include <math.h>


//---------------------------------------------------------------------------

Vector2::Vector2(float x1, float y1){
	x=x1;
	y=y1;
}

Vector2* operator+(Vector2 v1, Vector2 v2){
	return new Vector2(v2.x +v1.x, v2.y+v1.y);
}

bool Vector2::sobrePone(Vector2* p){
	int valor =0;
	 if (this->x < p->x) {
        valor = p->x - this->y;
    } else {
        valor = this->x - p->y;
    }
	
	 return valor <0;
	
}

Vector2* Vector2::normalIzquierda(){
	Vector2 *result = new Vector2(-y,x);

	result->normalizar();

	return result;
}

Vector2* operator-(Vector2 v1, Vector2 v2){
	return new Vector2(v1.x -v2.x, v1.y-v2.y);
}


Vector2* operator*(double v1, Vector2 v2){
	return new Vector2(v2.x*v1, v2.y*v1);
}

//---------------------------------------------------------------------------
Vector2::~Vector2(){
}
//---------------------------------------------------------------------------
float Vector2::getX(){
	return x;
}
//---------------------------------------------------------------------------
float Vector2::getY(){
	return y;
}
//---------------------------------------------------------------------------
void Vector2::setX(float x1){
	x=x1;
}
//---------------------------------------------------------------------------
void Vector2::setY(float y1){
	y=y1;
}
//---------------------------------------------------------------------------
void Vector2::trasladar(Vector2* traslacion){
	x= x+ traslacion->getX();
	y= y+ traslacion->getY();
}
//---------------------------------------------------------------------------
float Vector2::dot(Vector2* vector2){
	return x*vector2->getX() + y*vector2->getY();
}
//---------------------------------------------------------------------------
void Vector2::escalar(float factor){
	x= x*factor;
	y= y*factor;
}
//---------------------------------------------------------------------------
void Vector2::normalizar(){
	float norma2= dot(this);
	if(norma2>0){
		x= x/sqrt(norma2);
		y= y/sqrt(norma2);
	}
}
//---------------------------------------------------------------------------
Vector2* Vector2::clonar(){
	return new Vector2(x,y);
}
//---------------------------------------------------------------------------
float Vector2::distanciaAPunto(Vector2* p){
	float incX= x-p->getX();
	float incY= y-p->getY();
	return sqrt(incX*incX + incY*incY);
}
//---------------------------------------------------------------------------
Vector2* Vector2::rotaP(Vector2* centroRot, double ang){
	float cx= centroRot->getX();
	float cy= centroRot->getY();
	float dx=(1.0-cos(ang))*cx + sin(ang)*cy;
	float dy=-sin(ang)*cx + (1.0-cos(ang))*cy;
	float x1= x*cos(ang)-y*sin(ang)+dx;
	float y1= x*sin(ang)+y*cos(ang)+dy;
	return new Vector2(x1,y1);
}
//---------------------------------------------------------------------------
Vector2* Vector2::rotaV(double ang){
	float x1= x*cos(ang)-y*sin(ang);
	float y1= x*sin(ang)+y*cos(ang);
	return new Vector2(x1,y1);
}
//---------------------------------------------------------------------------
float Vector2::longitud(){
	return sqrt(x*x+y*y);
}
//---------------------------------------------------------------------------



