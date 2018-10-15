#ifndef MODULEGLSL
#define MODULEGLSL

#define GL_GLEXT_PROTOTYPES

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glext.h>

typedef struct uniform_info {
   const char *name;
   GLuint size;
   GLint location;
   GLfloat value[4];
} uniform_info;

GLuint createProgram(GLuint vertShader,GLuint fragShader);
GLuint createProgram(char *vertShaderFile,GLuint *vertShader,char *fragShaderFile,GLuint *fragShader);
void checkUniforms(uniform_info *uniforms,GLuint program);
void checkUniforms(uniform_info *uniforms,GLuint program,int aff);

#endif
