#define GL_GLEXT_PROTOTYPES

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glext.h>

#include "ModuleGLSL.h"

static void CheckError(int line) {
  GLenum err = glGetError();
  if (err) {
    printf("GL Error %s (0x%x) at line %d\n",
           gluErrorString(err), (int) err, line); }
}

static void LoadAndCompileShader(GLuint shader, const char *text) {
  GLint stat;
  glShaderSource(shader, 1, (const GLchar **) &text, NULL);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &stat);
  if (!stat) {
    GLchar log[1000];
    GLsizei len;
    glGetShaderInfoLog(shader, 1000, &len, log);
    fprintf(stderr, "Problem compiling shader: %s\n", log);
    exit(1); }
}

/**
 * Read a shader from a file.
 */
static void ReadShader(GLuint shader, const char *filename) {
  const int max = 100*1000;
  int n;
  char *buffer = (char*) malloc(max);
  FILE *f = fopen(filename, "r");
  if (!f) {
    fprintf(stderr, "Unable to open shader file %s\n", filename);
    exit(1); }
  n =(int) fread(buffer, 1, max, f);
  if (n > 0) {
    buffer[n] = 0;
    LoadAndCompileShader(shader, buffer); }
  fclose(f);
  free(buffer);
}

static void CheckLink(GLuint prog) {
  GLint stat;
  glGetProgramiv(prog, GL_LINK_STATUS, &stat);
  if ( !stat ) {
    GLchar log[1000];
    GLsizei len;
    glGetProgramInfoLog(prog, 1000, &len, log);
    fprintf(stderr, "Linker error:\n%s\n", log); }
}

GLuint createProgram(GLuint vertShader,GLuint fragShader) {
  GLuint program = glCreateProgram();
  if ( vertShader )
    glAttachShader(program,vertShader);
  if ( fragShader )
    glAttachShader(program,fragShader);
  glLinkProgram(program);
  CheckLink(program);
  CheckError(__LINE__);
  return(program);
}

GLuint createProgram(char *vertShaderFile,GLuint *vertShader,char *fragShaderFile,GLuint *fragShader) {
   if ( vertShaderFile != NULL ) {
     *vertShader = glCreateShader(GL_VERTEX_SHADER);
     ReadShader(*vertShader,vertShaderFile); }
     else
     if ( vertShader )
       *vertShader = 0;
   if ( fragShaderFile != NULL ) {
     *fragShader = glCreateShader(GL_FRAGMENT_SHADER);
     ReadShader(*fragShader,fragShaderFile); }
     else
     if ( fragShader )
       *fragShader = 0;
   return(createProgram(( vertShader ) ? *vertShader : 0,
                        ( fragShader ) ? *fragShader : 0));
}

void checkUniforms(uniform_info *uniforms,GLuint program,int aff) {
  if ( uniforms == NULL )
    return;  
  for ( int i = 0 ; uniforms[i].name ; i++ ) {
    uniforms[i].location = glGetUniformLocation(program, uniforms[i].name);
	if ( aff )
      printf("-> Uniform %s location: %d\n", uniforms[i].name,uniforms[i].location);
    switch (uniforms[i].size) {
      case 1:
        glUniform1fv(uniforms[i].location, 1, uniforms[i].value);
        break;
      case 2:
        glUniform2fv(uniforms[i].location, 1, uniforms[i].value);
        break;
      case 3:
        glUniform3fv(uniforms[i].location, 1, uniforms[i].value);
        break;
      case 4:
        glUniform4fv(uniforms[i].location, 1, uniforms[i].value);
        break;
      default:
         abort(); }
    CheckError(__LINE__); }
}

void checkUniforms(uniform_info *uniforms,GLuint program) {
  checkUniforms(uniforms,program,0);
}