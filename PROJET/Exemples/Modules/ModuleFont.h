/*
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED 
 * Permission to use, copy, modify, and distribute this software for 
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that 
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission. 
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 * US Government Users Restricted Rights 
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

/*
 *  font.c
 *
 *  Draws some text in a bitmapped font.  Uses glBitmap() 
 *  and other pixel routines.  Also demonstrates use of 
 *  display lists.
 */

/* Modifie par: Nicolas JANEY             */
/* nicolas.janey@univ-fcomte.fr           */
/* Septembre 2005                         */

#ifndef MODULEFONT
#define MODULEFONT

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

enum {
  CENTER = 0,
  RIGHT,
  LEFT } ;

enum {
  REGULAR8x13 = 1,
  REGULAR6x10,
  SYMBOL,
  DESSIN } ;

void lineOutput(int xi,int yi,int xf,int yf) ;
void simpleBitmapOutput(char *format,...) ;
void simpleBitmapOutput(int fonte,char *format,...) ;
void simpleBitmapOutput(int depth,int fonte,char *format,...) ;
void simpleBitmapOutput(char c) ;
void simpleBitmapOutput(int fonte,char c) ;
void simpleBitmapOutput(int depth,int fonte,char c) ;
void placeFontCursor(float x,float y,float z) ;
void deplacementCursor(float x,float y,float z) ;
void setFont(void *font,int alignement) ;
void setAlignement(int a);
void bitmapStringOutput(char *format,...) ;
void bitmapStringOutput(GLfloat x,GLfloat y,GLfloat z,char *format,...) ;
void bitmapOutput(void *font,char *format,...) ;
void bitmapOutput(GLfloat x,GLfloat y,GLfloat z,void *font,char *format,...) ;
void setBold(int b) ;
void setAntialiased(int a) ;
void setEcartementCaracteres(float e) ;
int getBold(void) ;
int getAntialiased(void) ;
float getEcartementCaracteres(void) ;
void strokeOutput(GLfloat x,GLfloat y,float fact,char *format,...) ;

#endif
