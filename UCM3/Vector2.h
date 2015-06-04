#pragma once
class Vector2
{
public:
   float x;
   float y;
   Vector2(float x1, float y1);
   Vector2();
   ~Vector2();
   void trasladar(Vector2* traslacion); //modifica this
   void escalar(float factor); //modifica this
   void normalizar(); //modifica this
   float dot(Vector2* vector2);
   void suma(Vector2* vector2); //modifica this
   Vector2* clonar();
   float distanciaAPunto(Vector2* p);
   float getX();
   float getY();
   void setX(float x1);
   void setY(float y1);
   float longitud(); //longitud del vector
   Vector2* rotaP(Vector2* centroRot, double ang);
   Vector2* rotaV(double ang);
   bool sobrePone(Vector2* p);

   Vector2* normalIzquierda();
   friend Vector2* operator- (Vector2 v2, Vector2 v1);
   friend Vector2* operator+ (Vector2 v2, Vector2 v1);
   friend Vector2* operator* (double exp, Vector2 v2);

};

