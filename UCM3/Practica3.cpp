#include "Practica3.h"
#include "TextureManagement.h"
#include "ObjetoConvexo.h"
#include "Selector.h"
#include "Textura.h"
#include <iostream>
#include <vector>
// Scene visible area size
GLdouble xLeft= 0.0, xRight= 800.0, yBot= 0.0, yTop= 600.0;

GLdouble escala = 1;

Objeto2D **od = new Objeto2D*[10];
int numObjetos = 0; // numero de objetos en la escena

GLuint textura;
GLuint tWidth, tHeight;
Selector *selec;
Vector2 **listaVertices;
Vector2 **listaVerticesAntiguio;
std::vector<Selector> selectores;   
Selector *selectorConstruccion;
MODO modoActual;
bool running;

int numVertices;

Practica3::Practica3(void)
{
	modoActual = design;

	listaVertices = new Vector2*[10];
	listaVerticesAntiguio = new Vector2*[10];
	running = false;
	//glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	// Cargo la textura en memoria
	initTexture(textura,tWidth,tHeight,"textura/ray.bmp");
	HEIGHT =600; WIDTH =800;
	//Establezco el modo inicial
	
	selectorConstruccion = new Selector();
	// Se carga el triangulo inicial por defecto
	listaVertices[numVertices] = new Vector2(200,200);
	listaVerticesAntiguio[numVertices++] = new Vector2(200,200);
	listaVertices[numVertices] = new Vector2(200,400);
	listaVerticesAntiguio[numVertices++] = new Vector2(200,400);
	listaVertices[numVertices] = new Vector2(400,200);
	listaVerticesAntiguio[numVertices++] = new Vector2(400,200);


	//selectorConstruccion->setVertices(numVertices,listaVertices);
	selectorConstruccion->modo = design;
	//selectorConstruccion->WIDTH =WIDTH;
	//selectorConstruccion->HEIGHT = HEIGHT;
	//selectorConstruccion->calcularBaricentro();
	
	selectores.insert(selectores.begin(), *selectorConstruccion);

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
	 if(modoActual == design) {
		od[i]->dibuja();
	 }
  }

  for (auto &selec : selectores) // access by reference to avoid copying
    {  selec.dibuja();   }

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


void timer(int flag){
	if(modoActual == animate && running){
	glutPostRedisplay();
	for (auto &selec : selectores) // access by reference to avoid copying
    {  selec.step();   }
	glutTimerFunc(1000/60,timer,0);
	}
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
	  modoActual = design;
	  running = false;
    break ;
  case 's' :
	  modoActual = select;
	  /*if(numVertices <3){
			listaVertices[0] = listaVerticesAntiguio[0]->clonar();
			listaVertices[1] = listaVerticesAntiguio[1]->clonar();
			listaVertices[2] = listaVerticesAntiguio[2]->clonar();
			selector->setVertices(3,listaVertices);
			numVertices =3;
	  }*/
	  running = false;
    break ;
  case 'a' :
	  modoActual = animate;
	 /* if(numVertices <3){
			listaVertices[0] = listaVerticesAntiguio[0]->clonar();
			listaVertices[1] = listaVerticesAntiguio[1]->clonar();
			listaVertices[2] = listaVerticesAntiguio[2]->clonar();
			selector->setVertices(3,listaVertices);
			numVertices =3;
	  }*/
	  if(!running){
	    running = true;
	    timer(1);
	  }
    break ;
   case 'p' :
	   for (auto &selec : selectores) // access by reference to avoid copying
    {  selec.step();   }
    break ;
   case 'q':
	   running = running ? false : true;
	   timer(1);
	break;


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
	if(modoActual == design) {
		if ((button==GLUT_LEFT_BUTTON) && (state==GLUT_DOWN)){
			Vector2 *v2 = new Vector2(x,HEIGHT-y);
			if(numVertices == 3) numVertices =0 ;
			listaVertices[numVertices++] = v2;
			selectorConstruccion->setVertices(numVertices,listaVertices);
			if(numVertices == 3){
				selectorConstruccion->calcularBaricentro() ;
				selectores.insert(selectores.begin(),*selectorConstruccion);
				selectorConstruccion = new Selector();
				/*
				listaVerticesAntiguio[0] = listaVertices[0]->clonar();
				listaVerticesAntiguio[1] = listaVertices[1]->clonar();
				listaVerticesAntiguio[2] = listaVertices[2]->clonar();
				*/
			}

			std::cout << x << '\t' << y << std::endl;
		}
	}else if(modoActual == select){
		if ((button==GLUT_LEFT_BUTTON) && (state==GLUT_DOWN)){
			Vector2 *v2 = new Vector2(x,HEIGHT-y);
			// Seleccionar sin mo
			for (auto &selec : selectores) 
			{  selec.estaDentro(v2);   }
		}
	}
		
}