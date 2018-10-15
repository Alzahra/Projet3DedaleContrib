/* Auteur: Nicolas JANEY                  */
/* nicolas.janey@univ-fcomte.fr           */
/* Septembre 2005                         */
/* Module de dessin des cylindres         */

#ifndef MODULECYLINDRE
#define MODULECYLINDRE

#define X 1
#define Y 2
#define Z 3

void wireCylindre(float r,float h,int n,int m);
void solidCylindre(float r,float h,int n,int m);
void wireCylindre(float r,float h,int n,int m,int axe);
void solidCylindre(float r,float h,int n,int m,int axe);
void myWireCylinder(float r,float h,int n,int m);
void mySolidCylinder(float r,float h,int n,int m);
void myWireCylinder(float r,float h,int n);
void mySolidCylinder(float r,float h,int n);

#endif
