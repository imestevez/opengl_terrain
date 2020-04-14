/*************************************************************************/
/*                                                                       */
/*   material.h												             */
/*   Rev. 2.0  01/01/2002   AUTORES: O. Belmonte, M. Chover, J. Ribelles */
/*                                                                       */
/*************************************************************************/


#ifndef MATERIAL_H
#define MATERIAL_H


/*********************** DECLARACION DE CONSTANTES ***********************/

#define anchoTextura 256
#define altoTextura  256
#define numTextura      3       

/***************** DECLARACION DE LA VARIABLES GLOBALES  *****************/

GLubyte textura[numTextura][anchoTextura][altoTextura][3];

/* Inicia OpenGL para poder definir las propiedades de los materiales */
void IniciaMaterial(void);

/* Define las propiedades del material cobre */
void Cobre (void);

/* Lee una imagen de textura en formato tga */
void leerTextura (char *fichero, int num);
void initTextura0(char *fichero);
void textura0(void);
void initTextura1(char *fichero);
void textura1(void);
void initTextura2(char *fichero);
void textura2(void);


#endif