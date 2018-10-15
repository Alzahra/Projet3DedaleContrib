/* Auteur: Nicolas JANEY                  */
/* nicolas.janey@univ-fcomte.fr           */
/* Septembre 2005                         */
/* Module de dessin des cubes             */

#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "ModuleCubes.h"

static void cube(float c,int n) {
  float d = c/n; 
  c /= 2.0F;
  glPushMatrix();
  glBegin(GL_QUADS);
  for ( int i = 0 ; i < n ; i++ )
    for ( int j = 0 ; j < n ; j++ ) {
      float si = -c+i*d;
      float sf = si+d;
      float ti = -c+j*d;
      float tf = ti+d;
      { glNormal3f(1.0F,0.0F,0.0F);
        glVertex3f(c,sf,ti);
        glVertex3f(c,sf,tf);
        glVertex3f(c,si,tf);
        glVertex3f(c,si,ti); }
      { glNormal3f(-1.0F,0.0F,0.0F);
        glVertex3f(-c,si,ti);
        glVertex3f(-c,si,tf);
        glVertex3f(-c,sf,tf);
        glVertex3f(-c,sf,ti); }
      { glNormal3f(0.0F,1.0F,0.0F);
        glVertex3f(si,c,ti);
        glVertex3f(si,c,tf);
        glVertex3f(sf,c,tf);
        glVertex3f(sf,c,ti); }
      { glNormal3f(0.0F,-1.0F,0.0F);
        glVertex3f(sf,-c,ti);
        glVertex3f(sf,-c,tf);
        glVertex3f(si,-c,tf);
        glVertex3f(si,-c,ti); }
      { glNormal3f(0.0F,0.0F,1.0F);
        glVertex3f(sf,ti,c);
        glVertex3f(sf,tf,c);
        glVertex3f(si,tf,c);
        glVertex3f(si,ti,c); }
      { glNormal3f(0.0F,0.0F,-1.0F);
        glVertex3f(si,ti,-c);
        glVertex3f(si,tf,-c);
        glVertex3f(sf,tf,-c);
        glVertex3f(sf,ti,-c); } }
  glEnd();
  glPopMatrix();
}

void myWireCube(float c,int n) {
  int mode[2];
  glGetIntegerv(GL_POLYGON_MODE,mode);
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  cube(c,n);
  glPolygonMode(GL_FRONT,mode[0]);
  glPolygonMode(GL_BACK,mode[1]);
}

void mySolidCube(float c,int n) {
  int mode[2];
  glGetIntegerv(GL_POLYGON_MODE,mode);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  cube(c,n);
  glPolygonMode(GL_FRONT,mode[0]);
  glPolygonMode(GL_BACK,mode[1]);
}

static void cube(float c) {
  c /= 2.0F;
  glPushMatrix();
  glBegin(GL_QUADS);
  { glNormal3f(0.0F,0.0F,-1.0F);
    glVertex3f(c,c,-c);
    glVertex3f(c,-c,-c);
    glVertex3f(-c,-c,-c);
    glVertex3f(-c,c,-c); }
  { glNormal3f(0.0F,0.0F,1.0F);
    glVertex3f(c,c,c);
    glVertex3f(-c,c,c);
    glVertex3f(-c,-c,c);
    glVertex3f(c,-c,c); }
  { glNormal3f(-1.0F,0.0F,0.0F);
    glVertex3f(-c,c,-c);
    glVertex3f(-c,-c,-c);
    glVertex3f(-c,-c,c);
    glVertex3f(-c,c,c); }
  { glNormal3f(1.0F,0.0F,0.0F);
    glVertex3f(c,c,c);
    glVertex3f(c,-c,c);
    glVertex3f(c,-c,-c);
    glVertex3f(c,c,-c); }
  { glNormal3f(0.0F,-1.0F,0.0F);
    glVertex3f(-c,-c,c);
    glVertex3f(-c,-c,-c);
    glVertex3f(c,-c,-c);
    glVertex3f(c,-c,c); }
  { glNormal3f(0.0F,1.0F,0.0F);
    glVertex3f(c,c,c);
    glVertex3f(c,c,-c);
    glVertex3f(-c,c,-c);
    glVertex3f(-c,c,c); }
  glEnd();
  glPopMatrix();
}

void myWireCube(float c) {
  int mode[2];
  glGetIntegerv(GL_POLYGON_MODE,mode);
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  cube(c);
  glPolygonMode(GL_FRONT,mode[0]);
  glPolygonMode(GL_BACK,mode[1]);
}

void mySolidCube(float c) {
  int mode[2];
  glGetIntegerv(GL_POLYGON_MODE,mode);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  cube(c);
  glPolygonMode(GL_FRONT,mode[0]);
  glPolygonMode(GL_BACK,mode[1]);
}
