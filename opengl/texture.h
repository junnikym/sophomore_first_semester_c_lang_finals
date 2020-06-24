#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

// Load a .BMP file using our custom loadert
GLuint gl_load_BMP (const char * imagepath);

// Load a .DDS file using GLFW's own loader
GLuint gl_load_DDS (const char * imagepath);

#endif /* GL_TEXTURE_H */





















   







     
