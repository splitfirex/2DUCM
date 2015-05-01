#include "Vector3.h"
#include <math.h>
#define NULL_VECTOR Vector3(0.0f,0.0f,0.0f)

Vector3::Vector3(GLdouble ax, GLdouble ay,  GLdouble az)
{
	x =ax; y=ay;z=az;
}

Vector3::Vector3(){
}

Vector3::~Vector3(void)
{
}

Vector3* Vector3::clone(){
	Vector3 *res;
	res = new Vector3();
	res->x = x;
	res->y = y;
	res->z = z;
	return res;
}

Vector3 Vector3::normalizar()
{
	Vector3 res;
	float l = longitud(*this);
	if (l == 0.0f) return NULL_VECTOR;
	res.x = x / l;
	res.y = y / l;
	res.z = z / l;
	return res;
}

Vector3* Vector3::normalizarPuntero()
{
	Vector3 *res ;
	res = new Vector3();
	float l = longitud(*this);
	if (l == 0.0f) return new Vector3(0,0,0);
	res->x = x / l;
	res->y = y / l;
	res->z = z / l;
	return res;
}

Vector3 operator+ (Vector3 v, Vector3 u)
{
	Vector3 res;
	res.x = v.x+u.x;
	res.y = v.y+u.y;
	res.z = v.z+u.z;
	return res;
}
Vector3 operator- (Vector3 v, Vector3 u)
{
	Vector3 res;
	res.x = v.x-u.x;
	res.y = v.y-u.y;
	res.z = v.z-u.z;
	return res;
}


Vector3 operator* (Vector3 v, float r)
{
	Vector3 res;
	res.x = v.x*r;
	res.y = v.y*r;
	res.z = v.z*r;
	return res;
}

Vector3 operator&(Vector3 u, Vector3 v)
{
	Vector3 resVector;
	resVector.x = u.y*v.z - u.z*v.y;
	resVector.y = u.z*v.x - u.x*v.z;
	resVector.z = u.x*v.y - u.y*v.x;

	return resVector;
}
GLfloat operator|(Vector3 v, Vector3 u)	//dot product
{
	return v.x*u.x+v.y*u.y+v.z*u.z;
}

GLfloat Vector3::longitud(Vector3 v1){
	return sqrt(v1.x*v1.x + v1.y*v1.y + v1.z*v1.z);
}