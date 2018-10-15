/* Auteur: Nicolas JANEY                  */
/* nicolas.janey@univ-fcomte.fr           */
/* Septembre 2005                         */
/* Module de dessin de fleches            */
/* en filaire et en volume                */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>

static void cylindre(double h,double r,int n) {
  int i;
  double *cs =(double *) calloc(n+1,sizeof(double)) ;
  double *sn =(double *) calloc(n+1,sizeof(double)) ;
  double *ncs =(double *) calloc(n+1,sizeof(double)) ;
  double *nsn =(double *) calloc(n+1,sizeof(double)) ;
  cs[0] = cs[n] = r ;
  sn[0] = sn[n] = 0.0 ;
  ncs[0] = ncs[n] = 1.0 ;
  nsn[0] = nsn[n] = 0.0 ;
  for ( i = 1 ; i < n ; i++ ) {
    double a = 3.14159/n*2*i ;
    ncs[i] = cos(a) ;
    nsn[i] = sin(a) ;
    cs[i] = r*ncs[i] ;
    sn[i] = r*nsn[i] ; }
  glBegin(GL_POLYGON) ;
  glNormal3f(0.0,1.0,0.0) ;
  for ( i = 0 ; i < n ; i++ ) {
    glVertex3d(cs[i],h/2,sn[i]); }
  glEnd() ;
  glBegin(GL_POLYGON) ;
  glNormal3f(0.0,-1.0,0.0) ;
  for ( i = 0 ; i < n ; i++ ) {
    glVertex3d(cs[i],-h/2,sn[i]); }
  glEnd() ;
  glBegin(GL_QUADS) ;
  for ( i = 0 ; i < n ; i++ ) {
    glNormal3d(ncs[i],0.0,nsn[i]) ;
    glVertex3d(cs[i],h/2,sn[i]);
    glNormal3d(ncs[i+1],0.0,nsn[i+1]) ;
    glVertex3d(cs[i+1],h/2,sn[i+1]);
    glVertex3d(cs[i+1],-h/2,sn[i+1]);
    glNormal3d(ncs[i],0.0,nsn[i]) ;
    glVertex3d(cs[i],-h/2,sn[i]); }
  glEnd() ;
  free(sn) ;
  free(cs) ;
  free(nsn) ;
  free(ncs) ;
}

static void cone(double h,double r,int n) {
  int i;
  double *cs =(double *) calloc(n+1,sizeof(double)) ;
  double *sn =(double *) calloc(n+1,sizeof(double)) ;
  double *ncs =(double *) calloc(n+1,sizeof(double)) ;
  double *nsn =(double *) calloc(n+1,sizeof(double)) ;
  cs[0] = cs[n] = r ;
  sn[0] = sn[n] = 0.0 ;
  ncs[0] = ncs[n] = 1.0 ;
  nsn[0] = nsn[n] = 0.0 ;
  for ( i = 1 ; i < n ; i++ ) {
    double a = 3.14159/n*2*i ;
    ncs[i] = cos(a) ;
    nsn[i] = sin(a) ;
    cs[i] = r*ncs[i] ;
    sn[i] = r*nsn[i] ; }
  glBegin(GL_POLYGON) ;
  glNormal3f(0.0,-1.0,0.0) ;
  for ( i = 0 ; i < n ; i++ ) {
    glVertex3d(cs[i],-h/2,sn[i]); }
  glEnd() ;
  glBegin(GL_QUADS) ;
  for ( i = 0 ; i < n ; i++ ) {
    glNormal3d(ncs[i],0.0,nsn[i]) ;
    glVertex3d(0,h/2,0);
    glNormal3d(ncs[i+1],0.0,nsn[i+1]) ;
    glVertex3d(0,h/2,0);
    glVertex3d(cs[i+1],-h/2,sn[i+1]);
    glNormal3d(ncs[i],0.0,nsn[i]) ;
    glVertex3d(cs[i],-h/2,sn[i]); }
  glEnd() ;
  free(sn) ;
  free(cs) ;
  free(nsn) ;
  free(ncs) ;
}

void flecheEnFilaire(float dx,float dy,float dz,float cr,float cl) {
  glPushMatrix();
  glBegin(GL_LINES);
  glVertex3f(0.0F,0.0F,0.0F);
  glVertex3f(dx,dy,dz);
  glEnd();
  glPushMatrix();
  double d = pow((double) (dx*dx+dy*dy+dz*dz),0.5);
  dx /= d; 
  dy /= d; 
  dz /= d; 
  double a = acos(dz) * 360 / 3.14159;
  glRotatef(a/2,-dy,dx,0);
  glTranslatef(0.0F,0.0F,(float) d-cl);
  glutSolidCone(cr,cl,10,10);
  glPopMatrix();
  glPopMatrix();
}

static int estEgal(float a,float b) {
  return(fabs(a-b) < 0.00001) ;
}

void flecheEnVolume(float dx,float dy,float dz,float cr,float cl,float ct) {
  glPushMatrix();
  glBegin(GL_LINES);
  glVertex3f(0.0F,0.0F,0.0F);
  glVertex3f(dx,dy,dz);
  glEnd();
  double d = pow((double) (dx*dx+dy*dy+dz*dz),0.5);
  glPushMatrix();
  dx /= d; 
  dy /= d; 
  dz /= d;
  if ( estEgal(dz,-1.0F) )
    glRotatef(180.0F,1.0F,0.0F,0.0F);
    else
    if ( !estEgal(dz,1.0F) ) {
      double a = acos(dz) * 180 / 3.14159;
      glRotatef(a,-dy,dx,0); }
  glTranslatef(0.0F,0.0F,(float) (d-cl)/2);
  glPushMatrix();
  glRotatef(90.0F,1.0F,0.0F,0.0F);
  cylindre(d-cl,ct,36);
  glPopMatrix();
  glTranslatef(0.0F,0.0F,(float) d/2);
  glPushMatrix();
  glRotatef(90.0F,1.0F,0.0F,0.0F);
  cone(cl,cr,36);
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();
}

void segmentEnVolume(float dx,float dy,float dz,float ct) {
  glPushMatrix();
  glBegin(GL_LINES);
  glVertex3f(0.0F,0.0F,0.0F);
  glVertex3f(dx,dy,dz);
  glEnd();
  double d = pow((double) (dx*dx+dy*dy+dz*dz),0.5);
  glPushMatrix();
  dx /= d; 
  dy /= d; 
  dz /= d;
  if ( estEgal(dz,-1.0F) )
    glRotatef(180.0F,1.0F,0.0F,0.0F);
    else
    if ( !estEgal(dz,1.0F) ) {
      double a = acos(dz) * 180 / 3.14159;
      glRotatef(a,-dy,dx,0); }
  glTranslatef(0.0F,0.0F,(float) (d/2));
  glPushMatrix();
  glRotatef(90.0F,1.0F,0.0F,0.0F);
  cylindre(d,ct,36);
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();
}

void biFlecheEnVolume(float dx,float dy,float dz,float cr,float cl,float ct) {
  glPushMatrix();
  glTranslatef(dx/2.0F,dy/2.0F,dz/2.0F);
  flecheEnVolume(dx/2.0F,dy/2.0F,dz/2.0F,cr,cl,ct);
  flecheEnVolume(-dx/2.0F,-dy/2.0F,-dz/2.0F,cr,cl,ct);
  glPopMatrix();
}

void coneOuverture(float dx,float dy,float dz,float a) {
  double d = pow((double) (dx*dx+dy*dy+dz*dz),0.5);
  glPushMatrix();
  dx /= d; 
  dy /= d; 
  dz /= d;
  if ( estEgal(dz,-1.0F) )
    glRotatef(180.0F,1.0F,0.0F,0.0F);
    else
    if ( !estEgal(dz,1.0F) ) {
      double a = acos(dz) * 180 / 3.14159;
      glRotatef(a,-dy,dx,0); }
  glPushMatrix();
  glRotatef(90.0F,1.0F,0.0F,0.0F);
  glRotatef(180.0F,0.0F,0.0F,1.0F);
  glTranslatef(0.0F,-d/2.0F,0.0F);
  cone(d,tan(a/180.0*3.14159F)*d,120);
  glPopMatrix();
  glPopMatrix();
}
