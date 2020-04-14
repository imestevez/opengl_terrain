/*************************************************************************/
/*                                                                       */
/*   examinar.c                                                          */
/*   Rev. 3.0  01/09/2012   Universidad Jaume I de Castellón             */
/*                                                                       */
/*************************************************************************/

/***************** INCLUDES DE LAS LIBRERIAS NECESARIAS ******************/
#include "glut.h"
#include <stdio.h>
#include <math.h>
#include "examinar.h"
#include "material.h"
#include "glig.h"
#include "modelado.h"

//lighting code
float light_pos1[] = { -150.0,150.0,100,1.0 };
float light_pos2[] = { 150.0,150.0,-100,1.0 };
float amb0[4] = { 1, 1, 1, 1 };
float diff0[4] = { 1, 1, 1, 1 };
float spec0[4] = { 1, 1, 1, 1 };

/* MATERIALS */
float m_amb[] = { 0.1745f, 0.01175f, 0.01175f, 0.55f };
float m_diff[] = { 0.61424f, 0.04136f, 0.04136f, 0.55f };
float m_spec[] = { 0.727811f, 0.626959f, 0.626959f, 0.55f };
float shiny = 76.8;

//shading
short flatShading = 0;

/******************************************************************************************/
/* Establece el area visible y el tipo de proyeccion                                      */
/* Parametros: int ancho --> Ancho del area visible                                       */
/*             int alto --> Alto del area visible                                         */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void TamanyoVentana(GLsizei ancho, GLsizei alto)
{
	//Definicion del viewport
	glViewport(0, 0, ancho, alto);

	//Definicion de la vista
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10.0, 10.0, -10.0*(GLfloat)alto/(GLfloat)ancho, 10.0*(GLdouble)alto/(GLfloat)ancho, -20.0, 20.0);
	gluPerspective(50, (GLdouble)alto / (GLdouble)ancho, 1.0, 10000.0);
}

/******************************************************************************************/
/* Abre una ventana OpenGL                                                                */
/* Parametros: int numeroArgumentos --> El numero de argumentos en la llamada al programa */
/*             char ** listaArgumentos --> Vector de cadenas con cada argumento           */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void AbreVentana(int numeroArgumentos, char ** listaArgumentos)
{
	glutInit(&numeroArgumentos, listaArgumentos);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(VentanaAncho, VentanaAlto);
	glutInitWindowPosition(VentanaX, VentanaY);
	glutCreateWindow(listaArgumentos[0]);
	glutDisplayFunc(Dibuja);
	glutReshapeFunc(TamanyoVentana);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //Establece el color de borrado
	glClear(GL_COLOR_BUFFER_BIT); //Borra el buffer de color
	glColor3f(1.0f, 1.0f, 1.0f); //Establece el color de dibujo

	glMatrixMode(GL_PROJECTION);
}


/******************************************************************************************/
/* Define las acciones tras una pulsacion del teclado                                     */
/* Parametros: unsigned char key --> Codigo de la tecla pulsada                           */
/*             int x --> Coordenada x del cursor en el momento de pulsar la tecla         */
/*             int y --> Coordenada y del cursor en el momento de pulsar la tecla         */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void Teclado(unsigned char tecla, int x, int y)
{
	switch (tecla)
	{
	case 27: //Codigo de la tecla de Escape
		exit(0);
		break;

	case 'w':
		modo = WALK;
		printf("Modo = WALK      \r");
		break;

	case 'e':
		modo = EXAMINAR;
		printf("Modo = EXAMINAR    \r");
		break;

	case 'f':
		modo = FLY;
		printf("Modo = FLY      \r");
		break;
	}
}


/******************************************************************************************/
/* Define las acciones tras una pulsacion del teclado ampliado                            */
/* Parametros: unsigned char key --> Codigo de la tecla pulsada                           */
/*             int x --> Coordenada x del cursor en el momento de pulsar la tecla         */
/*             int y --> Coordenada y del cursor en el momento de pulsar la tecla         */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void TecladoAmpliado(int tecla, int x, int y){
	switch (tecla)	{
	case GLUT_KEY_PAGE_UP:
		if (modo == FLY)		{
			beta = beta + 1.50;
			if (beta > 360.0) beta = beta - 360.0;
			iy = oy + PASO * sin(grad2rad(beta));
		}
		break;
	case GLUT_KEY_UP: //Pulsacion cursor arriba del teclado ampliado
		if (modo == WALK || modo == FLY)		{
			ox = ix;
			oz = iz;
			ix = ox + PASO * sin(grad2rad(alfa));
			iz = oz - PASO * cos(grad2rad(alfa));
			if (modo == FLY)			{
				oy = iy;
				iy = iy + PASO * sin(grad2rad(beta));
			}
		}
		else if (modo == EXAMINAR)		{
			beta = beta + 1.50;
			if (beta > 360.0) beta = beta - 360.0;
			iy = oy + PASO * sin(grad2rad(beta));
		}
		break;

	case GLUT_KEY_PAGE_DOWN:
		if (modo == FLY)		{
			beta = beta - 1.50;
			if (beta > 360.0) beta = beta - 360.0;
			iy = oy + PASO * sin(grad2rad(beta));
		}
		break;
	case GLUT_KEY_DOWN: //Pulsacion cursor abajo del teclado ampliado
		if (modo == WALK || modo == FLY)		{
			ox = ox - (ix - ox);
			oz = oz - (iz - oz);
			ix = ox + PASO * sin(grad2rad(alfa));
			iz = oz - PASO * cos(grad2rad(alfa));
			if (modo == FLY)			{
				iy = oy;
				oy = oy - PASO * sin(grad2rad(beta));
			}
		}
		else if (modo == EXAMINAR)		{
			beta = beta - 1.50;
			if (beta < 0.0) beta = beta + 360.0;
			iy = oy + PASO * sin(grad2rad(beta));
		}
		break;

	case GLUT_KEY_RIGHT: //Pulsacion cursor derecha del teclado ampliado
		alfa = alfa + 15.0;
		if (alfa > 360.0) alfa = alfa - 360.0;
		ix = ox + PASO * sin(grad2rad(alfa));
		iz = oz - PASO * cos(grad2rad(alfa));
		break;

	case GLUT_KEY_LEFT: //Pulsacion cursor izquierda del teclado ampliado
		alfa = alfa - 15.0;
		if (alfa < 0.0) alfa = alfa + 360.0;
		ix = ox + PASO * sin(grad2rad(alfa));
		iz = oz - PASO * cos(grad2rad(alfa));
		break;
	}
	glutPostRedisplay();
}


//Rutina de definición de eventos 
/******************************************************************************************/
/* Inicia las funciones de callback                                                       */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void IniciaFuncionesCallback(void){
	glutKeyboardFunc(Teclado);
	glutSpecialFunc(TecladoAmpliado);
}


/******************************************************************************************/
/* Funcion de dibujado                                                                    */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void Dibuja(void){
	//Transformacion de la camara
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(ox, oy, oz, ix, iy, iz, 0, 1, 0);

	//Llamadas a las display lists
	DibujaEscena();

	glFlush();
}


/******************************************************************************************/
/* Funcion principal                                                                      */
/* Parametros: int numeroArgumentos --> El numero de argumentos en la llamada al programa */
/*             char ** listaArgumentos --> Vector de cadenas con cada argumento           */
/* Salida: Un entero que se devuelve al sistema al acabar la ejecucion del programa       */
/******************************************************************************************/
int main(int numArgumentos, char ** listaArgumentos){
	//Creación de la ventana de la aplicación
	AbreVentana(numArgumentos, listaArgumentos);

	printf("Modo = WALK\r");

	//Rutinas para el control de eventos
	IniciaFuncionesCallback();

	initTextura0("./resources/grass.tga");
	initTextura1("./resources/marmol256.tga");
	initTextura2("./resources/cielo256.tga");


	//Crea las display list de cada cuadrica
	IniciaDisplayLists();

	glEnable(GL_DEPTH_TEST);

	//A la espera de eventos....
	glutMainLoop();

	return (0);
}