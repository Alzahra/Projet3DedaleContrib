/* Auteur: Nicolas JANEY                  */
/* nicolas.janey@univ-fcomte.fr           */
/* Septembre 2005                         */
/* Module de mathematiques matricielles   */

#ifndef MODULEMATRICEVECTEUR
#define MODULEMATRICEVECTEUR

typedef float vecteur[4];
typedef float matrice[4][4];

void toIdentite(matrice a) ;
void toTranslation(matrice a,float dx,float dy,float dz) ;
void toRotationX(matrice m,float a) ;
void toRotationY(matrice m,float a) ;
void toRotationZ(matrice m,float a) ;
void toRotation(matrice m,float a,float x,float y,float z) ;
void toScale(matrice a,float rx,float ry,float rz) ;
void produitMatriceMatrice(matrice a,matrice b,matrice r) ;
void produitMatriceVecteur(matrice m,vecteur v,vecteur r) ;
void affichageMatrice(matrice a) ;
float distance(vecteur p1,vecteur p2) ;
void calculVecteurNorme(vecteur pi,vecteur pf,vecteur n) ;
int normalise(vecteur n) ;
void calculVecteur(vecteur pi,vecteur pf,vecteur n) ;
float produitScalaire(vecteur d1,vecteur d2) ;
void produitVectoriel(vecteur v1,vecteur v2,vecteur n) ;

#endif
