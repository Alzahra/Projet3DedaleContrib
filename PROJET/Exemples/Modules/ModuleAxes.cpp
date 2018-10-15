/* Auteur: Nicolas JANEY                  */
/* nicolas.janey@univ-fcomte.fr           */
/* Septembre 2005                         */
/* Module de dessin des axes              */
/* du repere courant                      */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "ModuleAxes.h"
#include "ModuleFleche.h"
#include "ModuleCouleurs.h"
#include "ModuleManipulateur.h"
#include "ModuleMenus.h"
#include "ModuleReshape.h"
#include "ModuleFont.h"

static int maille = 0 ;

struct repere repereIdentite = { { 0.0F,0.0F,0.0F,1.0F },
                                 { 1.0F,0.0F,0.0F,0.0F },
                                 { 0.0F,1.0F,0.0F,0.0F },
                                 { 0.0F,0.0F,1.0F,0.0F } } ;

void switchAffichagePlan(void) {
  maille = !maille;
}

void axes() {
  int l = glIsEnabled(GL_LIGHTING);
  glDisable(GL_LIGHTING);
  float c[4];
  glGetFloatv(GL_CURRENT_COLOR,c);
  glPushMatrix() ;
  glColor4fv(couleurJaune()) ;
  glBegin(GL_LINES) ;
  glVertex3f(0.0F,0.0F,0.0F) ;
  glVertex3f(1.0F,0.0F,0.0F) ;
  glEnd() ;
  placeFontCursor(1.05F,0.05F,0.05F);
  simpleBitmapOutput('x');
  glColor4fv(couleurCyan()) ;
  glBegin(GL_LINES) ;
  glVertex3f(0.0F,0.0F,0.0F) ;
  glVertex3f(0.0F,1.0F,0.0F) ;
  glEnd() ;
  placeFontCursor(0.05F,1.05F,0.05F);
  simpleBitmapOutput('y');
  glColor4fv(couleurMagenta()) ;
  glBegin(GL_LINES) ;
  glVertex3f(0.0F,0.0F,0.0F) ;
  glVertex3f(0.0F,0.0F,1.0F) ;
  glEnd() ;
  placeFontCursor(0.05F,0.05F,1.05F);
  simpleBitmapOutput('z');
  if ( maille ) {
    glColor4fv(couleurGrisMoyen()) ;
    for ( int i = -100 ; i < 100 ; i++ ) {
      glBegin(GL_LINES) ;
      glVertex3f((float) i,200.0F,0.0F) ;
      glVertex3f((float) i,-200.0F,0.0F) ;
      glEnd() ;
      glBegin(GL_LINES) ;
      glVertex3f(200.0F,(float) i,0.0F) ;
      glVertex3f(-200.0F,(float) i,0.0F) ;
      glEnd() ; } }
  glPopMatrix() ;
  if ( l )
    glEnable(GL_LIGHTING);
  glColor4fv(c);
}

void axes(struct repere *r) {
  int l = glIsEnabled(GL_LIGHTING);
  glEnable(GL_LIGHTING);
  float c[4];
  glGetFloatv(GL_CURRENT_COLOR,c);
  glPushMatrix() ;
  glTranslatef(r->o[0],r->o[1],r->o[2]);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,couleurBlanc()) ;
  glutSolidSphere(0.05F,36,36);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,couleurJaune()) ;
  flecheEnVolume(r->axex[0],r->axex[1],r->axex[2],0.05F,0.25F,0.02F);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,couleurCyan()) ;
  flecheEnVolume(r->axey[0],r->axey[1],r->axey[2],0.05F,0.25F,0.02F);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,couleurMagenta()) ;
  flecheEnVolume(r->axez[0],r->axez[1],r->axez[2],0.05F,0.25F,0.02F);
  glDisable(GL_LIGHTING);
  glColor4fv(couleurJaune()) ;
  placeFontCursor(r->axex[0]+0.05F,r->axex[1]+0.05F,r->axex[2]+0.05F);
  simpleBitmapOutput("x");
  glColor4fv(couleurCyan()) ;
  placeFontCursor(r->axey[0]+0.05F,r->axey[1]+0.05F,r->axey[2]+0.05F);
  simpleBitmapOutput("y");
  glColor4fv(couleurMagenta()) ;
  placeFontCursor(r->axez[0]+0.05F,r->axez[1]+0.05F,r->axez[2]+0.05F);
  simpleBitmapOutput("z");
  glPopMatrix() ;
  if ( l )
    glEnable(GL_LIGHTING);
  glColor4fv(c);
}
