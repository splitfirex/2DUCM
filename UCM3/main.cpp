#include <stdio.h>
#include <iostream>
#include <GL/freeglut.h>
#include <Windows.h>
#include "Practica3.h"

void Display();
void reshape(int w, int h);
void initGL();
void keyFunc(unsigned char key, int mX, int mY);
void keySp(int key, int mX, int mY);
void timer(int flag);
void mouse(int button, int state, int x, int y);

Escena *actual;

int main(int argc, char *argv[]){

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
	actual = new Practica3();
	glutInitWindowSize(actual->WIDTH,actual->HEIGHT);
	glutInit(&argc,argv);
	glutCreateWindow("Graficas Practica 3");

	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyFunc);
	glutSpecialFunc(keySp);
	glutMouseFunc(mouse);

	//timer(0);
	glutMainLoop();

	return 0;
}

void timer(int flag){
	glutPostRedisplay();
	glutTimerFunc(1000/60,timer,0);
}

void Display(){
	actual->dibujar();
	glFlush();
	glutSwapBuffers();
}

void reshape(int w, int h){
	actual->reshape(w,h);
}


void keyFunc(unsigned char key, int mX, int mY){
	actual->keyboard(key,mX,mY);
}

void keySp(int key, int mX, int mY){
	actual->keyboardSP(key,mX, mY);
}

void mouse(int button, int state, int x, int y){
	actual->mouse(button,state,x,y);
}