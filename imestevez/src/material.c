/*************************************************************************/
/*                                                                       */
/*   material.c                                                          */
/*   Rev. 2.0  01/01/2002   AUTORES: O. Belmonte, M. Chover, J. Ribelles */
/*                                                                       */
/*************************************************************************/

/***************** INCLUDES DE LAS LIBRERIAS NECESARIAS ******************/

#include <stdio.h>
#include "glut.h"
#include "material.h"


/********************** RUTINA DE INICIO **************************************************/
/******************************************************************************************/
/* Inicia OpenGL para poder definir las propiedades de los materiales                     */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void IniciaMaterial(void){
	/* Se modificara las propiedades de color de material ambiente y difusa */
	glColorMaterial(GL_FRONT,GL_DIFFUSE);

	/* Se permite el cambio de la propiedad de material con glColor */
	glEnable(GL_COLOR_MATERIAL);
}

/*********************** DEFINICION DE MATERIALES *****************************************/
/******************************************************************************************/
/* Define las propiedades del material cobre                                              */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void Cobre (void){
//	glColor3f(1,1,1);
}


/*********************** ESPECIFICACIÓN DE TEXTURAS****************************************/
/******************************************************************************************/
/* Lee una imagen de textura en formato tga                                               */
/* Parametros --> char *fichero : Cadena de caracteres con el nombre del fichero          */
/*				  int num: Numero que identifica la textura                               */
/* Salido --> Ninguna                                                                     */
/******************************************************************************************/
void leerTextura (char *fichero, int num){
	int   i, j;
	char  r, g, b, c;
	FILE  *tga;

	/* Apertura del fichero TGA */
	if ((tga = fopen(fichero, "rb")) == NULL)
		printf ("Error abriendo el fichero: %s\n", fichero);
	else	{
		/* Lee los 18 primeros caracteres de la cabecera */
		for (j=1; j<=18; j++)
			fscanf (tga, "%c", &c);

		/* Lee la imagen */
		for (j=altoTextura-1; j>=0; j--){
			for (i=anchoTextura-1; i>=0; i--){
				fscanf(tga, "%c%c%c", &b, &g, &r); 
				textura[num][j][i][0] = (GLubyte)r;
				textura[num][j][i][1] = (GLubyte)g;
				textura[num][j][i][2] = (GLubyte)b;
			}
		}
		fclose(tga);   /* Cierre del fichero TGA */
	}
}

/*********************** RUTINA DE CARGA Y ACTIVACION DE TEXTURAS *************************/
/******************************************************************************************/
/******************************************************************************************/
void initTextura0(char *fichero){
	leerTextura (fichero,0);
}


/******************************************************************************************/
/******************************************************************************************/
void textura0(void){
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
	glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[0]); 
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	glEnable (GL_TEXTURE_2D);

}


/******************************************************************************************/
/******************************************************************************************/
void initTextura1(char *fichero){ 
	leerTextura (fichero,1);
}


/******************************************************************************************/
/******************************************************************************************/
void textura1(void){ 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
	glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[1]); 
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	glEnable (GL_TEXTURE_2D);

}


/******************************************************************************************/
/******************************************************************************************/
void initTextura2(char *fichero){
	leerTextura (fichero,2);

}


/******************************************************************************************/
/******************************************************************************************/
void textura2(void){ 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
	glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[2]); 
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	glEnable (GL_TEXTURE_2D);
	//glDisable(GL_TEXTURE_2D);
}