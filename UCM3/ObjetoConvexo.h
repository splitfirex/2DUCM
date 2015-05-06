
#include "Objeto2D.h"
#pragma once

class ObjetoConvexo : public Objeto2D
{
public:
	ObjetoConvexo(int lados, double tam);
	~ObjetoConvexo(void);
	void dibuja();

private:
	int lados;
	double tamano;

};

