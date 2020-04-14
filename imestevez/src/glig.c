/*************************************************************************/
/*                                                                       */
/*                 glig.c LIBRERIA DE MODELADO GEOMETRICO	             */
/*                                                                       */
/*   Rev. 3.0  01/09/2012   Universidad Jaume I de Castellón             */
/*                                                                       */
/*************************************************************************/

/***************** INCLUDES DE LAS LIBRERIAS NECESARIAS ******************/
#include "glut.h"
#include <math.h>
#include <stdio.h>
#include "glig.h"

#define PI 3.1415926535897932
#define ALFA (0.5-v)*PI
#define BETA 2*PI*u
#define E 0.001
#define F 0.002


/************************* FUNCIONES BASICAS **********************************************/
/******************************************************************************************/
/* Devuelve la coordenada x de un punto en R3 a partir de un punto (u,v)                  */
/*   de un espacio parametrico en R2                                                      */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La coordenada x de un punto en R3                                              */
/******************************************************************************************/
float xSuperQuadric(float u, float v, float R, float s1, float s2)
{
	float cosalfa, cosbeta, powcosalfa, powcosbeta;

	cosalfa = (float)cos(ALFA);
	cosbeta = (float)cos(BETA);

	if (cosalfa > 0.0)
		powcosalfa = (float)pow(cosalfa, s1);
	else
		powcosalfa = (float)-pow(-cosalfa, s1);

	if (cosbeta > 0.0)
		powcosbeta = (float)pow(cosbeta, s2);
	else
		powcosbeta = (float)-pow(-cosbeta, s2);

	return (R*powcosalfa*powcosbeta);

}


/******************************************************************************************/
/* Devuelve la coordenada y de un punto en R3 a partir de un punto (u,v)                  */
/*   de un espacio parametrico en R2                                                      */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La coordenada y de un punto en R3                                              */
/******************************************************************************************/
float ySuperQuadric(float u, float v, float R, float s1, float s2)
{
	float sinalfa, powsinalfa;

	sinalfa = (float)sin(ALFA);

	if (sinalfa > 0.0)
		powsinalfa = (float)pow(sinalfa, s1);
	else
		powsinalfa = (float)-pow(-sinalfa, s1);

	return (R*powsinalfa);
}


/******************************************************************************************/
/* Devuelve la coordenada de un punto en R3 a partir de un punto (u,v)                    */
/*   de un espacio parametrico en R2                                                      */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La coordenada z de un punto en R3                                              */
/******************************************************************************************/
float zSuperQuadric(float u, float v, float R, float s1, float s2)
{
	float cosalfa, sinbeta, powcosalfa, powsinbeta;

	cosalfa = (float)cos(ALFA);
	sinbeta = (float)sin(BETA);

	if (cosalfa > 0.0)
		powcosalfa = (float)pow(cosalfa, s1);
	else
		powcosalfa = (float)-pow(-cosalfa, s1);

	if (sinbeta > 0.0)
		powsinbeta = (float)pow(sinbeta, s2);
	else
		powsinbeta = (float)-pow(-sinbeta, s2);

	return(R*powcosalfa*powsinbeta);
}
/******************************************************************************************/
/* Calcula la variacion en x para un incremento de u, derivada de x con respecto de u     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de x con u                                                        */
/******************************************************************************************/
float dxuSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((xSuperQuadric(u + E, v, R, s1, s2) - xSuperQuadric(u - E, v, R, s1, s2)) / (2 * E));
}


/******************************************************************************************/
/* Calcula la variacion en y para un incremento de u, derivada de y con respecto de u     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de y con u                                                        */
/******************************************************************************************/
float dyuSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((ySuperQuadric(u + E, v, R, s1, s2) - ySuperQuadric(u - E, v, R, s1, s2)) / (2 * E));
}


/******************************************************************************************/
/* Calcula la variacion en z para un incremento de u, derivada de z con respecto de u     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de z con u                                                        */
/******************************************************************************************/
float dzuSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((zSuperQuadric(u + E, v, R, s1, s2) - zSuperQuadric(u - E, v, R, s1, s2)) / (2 * E));
}


/******************************************************************************************/
/* Calcula la variacion en x para un incremento de v, derivada de x con respecto de v     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de x con v                                                        */
/******************************************************************************************/
float dxvSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((xSuperQuadric(u, v + E, R, s1, s2) - xSuperQuadric(u, v - E, R, s1, s2)) / (2 * E));
}


/******************************************************************************************/
/* Calcula la variacion en y para un incremento de u, derivada de y con respecto de v     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de y con u                                                        */
/******************************************************************************************/
float dyvSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((ySuperQuadric(u, v + E, R, s1, s2) - ySuperQuadric(u, v - E, R, s1, s2)) / (2 * E));
}

/******************************************************************************************/
/* Calcula la variacion en z para un incremento de u, derivada de z con respecto de v     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de z con u                                                        */
/******************************************************************************************/
float dzvSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((zSuperQuadric(u, v + E, R, s1, s2) - zSuperQuadric(u, v - E, R, s1, s2)) / (2 * E));
}

/******************************************************************************************/
/* Calcula la componente x del vector normal a la supercuadrica en (u,v)                  */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: Componente x del vector normal                                                 */
/******************************************************************************************/
float nxSuperQuadric(float u, float v, float R, float s1, float s2)
{
	if (v <= E) v = F;
	if (v >= 1 - E) v = 1 - F;
	return(dyuSuperQuadric(u, v, R, s1, s2)*dzvSuperQuadric(u, v, R, s1, s2) -
		dyvSuperQuadric(u, v, R, s1, s2)*dzuSuperQuadric(u, v, R, s1, s2));
}

/******************************************************************************************/
/* Calcula la componente y del vector normal a la supercuadrica en (u,v)                  */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: Componente y del vector normal                                                 */
/******************************************************************************************/
float nySuperQuadric(float u, float v, float R, float s1, float s2)
{
	if (v <= E) v = F;
	if (v >= 1 - E) v = 1 - F;
	return(dxvSuperQuadric(u, v, R, s1, s2)*dzuSuperQuadric(u, v, R, s1, s2) -
		dxuSuperQuadric(u, v, R, s1, s2)*dzvSuperQuadric(u, v, R, s1, s2));
}

/******************************************************************************************/
/* Calcula la componente z del vector normal a la supercuadrica en (u,v)                  */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: Componente z del vector normal                                                 */
/******************************************************************************************/
float nzSuperQuadric(float u, float v, float R, float s1, float s2)
{
	if (v <= E) v = F;
	if (v >= 1 - E) v = 1 - F;
	return(dxuSuperQuadric(u, v, R, s1, s2)*dyvSuperQuadric(u, v, R, s1, s2) -
		dxvSuperQuadric(u, v, R, s1, s2)*dyuSuperQuadric(u, v, R, s1, s2));
}

/********************************************************************************************/
/* Dibuja una esfera a partir de paralelos y meridianos usando las funciones _SuperQuadric	*/
/* Parametros: int pu --> Número de puntos para la representación en X						*/
/*             int pv --> Número de puntos para la representación en Y						*/
/*             float R --> Radio de la esfera envolvente									*/
/*             float s1 --> Numero de divisiones en u										*/
/*             float s2 --> Numero de divisiones en v										*/
/* Salida: void																				*/
/********************************************************************************************/
void igCreateQuadraticObject(int pu, int pv, float uMax, float vMax, float R, float s1, float s2)
{
	float u, v, inc_u, inc_v;
	float x;
	float y;
	float z;
	int   i, j;

	v = 0.0f;
	u = 0.0f;
	inc_u = 1.0f / pu;
	inc_v = 1.0f / pv;


	for (j = 0; j <= pv; j++) {
		glBegin(GL_LINE_STRIP); {
			for (i = 0; i <= pu; i++) {
				x = xSuperQuadric(u, v, R, s1, s2);
				y = ySuperQuadric(u, v, R, s1, s2);
				z = zSuperQuadric(u, v, R, s1, s2);
				glVertex3f(x, y, z);
				if (u < uMax)u = u + inc_u;
			}
			if (v < vMax)v += inc_v;
			u = 0;
		}glEnd();
	}
	u = v = 0;
	for (j = 0; j <= pu; j++) {
		glBegin(GL_LINE_STRIP); { //Para que no una el comienzo con el final 
			for (i = 0; i <= pv; i++) { //Una iteracion más para cerrar esfera
				x = xSuperQuadric(u, v, R, s1, s2);
				y = ySuperQuadric(u, v, R, s1, s2);
				z = zSuperQuadric(u, v, R, s1, s2);
				glVertex3f(x, y, z);
				if (v < vMax)v += inc_v;
			}
			if (u < uMax)u = u + inc_u;
			v = 0;
		}glEnd();
	}
}
void igWireSphere(int pu, int pv) /* s1 y s2 a 1 */
{
	igCreateQuadraticObject(pu, pv, 1, 1, 1, 1, 1);
}
void igWireRulo(int pu, int pv) /* s1= 0.5, s2= 1 */
{
	igCreateQuadraticObject(pu, pv, 1, 1, 1, 0.5, 1);
}
void igWireDado(int pu, int pv) /* s1= 0.5, s2 =0.5 */
{
	igCreateQuadraticObject(pu, pv, 1, 1, 1, 0.5, 0.5);
}
void igWireSemiSphere(int pu, int pv) /* s1 y s2 a 1, uMax= 1, vMax= 0.5 */
{
	igCreateQuadraticObject(pu, pv, 1, 0.5, 1, 1, 1);
}

void igWireCube(void) {

	float Vertices[8][3] = {
		{ -0.5f, -0.5f, -0.5f } ,
		{ -0.5f, -0.5f, 0.5f },
		{ 0.5f, -0.5f, 0.5f },
		{ 0.5f, -0.5f, -0.5f },
		{ -0.5f, 0.5f, -0.5f },
		{ -0.5f, 0.5f, 0.5f },
		{ 0.5f, 0.5f, 0.5f },
		{ 0.5f, 0.5f, -0.5f }
	};
	//Parte delantera
	glBegin(GL_LINE_LOOP); {
		glVertex3fv(Vertices[0]);
		glVertex3fv(Vertices[1]);
		glVertex3fv(Vertices[2]);
		glVertex3fv(Vertices[3]);
	}glEnd();

	//Parte trasera
	glBegin(GL_LINE_LOOP); {
		glVertex3fv(Vertices[4]);
		glVertex3fv(Vertices[5]);
		glVertex3fv(Vertices[6]);
		glVertex3fv(Vertices[7]);
	}glEnd();

	//Union entre ambas partes
	glBegin(GL_LINES); {
		glVertex3fv(Vertices[0]);
		glVertex3fv(Vertices[4]);
		glVertex3fv(Vertices[1]);
		glVertex3fv(Vertices[5]);
		glVertex3fv(Vertices[2]);
		glVertex3fv(Vertices[6]);
		glVertex3fv(Vertices[3]);
		glVertex3fv(Vertices[7]);
	}glEnd();
}

void igWireCone(int pu, int pv) {
	igCreateQuadraticObject(pu, pv, 1, 0.5f, 1, 2.0f, 1.0f);
}
/******************************************************************************************/
/* Crea una cuadrica segun los parametros que se le pasan                                 */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/*             float uMax --> Valor maximo que alcanza el parametro u                     */
/*             float vMax --> Valor maximo que alcanza el parametro v                     */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1, float s2 --> Definen la forma de la cuadrica                     */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igCreateSolidQuadricObject(int pu, int pv, float uMax, float vMax, float R, float s1, float s2)
{
	float u, v, inc_u, inc_v;
	float x, y, z;
	float nx, ny, nz;
	int i;
	int j;

	v = 0.0;
	u = 0.0;
	inc_u = uMax / pu; /* donde 10 es el número de puntos en u */
	inc_v = vMax / pv;

	for (j = 0; j < pv; j++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0; i <= pu; i++)
		{
			glTexCoord2f(u, v);
			nx = nxSuperQuadric(u, v, R, s1, s2);
			ny = nySuperQuadric(u, v, R, s1, s2);
			nz = nzSuperQuadric(u, v, R, s1, s2);
			glNormal3f(nx, ny, nz);
			x = xSuperQuadric(u, v, R, s1, s2);
			y = ySuperQuadric(u, v, R, s1, s2);
			z = zSuperQuadric(u, v, R, s1, s2);
			glVertex3f(x, y, z);

			glTexCoord2f(u, v + inc_v);
			nx = nxSuperQuadric(u, v + inc_v, R, s1, s2);
			ny = nySuperQuadric(u, v + inc_v, R, s1, s2);
			nz = nzSuperQuadric(u, v + inc_v, R, s1, s2);
			glNormal3f(nx, ny, nz);
			x = xSuperQuadric(u, v + inc_v, R, s1, s2);
			y = ySuperQuadric(u, v + inc_v, R, s1, s2);
			z = zSuperQuadric(u, v + inc_v, R, s1, s2);
			glVertex3f(x, y, z);
			u = u + inc_u;
		}
		glEnd();
		v = v + inc_v;
		u = 0.0f;
	}
}

/******************************************************************************************/
/* Crea una esfera a partir de las ecuaciones de la supercuadrica                         */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidSphere(int pu, int pv)
{
	igCreateSolidQuadricObject(pu, pv, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
}


/******************************************************************************************/
/* Crea un rulo a partir de las ecuaciones de la supercuadrica                            */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidRulo(int pu, int pv)
{
	igCreateSolidQuadricObject(pu, pv, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f);
}


/******************************************************************************************/
/* Crea un dado a partir de las ecuaciones de la supercuadrica                            */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidDado(int pu, int pv)
{
	igCreateSolidQuadricObject(pu, pv, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f);
}


/******************************************************************************************/
/* Crea una semiesfera a partir de las ecuaciones de la supercuadrica                     */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidSemiSphere(int pu, int pv)
{
	igCreateSolidQuadricObject(pu, pv, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f);
}


/******************************************************************************************/
/* Crea un cono a partir de las ecuaciones de la supercuadrica                            */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidCone(int pu, int pv)
{
	igCreateSolidQuadricObject(pu, pv, 1.0f, 0.5f, 1.0f, 2.0f, 1.0f);
}


/******************************************************************************************/
/* Dibuja un cono de arista unidad y centrado en el origen                                */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidCube(void)
{
	float vertices[8][3] = { {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, 0.5f},
							{0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, 0.5f} };

	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3fv(vertices[4]);
	glVertex3fv(vertices[0]);
	glVertex3fv(vertices[5]);
	glVertex3fv(vertices[1]);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3fv(vertices[6]);
	glVertex3fv(vertices[2]);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3fv(vertices[7]);
	glVertex3fv(vertices[3]);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3fv(vertices[4]);
	glVertex3fv(vertices[0]);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3fv(vertices[1]);
	glVertex3fv(vertices[0]);
	glVertex3fv(vertices[2]);
	glVertex3fv(vertices[3]);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3fv(vertices[4]);
	glVertex3fv(vertices[5]);
	glVertex3fv(vertices[7]);
	glVertex3fv(vertices[6]);
	glEnd();
}