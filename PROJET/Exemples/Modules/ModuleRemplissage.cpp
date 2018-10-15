/* Auteur: Nicolas JANEY            */
/* nicolas.janey@univ-fcomte.fr     */
/* Septembre 2005                   */
/* Remplissage d'une facette 2D     */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ModuleRemplissage.h"

void ligne(int xi,int yi,int xf,int yf,int *px,int ymax) {
  int i,cumul ;
  int x = xi ;
  int y = yi ;
  int dx = xf - xi ;
  int dy = yf - yi ;
  int xinc = ( dx > 0 ) ? 1 : -1 ;
  int yinc = ( dy > 0 ) ? 1 : -1 ;
  dx = abs(dx) ;
  dy = abs(dy) ;
  if ( ( y >= 0 ) && ( y < ymax ) )
    px[y] = x ;
  if ( dx > dy ) {
    cumul = dx / 2 ;
    for ( i = 1 ; i <= dx ; i++ ) {
      x += xinc ;
      cumul += dy ;
      if (cumul >= dx) {
        cumul -= dx ;
        y += yinc ; }
      if ( ( y >= 0 ) && ( y < ymax ) )
        px[y] = x ; } }
    else {
    cumul = dy / 2 ;
    for ( i = 1 ; i <= dy ; i++ ) {
      y += yinc ;
      cumul += dx ;
      if ( cumul >= dy ) {
        cumul -= dy ;
        x += xinc ; }
      if ( ( y >= 0 ) && ( y < ymax ) )
        px[y] = x ; } }
}

void ligneCote(int xi,int yi,int xf,int yf,int *px,int ymax) {
  if ( xi > xf )
    ligne(xf,yf,xi,yi,px,ymax) ;
    else
    ligne(xi,yi,xf,yf,px,ymax) ;
}

void Pixel(int x,int y,bitmap *b,int c) {
  if ( ( x >= 0 ) && ( x < b->tx ) )
    b->p[y][x] = c ;
}

void LigneDiscrete(int y,int x1,int x2,int c,bitmap *b) {
  if ( x2 != -100 ) {
    int i ;
    int x = x1 ;
    int dx = x2 - x1 ;
    int xinc = ( dx > 0 ) ? 1 : -1 ;
    dx = abs(dx) ;
    Pixel(x,y,b,c) ;
    for ( i = 1 ; i <= dx ; i++ ) {
      x += xinc ;
      Pixel(x,y,b,c) ; } }
}

void echange(float *p1,float *p2) {
  float aux = *p1 ;
  *p1 = *p2 ;
  *p2 = aux ;
}

void echangeSommet(float *p1,float *p2) {
  if ( p1[1] > p2[1] ) {
    echange(&p1[0],&p2[0]) ;
    echange(&p1[1],&p2[1]) ; }
}

void FacetteDiscrete(bitmap *b,int coul,float *p1,float *p2,float *p3) {
  int *px1 =(int *) calloc(b->ty,sizeof(int)) ;
  int *px2 =(int *) calloc(b->ty,sizeof(int)) ;
  int *px3 =(int *) calloc(b->ty,sizeof(int)) ;
  int i;
  for ( i = 0 ; i < b->ty ; i++ )
    px1[i] = px2[i] = px3[i] = -100000 ;
  ligneCote((int) p1[0],(int) p1[1],(int) p2[0],(int) p2[1],px1,b->ty) ;
  ligneCote((int) p1[0],(int) p1[1],(int) p3[0],(int) p3[1],px2,b->ty) ;
  ligneCote((int) p2[0],(int) p2[1],(int) p3[0],(int) p3[1],px3,b->ty) ;
  int *x1 =(int *) calloc(b->ty,sizeof(int)) ;
  int *x2 =(int *) calloc(b->ty,sizeof(int)) ;
  for ( i = 0 ; i < b->ty ; i++ )
    x1[i] = x2[i] = -100000 ;
  for ( i = 0 ; i < b->ty ; i++ ) {
    if ( px1[i] > x1[i] )
      x1[i] = px1[i] ;
    if ( px2[i] > x1[i] )
      x1[i] = px2[i] ;
    if ( px3[i] > x1[i] )
      x1[i] = px3[i] ; }
  for ( i = 0 ; i < b->ty ; i++ )
    x2[i] = x1[i] ;
  for ( i = 0 ; i < b->ty ; i++ ) {
    if ( ( px1[i] <= x2[i] ) && ( px1[i] != -100000 ) )
      x2[i] = px1[i] ;
    if ( ( px2[i] <= x2[i] ) && ( px2[i] != -100000 ) )
      x2[i] = px2[i] ;
    if ( ( px3[i] <= x2[i] ) && ( px3[i] != -100000 ) )
      x2[i] = px3[i] ; }
  for ( int y = 0 ; y < b->ty ; y++ )
    LigneDiscrete(y,x2[y],x1[y],coul,b) ;
  free(px1);
  free(px2);
  free(px3);
  free(x1);
  free(x2);
}

void allocBitmap(int tx,int ty,bitmap *b) {
  b->tx = tx;
  b->ty = ty;
  b->p =(int **) calloc(ty,sizeof(int *));
  for ( int i = 0 ; i < ty ; i++ )
    b->p[i] =(int *) calloc(tx,sizeof(int));
}

void freeBitmap(bitmap *b) {
  for ( int i = 0 ; i < b->ty ; i++ )
    free(b->p[i]);
  free(b->p);
}

void remplissageFacette(facette3 *f,bitmap *b) {
  float p0[3];
  float p1[3];
  float p2[3];
  p0[0] = f->s[0].x;
  p0[1] = f->s[0].y;
  p0[2] = f->s[0].z;
  p1[0] = f->s[1].x;
  p1[1] = f->s[1].y;
  p1[2] = f->s[1].z;
  p2[0] = f->s[2].x;
  p2[1] = f->s[2].y;
  p2[2] = f->s[2].z;
  FacetteDiscrete(b,1,p0,p1,p2);
}
