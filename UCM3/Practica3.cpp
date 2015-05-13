#include "Practica3.h"
#include "TextureManagement.h"
#include "ObjetoConvexo.h"
#include "Selector.h"
#include "Textura.h"
#include <iostream>
// Scene visible area size
GLdouble xLeft= 0.0, xRight= 800.0, yBot= 0.0, yTop= 600.0;

GLdouble escala = 1;

Objeto2D **od = new Objeto2D*[10];
int numObjetos = 0; // numero de objetos en la escena

GLuint textura;
GLuint tWidth, tHeight;
Selector *selec;
Vector2 **listaVertices;
Selector *selector;
int numVertices;

Practica3::Practica3(void)
{
	
	listaVertices = new Vector2*[10];
	//glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	// Cargo la textura en memoria
	initTexture(textura,tWidth,tHeight,"textura/ray.bmp");
	HEIGHT =600; WIDTH =800;
	//Establezco el modo inicial
	selector = new Selector();
	// Se carga el triangulo inicial por defecto
	listaVertices[numVertices++] = new Vector2(200,200);
	listaVertices[numVertices++] = new Vector2(200,400);
	listaVertices[numVertices++] = new Vector2(400,200);

	selector->setVertices(numVertices,listaVertices);
	selector->modo = design;
	selector->WIDTH =WIDTH;
	selector->HEIGHT = HEIGHT;
	selector->calcularBaricentro();

	//Genero el objeto textura
	Vector2 **vectores = new Vector2*[4];
	vectores[0] = new Vector2(0,0); vectores[1] = new Vector2(WIDTH,0);
	vectores[2] = new Vector2(WIDTH,HEIGHT); vectores[3] = new Vector2(0,HEIGHT);
	od[numObjetos] = new Textura();
	od[numObjetos]->setVertices(4,vectores);
	numObjetos++;
	

}


Practica3::~Practica3(void)
{
}

void Practica3::dibujar(){
  glClear( GL_COLOR_BUFFER_BIT );

  for(int i =0 ; i< numObjetos ; i++){
	 glBindTexture(GL_TEXTURE_2D, textura);
	 if(selector->modo == design) {
		od[i]->dibuja();
	 }
  }
  selector->dibuja();
}


void Practica3::reshape(int w, int h){

	//GLdouble widthScale= WIDTH/(xRight-xLeft);
  //GLdouble heightScale= HEIGHT/(yTop-yBot);
  
  //Resize Scene Visible Area 
  //Width and height scale remain
  GLdouble newSVAWidth= w*(xRight-xLeft)/WIDTH; //= newWidth/widthScale
  GLdouble newSVAHeight= h*(yTop-yBot)/HEIGHT; //= newHeight/heightScale

  GLdouble xMiddle= ( xLeft+xRight )/2.0;
  xRight= xMiddle + newSVAWidth/2.0;
  xLeft=  xMiddle - newSVAWidth/2.0;
  
  GLdouble yMiddle= ( yBot+yTop )/2.0;
  yTop= yMiddle + newSVAHeight/2.0;
  yBot= yMiddle - newSVAHeight/2.0;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(xLeft, xRight, yBot, yTop);

  //Resize Viewport
  WIDTH= w;
  HEIGHT= h;
  glViewport ( 0, 0, WIDTH, HEIGHT ) ;

}

void Practica3::keyboard(unsigned char key, int mX, int mY){
	
  bool need_redisplay = true;

  switch (key) {
  case 27:  /* Escape key */
    //continue_in_main_loop = false; // (**)
	//glutLeaveMainLoop(); //Freeglut's sentence for stopping glut's main loop (*)
    break;

  case '+' :
    //xTriangle += 10.0;
    break ;

  case '-' :
    //xTriangle -= 10.0;
    break ;

  case 'd' :
	  selector->modo = design;
    break ;
  case 's' :
	  selector->modo = select;
    break ;

  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}

void Practica3::keyboardSP(int key, int mX, int mY){
	bool need_redisplay = true;

	switch(key) {
        case GLUT_KEY_LEFT:
            std::cout << std::endl << "izq" << std::endl;//key up
			xLeft+= WIDTH*5/100 ; xRight+= WIDTH*5/100 ;
            break;
        case GLUT_KEY_RIGHT:
            std::cout << std::endl << "der" << std::endl;   // key down
			xLeft-= WIDTH*5/100 ; xRight-= WIDTH*5/100 ;
            break;
        case GLUT_KEY_UP:
			yBot-= HEIGHT*5/100 ; yTop-= HEIGHT*5/100 ;
            std::cout << std::endl << "Right" << std::endl;  // key right
            break;
        case GLUT_KEY_DOWN:
			yBot+= HEIGHT*5/100 ; yTop+= HEIGHT*5/100 ;
            std::cout << std::endl << "Left" << std::endl;  // key left
            break;
        default:
            need_redisplay = false;
            break;
        }
	  if (need_redisplay){
		  reshape(WIDTH, HEIGHT);
		  glutPostRedisplay();
	  }

}

void Practica3::mouse(int button, int state, int x, int y){
	if(selector->modo == design) {
		if ((button==GLUT_LEFT_BUTTON) && (state==GLUT_DOWN)){
			Vector2 *v2 = new Vector2(x,HEIGHT-y);
			if(numVertices == 3) numVertices =0 ;
			listaVertices[numVertices++] = v2;
			selector->setVertices(numVertices,listaVertices);
			if(numVertices == 3) selector->calcularBaricentro() ;
			std::cout << x << '\t' << y << std::endl;
		}
	}
		
}