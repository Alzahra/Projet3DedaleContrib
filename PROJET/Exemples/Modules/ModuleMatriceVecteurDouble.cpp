/* Auteur: Nicolas JANEY                  */
/* nicolas.janey@univ-fcomte.fr           */
/* Septembre 2005                         */
/* Module de mathematiques matricielles   */

#include <math.h>
#include <stdio.h>

#include "ModuleMatriceVecteurDouble.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

/* ************************************************** */

/* -------------------------------------------------- */
/* Initialisation a l'identite                        */
/* -------------------------------------------------- */
void toIdentite(matrice a) {
  for ( int i = 0 ; i < 4 ; i++ ) 
    for ( int j = 0 ; j < 4 ; j++ ) 
      a[i][j] = ( i == j) ? 1.0 : 0.0;
}
/* -------------------------------------------------- */
/* Initialisation a la translation (dx,dy,dz)         */
/* -------------------------------------------------- */
void toTranslation(matrice a,double dx,double dy,double dz) {
  toIdentite(a);
  a[0][3] = dx;
  a[1][3] = dy;
  a[2][3] = dz;
}
/* -------------------------------------------------- */
/* Initialisation a la rotation d'angle a             */
/* autour de Ox                                       */
/* -------------------------------------------------- */
void toRotationX(matrice m,double a) {
  toIdentite(m);
  double aa = a/180.0*M_PI;
  m[2][1] = sin(aa);
  m[1][2] = -m[2][1];
  m[1][1] = m[2][2] = cos(aa);
  }
/* -------------------------------------------------- */
/* Initialisation a la rotation d'angle a             */
/* autour de Oy                                       */
/* -------------------------------------------------- */
void toRotationY(matrice m,double a) {
  toIdentite(m);
  double aa = a/180.0*M_PI;
  m[0][2] = sin(aa);
  m[2][0] = -m[0][2];
  m[0][0] = m[2][2] = cos(aa);
}
/* -------------------------------------------------- */
/* Initialisation a la rotation d'angle a             */
/* autour de Oz                                       */
/* -------------------------------------------------- */
void toRotationZ(matrice m,double a) {
  toIdentite(m);
  double aa = a/180.0*M_PI;
  m[1][0] = sin(aa);
  m[0][1] = -m[1][0];
  m[1][1] = m[0][0] = cos(aa);
}
/* -------------------------------------------------- */
/* Initialisation a la rotation d'angle a             */
/* autour de Oz                                       */
/* -------------------------------------------------- */
void toRotation(matrice m,double a,double x,double y,double z) {
  toIdentite(m);
  vecteur v = { x,y,z };
  normalise(v);
  double aa = a/180.0*M_PI;
  double sn = sin(aa);
  double cs = cos(aa);
  m[0][0] = v[0]*v[0]+cs*(1-v[0]*v[0]);
  m[0][1] = v[0]*v[1]*(1-cs)-sn*v[2];
  m[0][2] = v[0]*v[2]*(1-cs)+sn*v[1];
  m[1][0] = v[0]*v[1]*(1-cs)+sn*v[2];
  m[1][1] = v[1]*v[1]+cs*(1-v[1]*v[1]);
  m[1][2] = v[1]*v[2]*(1-cs)-sn*v[0];
  m[2][0] = v[0]*v[2]*(1-cs)-sn*v[1];
  m[2][1] = v[1]*v[2]*(1-cs)+sn*v[0];
  m[2][2] = v[2]*v[2]+cs*(1-v[2]*v[2]);
}
/* -------------------------------------------------- */
/* Initialisation a la mise a l'echelle (rx,ry,rz)    */
/* -------------------------------------------------- */
void toScale(matrice a,double rx,double ry,double rz) {
  toIdentite(a);
  a[0][0] = rx;
  a[1][1] = ry;
  a[2][2] = rz;
}
/* -------------------------------------------------- */
/* Produit matrice matrice                            */
/* -------------------------------------------------- */
void produitMatriceMatrice(matrice a,matrice b,matrice r) {
  matrice rr;
  int i,j;
  for ( i = 0 ; i < 4 ; i++ ) 
    for ( j = 0 ; j < 4 ; j++ ) {
      rr[i][j] = 0.0;
      for ( int k = 0 ; k < 4 ; k++ ) {
        rr[i][j] += a[i][k]*b[k][j]; } }
  for ( i = 0 ; i < 4 ; i++ ) 
    for ( j = 0 ; j < 4 ; j++ )
      r[i][j] = rr[i][j];
}
/* -------------------------------------------------- */
/* Produit matrice vecteur                            */
/* -------------------------------------------------- */
void produitMatriceVecteur(matrice m,vecteur v,vecteur r) {
  vecteur rr;
  int i;
  for ( i = 0 ; i < 4 ; i++ ) {
    rr[i] = 0.0;
    for ( int j = 0 ; j < 4 ; j++ ) {
      rr[i] += m[i][j]*v[j]; } }
  for ( i = 0 ; i < 4 ; i++ ) {
    r[i] = rr[i]; }
}
/* -------------------------------------------------- */
/* Produit matrice matrice                            */
/* -------------------------------------------------- */
void affichageMatrice(matrice a) {
  int i,j;
  for ( i = 0 ; i < 4 ; i++ ) {
    for ( j = 0 ; j < 4 ; j++ )
      printf("%10lf",a[i][j]);
    printf("\n"); }
  printf("\n");
}
/* -------------------------------------------------- */
/* Calcul de la distance entre deux sommets           */
/* -------------------------------------------------- */
double distance(vecteur p1,vecteur p2) {
  double x = p1[0] - p2[0] ; 
  double y = p1[1] - p2[1] ; 
  double z = p1[2] - p2[2] ;
  double d2 = x*x + y*y + z*z ;
  return( pow(d2,0.5)) ;
} 
/* -------------------------------------------------- */
/* Calcul du vecteur norme colineaire a l'axe forme   */
/* par deux sommets                                   */
/* -------------------------------------------------- */
void calculVecteurNorme(vecteur pi,vecteur pf,vecteur n) {
  double x = pf[0] - pi[0] ; 
  double y = pf[1] - pi[1] ; 
  double z = pf[2] - pi[2] ;
  double d2 = distance(pi,pf) ;
  n[0] = (x / d2) ;
  n[1] = (y / d2) ;
  n[2] = (z / d2) ;
  n[3] = 0.0;
} 
/* -------------------------------------------------- */
/* Normalisation d'un vecteur                         */
/* -------------------------------------------------- */
int normalise(vecteur n) {
  double d2 = n[0]*n[0] + n[1]*n[1] + n[2]*n[2] ;
  d2 = pow(d2,0.5) ;
  if ( d2 == 0.0 )
    return(0);
  n[0] /= d2 ;
  n[1] /= d2 ;
  n[2] /= d2 ;
  return(1);
} 
/* -------------------------------------------------- */
/* Calcul du vecteur entre deux sommets               */
/* -------------------------------------------------- */
void calculVecteur(vecteur pi,vecteur pf,vecteur n) {
  n[0] = pf[0] - pi[0] ; 
  n[1] = pf[1] - pi[1] ; 
  n[2] = pf[2] - pi[2] ;
  n[3] = 0.0;
} 
/* -------------------------------------------------- */
/* Calcul du produit scalaire entre deux vecteurs     */
/* -------------------------------------------------- */
double produitScalaire(vecteur d1,vecteur d2) {
  return(d1[0]*d2[0] + d1[1]*d2[1] + d1[2]*d2[2]) ;
}
/* -------------------------------------------------- */
/* Calcul du produit vectoriel entre deux vecteurs    */
/* -------------------------------------------------- */
void produitVectoriel(vecteur v1,vecteur v2,vecteur n) {
  n[0] = v1[1]*v2[2] - v1[2]*v2[1];
  n[1] = v1[2]*v2[0] - v1[0]*v2[2];
  n[2] = v1[0]*v2[1] - v1[1]*v2[0];
  n[3] = 0.0;
}

/* ************************************************** */
