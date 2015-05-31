#include <stdio.h>
#include <iostream>
#include <GL/freeglut.h>
#include <Windows.h>
#include "Practica3.h"
#include <time.h>

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

	glutInitWindowSize(800,600);
	glutInit(&argc,argv);
	glutCreateWindow("Graficas Practica 3");

	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyFunc);
	glutSpecialFunc(keySp);
	glutMouseFunc(mouse);

	time_t seconds;	
	time(&seconds);

	srand((unsigned int) seconds);

	actual = new Practica3();
	initGL();

	//timer(0);
	glutMainLoop();

	return 0;
}

void Display(){
	actual->dibujar();
	//glFlush();
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

void initGL(){
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0); 

	glPointSize(4.0);
	glLineWidth(2.0);

	// Viewport
	glViewport(0, 0, actual->WIDTH, actual->HEIGHT);

	// Model transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Scene Visible Area
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}