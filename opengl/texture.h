#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H

#include <GL/glew.h>

// Load a .BMP file using our custom loader
GLuint gl_load_BMP (const char * imagepath);

// Load a .DDS file using GLFW's own loader
GLuint gl_load_DDS (const char * imagepath);



#endif /* GL_TEXTURE_H */
