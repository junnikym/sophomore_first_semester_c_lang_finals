#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>

#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

static GLfloat g_FOV = 0.0f;

// Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
static mat4 g_cam_projection = GLM_MAT4_IDENTITY_INIT;

// Camera matrix
static mat4 g_cam_view = GLM_MAT4_IDENTITY_INIT;

static mat4 g_VP =GLM_MAT4_IDENTITY_INIT;		// MVP -> M | VP

// ------------------------------------------------------- //
// ----- setter	------------------------------------------

void gl_set_FOV ( GLfloat angle );
void gl_add_FOV ( GLfloat how_much );

void gl_set_projection ( );

void gl_set_view ( vec3 pos, vec3 at, vec3 up_vec );
void gl_set_view_mat ( mat4 look_at );
void gl_set_view_pos ( vec3 pos );

void gl_update_cam ( );

// ------------------------------------------------------- //
// ----- getter	------------------------------------------

void gl_get_mvp( const mat4 model, mat4 result );

// ------------------------------------------------------- //

#endif /* CAMERA_H */




  
