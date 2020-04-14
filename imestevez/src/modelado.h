/*************************************************************************/
/*                                                                       */
/*   modelado.h                                                          */
/*   Rev. 3.0  01/09/2012   Universidad Jaume I de Castellón             */
/*                                                                       */
/*************************************************************************/

#ifndef MODELADO_H
#define MODELADO_H

#include "glut.h"
/* Identificadores de las display lists */
GLuint arco, arcos, suelo, escena, terreno;

/* Funciones de modelado */
/* Crea las distintas display lists */
void IniciaDisplayLists (void);

/* Dibuja la escena */
void DibujaEscena (void);

/* Crea una display list para un arco */
void CreaArco (void);

/* Crea una display list para todos los arcos */
void CreaArcos (void);

/* Crea una display list para el suelo */
void CreaSuelo (void);

/*  Crea una display list para toda la escena */
void CreaEscena(void);

void CreaTerreno(void);
void CreaCelda(int i, int j);
void PintaTerreno(int i, int j);
void ReseteaAlturas();
void CalculaMalla();
void CalcVectoresNormales();
#endif