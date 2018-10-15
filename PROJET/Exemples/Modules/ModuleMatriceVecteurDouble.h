/* Auteur: Nicolas JANEY                  */
/* nicolas.janey@univ-fcomte.fr           */
/* Septembre 2005                         */
/* Module de mathematiques matricielles   */

#ifndef MODULEMATRICEVECTEUR
#define MODULEMATRICEVECTEUR

typedef double vecteur[4];
typedef double matrice[4][4];

void toIdentite(matrice a) ;
void toTranslation(matrice a,double dx,double dy,double dz) ;
void toRotationX(matrice m,double a) ;
void toRotationY(matrice m,double a) ;
void toRotationZ(matrice m,double a) ;
void toRotation(matrice m,double a,double x,double y,double z) ;
void toScale(matrice a,double rx,double ry,double rz) ;
void produitMatriceMatrice(matrice a,matrice b,matrice r) ;
void produitMatriceVecteur(matrice m,vecteur v,vecteur r) ;
void affichageMatrice(matrice a) ;
double distance(vecteur p1,vecteur p2) ;
void calculVecteurNorme(vecteur pi,vecteur pf,vecteur n) ;
int normalise(vecteur n) ;
void calculVecteur(vecteur pi,vecteur pf,vecteur n) ;
double produitScalaire(vecteur d1,vecteur d2) ;
void produitVectoriel(vecteur v1,vecteur v2,vecteur n) ;

#endif
