/*************************************************************************/
/*                                                                       */
/*   modelado.c                                                          */
/*   Rev. 3.0  01/09/2012   Universidad Jaume I de Castell�n             */
/*                                                                       */
/*************************************************************************/
#define RAND_MAX 0x7FFFU

#include <stdio.h>
#include "glig.h"
#include "modelado.h"
#include <limits.h>
#include <math.h>


#include "glut.h"

extern const int CircleIter = 300; //Numero de iteraciones para el cálculo de alturas usando circles algorithm

//initializing all the required variables
float Vertices[400][400];
float VNormales[400][400][3];
short DibujaOn = 1;
float AlturaMax = 0;
float AlturaMin = 0;

//size of the area
int SizeX = 400;
int SizeZ = 400;

//camera positions
float camPos[] = { 50, 100, 50 };
float angle = 0.0f;

/******************************************************************************************/
/* Crea las distintas display lists                                                       */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void IniciaDisplayLists(void) {
	CreaEscena();
}


/******************************************************************************************/
/* Dibuja la escena                                                                       */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void DibujaEscena(void) {
	glCallList(escena);
}


/******************************************************************************************/
/* Define un arco de la escena                                                            */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void ArcoSolid(void) {
	glPushMatrix();
	glTranslatef(0.75, 0.0, 0.0);
	glScalef(0.2, 1.0, 0.2);
	igSolidRulo(10, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.75, 0.0, 0.0);
	glScalef(0.2, 1.0, 0.2);
	igSolidRulo(10, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 1.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.05, 2.3, 0.5);
	igSolidCube();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, -0.98, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.05, 2.3, 0.5);
	igSolidCube();
	glPopMatrix();
}

/******************************************************************************************/
/* Define los arcos de la escena                                                          */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void ArcosSolid(void) {
	int i;
	glScalef(0.9, 0.9, 0.9);
	for (i = 0; i < 12; i++) {
		glPushMatrix();
		glRotatef(i * 360 / 12, 0.0, 1.0, 0.0);
		glTranslatef(0.0, 0.0, -2.0);
		glScalef(0.5, 0.5, 0.5);
		ArcoSolid();
		glPopMatrix();
	}
}


/******************************************************************************************/
/* Crea una display list para el suelo                                                    */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaSuelo(void) {
	suelo = glGenLists(1);
	if (suelo != 0) {
		glNewList(suelo, GL_COMPILE);
		glPushMatrix();
		glTranslatef(0.0, -0.5, 0.0);
		glRotatef(12.0, 0.0, 1.0, 0.0);
		glScalef(2.0, 0.005, 2.0);
		igWireCone(12, 6);
		glPopMatrix();
		glEndList();
	}
	else puts("Se ha producido un error creando la display list para el suelo.");
}


/******************************************************************************************/
/*  Crea una display list para toda la escena                                             */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaEscena(void) {
	escena = glGenLists(1);
	if (escena != 0) {
		glNewList(escena, GL_COMPILE);
		glPushMatrix();
		CalculaMalla();
		CreaTerreno();
		//textura1();
		//ArcosSolid();
		glPopMatrix();
		glEndList();
	}
	else puts("Se ha producido un error creando la display list de la escena.");
}

/******************************************************************************************/
/* Crea el terreno con montañas                                                           */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaTerreno() { 
	int i, j;
	for (i = 0; i < SizeX - 1; i++) { 
		for (j = 0; j < SizeZ - 1; j++) {
			PintaTerreno(i, j);
			CreaCelda(i, j);
		}
	}
}

/******************************************************************************************/
/* Selecciona el color de los cuadrados de la malla que compone el terreno en función     */
/* de la altura en y                                                                      */
/* Parametros: i: posicion en X; j: posicion en Z										  */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void PintaTerreno(int i, int j) {
	float faceColour = (((Vertices[i][j] - AlturaMin) / (AlturaMax - AlturaMin)) + 0.05); //calculates the average value for the poistion which gives the neede colour
	if (Vertices[i][j] < 0.5) {//creates the colour of water
		glColor3f(0.549*faceColour, 0.8196*faceColour, 1 * faceColour);
	}
	else if (Vertices[i][j] > 0.5 && Vertices[i][j] < 2) {//creates the colour of sand
		glColor3f(0.76*faceColour, 0.698*faceColour, 0.5*faceColour);
	}
	else if (Vertices[i][j] > 2 && Vertices[i][j] < 10) {//creates the colour of grass
		glColor3f(0.396*faceColour, 0.56*faceColour, 0.19*faceColour);
	}
	else if (Vertices[i][j] > 10 && Vertices[i][j] < 16) {//creates the colour of rocks/mountain
		glColor3f(0.65*faceColour, 0.43*faceColour, 0.18*faceColour);
	}
	else if (Vertices[i][j] > 16) {//creats the colour of snow
		glColor3f(1 * faceColour, 0.98*faceColour, 0.98*faceColour);
	}
}
/******************************************************************************************/
/* Crea un cuadrado mediante GL_TRIANGLE_STRIP										      */
/* Parametros: i: posicion en X; j: posicion en Z										  */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaCelda(int i, int j) {
	glBegin(GL_TRIANGLE_STRIP); {
		glNormal3fv(VNormales[i][j]);
		glVertex3f(i, Vertices[i][j], j);

		glNormal3fv(VNormales[i][j + 1]);
		glVertex3f(i, Vertices[i][j + 1], j + 1);


		glNormal3fv(VNormales[i + 1][j]);
		glVertex3f(i + 1, Vertices[i + 1][j], j);

		glNormal3fv(VNormales[i + 1][j + 1]);
		glVertex3f(i + 1, Vertices[i + 1][j + 1], j + 1);
	}glEnd();
}
void CalcVectoresNormales() {
	float v1[3];
	float v2[3];
	float v[3];
	for (int i = 0; i < SizeX; i++) {
		for (int j = 0; j < SizeZ; j++) {
			v1[0] = i + 1;
			v1[1] = Vertices[i + 1][j] - Vertices[i][j];
			v1[2] = j;

			v2[0] = i + 1;
			v2[1] = Vertices[i + 1][j + 1] - Vertices[i][j];
			v2[2] = j + 1;

			//calculate cross product 
			v[0] = v1[1] * v2[2] - v1[2] * v2[1];
			v[1] = v1[2] * v2[0] - v1[0] * v2[2];
			v[2] = v1[0] * v2[1] - v1[1] * v2[0];
			float l = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

			//normal vectors
			VNormales[i][j][0] = v[0] / l;
			VNormales[i][j][1] = v[1] / l;
			VNormales[i][j][2] = v[2] / l;
		}
	}
}

//runs the circle algorithm to create the terrain
void CircleAlgorithm() {
	int randomx = rand() % SizeX;
	int randomz = rand() % SizeZ;
	int randomRadius = (rand() % 20) + 10;
	float disp = (rand() % 12) + 1;
	for (int i = 0; i < SizeX; i++) {
		for (int j = 0; j < SizeZ; j++) {
			int dx = i - randomx;
			int dz = j - randomz;
			float distance = sqrtf((dx*dx) + (dz*dz));
			float pd = (distance * 2) / randomRadius;
			if (fabs(pd) <= 1.0) {
				Vertices[i][j] += (disp / 2.0) + (cos(pd*3.14)*(disp / 2.0));
			}
			//calculates the max and min value of the terain so that it can be used for colouring 
			if (Vertices[i][j] > AlturaMax) {
				AlturaMax = Vertices[i][j];
			}
			if (Vertices[i][j] < AlturaMin) {
				AlturaMin = Vertices[i][j];
			}
		}
	}
}

void CalculaMalla() {
	if (DibujaOn == 1) {
		for (int i = 0; i < CircleIter; i++) {//for the algorithms for 500 instances 
			CircleAlgorithm();//runs the circle algorithm 
		}
		CalcVectoresNormales();
		DibujaOn = 0; //Desactiva el dibujado
	}
}

void ReseteaAlturas() {//resets height to zero
	for (int i = 0; i < SizeX; i++) {
		for (int j = 0; j < SizeZ; j++) {
			Vertices[i][j] = 0;
		}
	}
}
