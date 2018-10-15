/* Auteur: Nicolas JANEY                  */
/* nicolas.janey@univ-fcomte.fr           */
/* Septembre 2005                         */
/* Module de dessin de :                  */
/*  - fleches en filaire et en volume     */
/*  - segment en volume                   */
/*  - cone                                */

#ifndef MODULEFLECHE
#define MODULEFLECHE

void flecheEnFilaire(float dx,float dy,float dz,float cr,float cl) ;
void flecheEnVolume(float dx,float dy,float dz,float cr,float cl,float ct) ;
void biFlecheEnVolume(float dx,float dy,float dz,float cr,float cl,float ct) ;
void coneOuverture(float dx,float dy,float dz,float ang) ;
void segmentEnVolume(float dx,float dy,float dz,float ct) ;

#endif
