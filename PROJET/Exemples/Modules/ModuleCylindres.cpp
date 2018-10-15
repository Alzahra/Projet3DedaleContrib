/* Auteur: Nicolas JANEY                  */
/* nicolas.janey@univ-fcomte.fr           */
/* Septembre 2005                         */
/* Module de dessin des cylindres         */

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "ModuleCylindres.h"

void wireCylindre(float r,float h,int n,int m) {
  glPushMatrix();
  glRotatef(90.0F,1.0F,0.0F,0.0F);
  glTranslatef(0.0F,0.0F,-h/2);
  GLUquadricObj *qobj = gluNewQuadric();
  gluQuadricDrawStyle(qobj,GLU_LINE);
  gluCylinder(qobj,r,r,h,n,m);
  gluDeleteQuadric(qobj);  
  glPopMatrix();
}

void solidCylindre(float r,float h,int n,int m) {
  glPushMatrix();
  glRotatef(90.0F,1.0F,0.0F,0.0F);
  glTranslatef(0.0F,0.0F,-h/2);
  GLUquadricObj *qobj = gluNewQuadric();
  gluQuadricDrawStyle(qobj,GLU_FILL);
  gluCylinder(qobj,r,r,h,n,m);
  gluDeleteQuadric(qobj);  
  glPopMatrix();
}

void wireCylindre(float r,float h,int n,int m,int axe) {
  glPushMatrix();
  switch (axe) {
    case X : glRotatef(90.0F,0.0F,1.0F,0.0F);
             break;
    case Y : glRotatef(90.0F,1.0F,0.0F,0.0F);
             break; }
  glTranslatef(0.0F,0.0F,-h/2);
  GLUquadricObj *qobj = gluNewQuadric();
  gluQuadricDrawStyle(qobj,GLU_LINE);
  gluCylinder(qobj,r,r,h,n,m);
  gluDeleteQuadric(qobj);  
  glPopMatrix();
}

void solidCylindre(float r,float h,int n,int m,int axe) {
  glPushMatrix();
  switch (axe) {
    case X : glRotatef(90.0F,0.0F,1.0F,0.0F);
             break;
    case Y : glRotatef(90.0F,1.0F,0.0F,0.0F);
             break; }
  glTranslatef(0.0F,0.0F,-h/2);
  GLUquadricObj *qobj = gluNewQuadric();
  gluQuadricDrawStyle(qobj,GLU_FILL);
  gluCylinder(qobj,r,r,h,n,m);
  gluDeleteQuadric(qobj);  
  glPopMatrix();
}

void myWireCylinder(float r,float h,int n,int m) {
  wireCylindre(r,h,n,m);
}

void mySolidCylinder(float r,float h,int n,int m) {
  solidCylindre(r,h,n,m);
}

void myWireCylinder(float r,float h,int n) {
  wireCylindre(r,h,n,1);
}

void mySolidCylinder(float r,float h,int n) {
  solidCylindre(r,h,n,1);
}

