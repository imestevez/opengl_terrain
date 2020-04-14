/*************************************************************************/
/*                                                                       */
/*                 glig.h LIBRERIA DE MODELADO GEOMETRICO	             */
/*                                                                       */
/*   Rev. 3.0  01/09/2012   Universidad Jaume I de Castellón             */
/*                                                                       */
/*************************************************************************/



#ifndef GLIG_H
#define GLIG_H

/* Devuelve la coordenada x de un punto en R3 a partir de un punto (u,v) */
float xSuperQuadric(float u, float v, float R, float s1, float s2);

/* Devuelve la coordenada y de un punto en R3 a partir de un punto (u,v) */
float ySuperQuadric(float u, float v, float R, float s1, float s2);

/* Devuelve la coordenada z de un punto en R3 a partir de un punto (u,v) */
float zSuperQuadric(float u, float v, float R, float s1, float s2);

/* Calcula la variacion en x para un incremento de u, derivada de x con respecto de u */
float dxuSuperQuadric(float u, float v, float R, float s1, float s2);

/* Calcula la variacion en y para un incremento de u, derivada de y con respecto de u */
float dyuSuperQuadric(float u, float v, float R, float s1, float s2);

/* Calcula la variacion en z para un incremento de u, derivada de z con respecto de u */
float dzuSuperQuadric(float u, float v, float R, float s1, float s2);

/* Calcula la variacion en x para un incremento de v, derivada de x con respecto de v */
float dxvSuperQuadric(float u, float v, float R, float s1, float s2);

/* Calcula la variacion en y para un incremento de u, derivada de y con respecto de v */
float dyvSuperQuadric(float u, float v, float R, float s1, float s2);

/* Calcula la variacion en z para un incremento de u, derivada de z con respecto de v */
float dzvSuperQuadric(float u, float v, float R, float s1, float s2);

/* Calcula la componente x del vector normal a la supercuadrica en (u,v) */
float nxSuperQuadric(float u, float v, float R, float s1, float s2);

/* Calcula la componente y del vector normal a la supercuadrica en (u,v) */
float nySuperQuadric(float u, float v, float R, float s1, float s2);

/* Calcula la componente z del vector normal a la supercuadrica en (u,v) */
float nzSuperQuadric(float u, float v, float R, float s1, float s2);

//Crea un Objeto cuadrático a partir de los parámetros pasados
void igCreateQuadraticObject(int pu, int pv, float uMax, float vMax, float R, float s1, float s2);

void igWireSphere(int pu, int pv); /* s1 y s2 a 1 */
void igWireRulo(int pu, int pv); /* s1= 0.5, s2= 1 */
void igWireDado(int pu, int pv); /* s1= 0.5, s2 =0.5 */
void igWireSemiSphere(int pu, int pv); /* s1 y s2 a 1, uMax= 1, vMax= 0.5 */

//Esta primitiva debe tener de lado 1 y estar centrada en el origen de coordenadas. 
void igWireCube(void);

/* s1= 2.0, s2= 1.0, uMax= 1.0, vMax= 0.5 */
void igWireCone(int pu, int pv);

/* Crea una esfera a partir de las ecuaciones de la supercuadrica */
void igSolidSphere(int pu, int pv);

/* Crea un rulo a partir de las ecuaciones de la supercuadrica */
void igSolidRulo(int pu, int pv);

/* Crea un dado a partir de las ecuaciones de la supercuadrica */
void igSolidDado(int pu, int pv);

/* Crea una semiesfera a partir de las ecuaciones de la supercuadrica */
void igSolidSemiSphere(int pu, int pv);

/* Crea un cono a partir de las ecuaciones de la supercuadrica */
void igSolidCone(int pu, int pv);

/* Dibuja un cuadrado de arista unidad y centrado en el origen */
void igSolidCube(void);

#endif