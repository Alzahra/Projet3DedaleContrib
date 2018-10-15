/* Auteur: Nicolas JANEY                  */
/* nicolas.janey@univ-fcomte.fr           */
/* Septembre 2005                         */
/* Module de dessin d'arc                 */

#ifndef MODULEDESSINARC
#define MODULEDESSINARC

#include "ModuleMatriceVecteur.h"

void traceAngle(vecteur n,vecteur l,int np,float f,int t) ;
void traceAngleFleche(vecteur n,vecteur l,int np,float f,int t,int tf,float af,float lf) ;
void positionIntermediaire(vecteur n,vecteur l,float f,vecteur p) ;
void traceAngle(vecteur n,vecteur l,vecteur pp,int np,float f,int t) ;
void positionIntermediaire(vecteur n,vecteur l,vecteur pp,float f,vecteur p) ;
void traceAngleSurN(vecteur n,vecteur l,int np,float f,int t) ;
void positionIntermediaireSurN(vecteur n,vecteur l,float f,vecteur p) ;

#endif
