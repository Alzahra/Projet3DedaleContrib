/* Auteur: Nicolas JANEY                  */
/* nicolas.janey@univ-fcomte.fr           */
/* Septembre 2005                         */
/* Module de dessin d'arc                 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "ModuleMatriceVecteur.h"

float parametres(vecteur n,vecteur l,vecteur axe1) {
  vecteur n1;
  n1[0] = n[0];
  n1[1] = n[1];
  n1[2] = n[2]; 
  normalise(n1);
  vecteur l1;
  l1[0] = l[0];
  l1[1] = l[1];
  l1[2] = l[2]; 
  normalise(l1);
  float a1 = acos(produitScalaire(n1,l1))*180.0F/3.14159F;
  produitVectoriel(n1,l1,axe1);
  return(a1);
}

void traceAngleSurN(vecteur n,vecteur l,int np,float f,int t) {
  vecteur axe1;
  float a1 = parametres(n,l,axe1);
  if ( t )
    glBegin(GL_LINE_STRIP);
    else
    glBegin(GL_POINTS);
  vecteur nn = { n[0]*f,n[1]*f,n[2]*f };
  for ( int i = 0 ; i < np+1 ; i++ ) {
    vecteur p;
    matrice m;
    toRotation(m,a1*i/np,axe1[0],axe1[1],axe1[2]);
    produitMatriceVecteur(m,nn,p);
    p[0] += n[0];
    p[1] += n[1];
    p[2] += n[2];
    glVertex3fv(p); }
  glEnd();
}

void positionIntermediaireSurN(vecteur n,vecteur l,float f,vecteur p) {
  vecteur axe1;
  float a1 = parametres(n,l,axe1);
  vecteur nn = { n[0]*f,n[1]*f,n[2]*f };
  matrice m;
  toRotation(m,a1/2.0F,axe1[0],axe1[1],axe1[2]);
  produitMatriceVecteur(m,nn,p);
  p[0] += n[0];
  p[1] += n[1];
  p[2] += n[2];
}

void traceAngle(vecteur n,vecteur l,int np,float f,int t) {
  vecteur axe1;
  float a1 = parametres(n,l,axe1);
  if ( t )
    glBegin(GL_LINE_STRIP);
    else
    glBegin(GL_POINTS);
  vecteur nn = { n[0]*f,n[1]*f,n[2]*f };
  for ( int i = 0 ; i < np+1 ; i++ ) {
    vecteur p;
    matrice m;
    toRotation(m,a1*i/np,axe1[0],axe1[1],axe1[2]);
    produitMatriceVecteur(m,nn,p);
    glVertex3fv(p); }
  glEnd();
}

void traceAngleFleche(vecteur n,vecteur l,int np,float f,int t,int tf,float af,float lf) {
  vecteur axe1;
  float a1 = parametres(n,l,axe1);
  if ( t )
    glBegin(GL_LINE_STRIP);
    else
    glBegin(GL_POINTS);
  vecteur nn = { n[0]*f,n[1]*f,n[2]*f };
  for ( int i = 0 ; i < np+1 ; i++ ) {
    vecteur p;
    matrice m;
    toRotation(m,a1*(float) i/np,axe1[0],axe1[1],axe1[2]);
    produitMatriceVecteur(m,nn,p);
    glVertex3fv(p); }
  glEnd();
  if ( tf ) {
    vecteur nf1 = { n[0]*(f+lf),n[1]*(f+lf),n[2]*(f+lf) };
    vecteur nf2 = { n[0]*(f-lf),n[1]*(f-lf),n[2]*(f-lf) };
    vecteur pf;
    vecteur pf1;
    vecteur pf2;
    matrice m;
    if ( ( tf == 2 ) || ( tf == 3 ) ) {
      toRotation(m,a1,axe1[0],axe1[1],axe1[2]);
      produitMatriceVecteur(m,nn,pf);
      toRotation(m,a1-af,axe1[0],axe1[1],axe1[2]);
      produitMatriceVecteur(m,nf1,pf1);
      produitMatriceVecteur(m,nf2,pf2);
      glBegin(GL_LINES);
      glVertex3fv(pf);
      glVertex3fv(pf1);
      glVertex3fv(pf);
      glVertex3fv(pf2);
      glEnd(); }
    if ( ( tf == 1 ) || ( tf == 3 ) ) {
      pf[0] = nn[0];
      pf[1] = nn[1];
      pf[2] = nn[2];
      toRotation(m,af,axe1[0],axe1[1],axe1[2]);
      produitMatriceVecteur(m,nf1,pf1);
      produitMatriceVecteur(m,nf2,pf2);
      glBegin(GL_LINES);
      glVertex3fv(pf);
      glVertex3fv(pf1);
      glVertex3fv(pf);
      glVertex3fv(pf2);
      glEnd(); } }
}

void positionIntermediaire(vecteur n,vecteur l,float f,vecteur p) {
  vecteur axe1;
  float a1 = parametres(n,l,axe1);
  vecteur nn = { n[0]*f,n[1]*f,n[2]*f };
  matrice m;
  toRotation(m,a1/2.0F,axe1[0],axe1[1],axe1[2]);
  produitMatriceVecteur(m,nn,p);
}

void traceAngle(vecteur n,vecteur l,vecteur pp,int np,float f,int t) {
  vecteur axe1;
  float a1 = parametres(n,l,axe1);
  if ( t )
    glBegin(GL_LINE_STRIP);
    else
    glBegin(GL_POINTS);
  vecteur nn = { n[0]*f,n[1]*f,n[2]*f };
  for ( int i = 0 ; i < np+1 ; i++ ) {
    vecteur p;
    matrice m;
    toRotation(m,a1*i/np,axe1[0],axe1[1],axe1[2]);
    produitMatriceVecteur(m,nn,p);
    p[0] += pp[0];
    p[1] += pp[1];
    p[2] += pp[2];
    glVertex3fv(p); }
  glEnd();
}

void positionIntermediaire(vecteur n,vecteur l,vecteur pp,float f,vecteur p) {
  vecteur axe1;
  float a1 = parametres(n,l,axe1);
  produitVectoriel(n,l,axe1);
  vecteur nn = { n[0]*f,n[1]*f,n[2]*f };
  matrice m;
  toRotation(m,a1/2.0F,axe1[0],axe1[1],axe1[2]);
  produitMatriceVecteur(m,nn,p);
  p[0] += pp[0];
  p[1] += pp[1];
  p[2] += pp[2];
}
