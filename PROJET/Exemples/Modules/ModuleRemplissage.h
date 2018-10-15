/* Auteur: Nicolas JANEY            */
/* nicolas.janey@univ-fcomte.fr     */
/* Septembre 2005                   */
/* Remplissage d'une facette 2D     */

#ifndef MODULEREMPLISSAGE
#define MODULEREMPLISSAGE

struct coord3D {
  float x;
  float y;
  float z; } ;

struct facette3 {
  coord3D s[3]; } ;

struct bitmap {
  int tx ;
  int ty ;
  int **p ; } ;

void allocBitmap(int tx,int ty,bitmap *b);
void freeBitmap(bitmap *b);
void remplissageFacette(facette3 *f,bitmap *b);

#endif
