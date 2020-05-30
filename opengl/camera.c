#include "camera.h"

// ------------------------------------------------------- //
// ----- setter	------------------------------------------

void gl_set_FOV ( GLfloat angle ) {
	g_FOV = angle;
}

void gl_set_projection() {
	// ! TODO : Change screen ratio

	glm_perspective ( 45.0f, 1024.0f / 768.0f, 0.1f, 100.0f, g_cam_projection );
}

void gl_set_view ( vec3 pos, vec3 at, vec3 up_vec ) {
	glm_lookat (
		pos,
		at,
		up_vec,
		g_cam_view
	);
}

void gl_set_view_mat ( mat4 look_at ) {
	glm_mat4_copy(look_at, g_cam_view);
}

void gl_update_cam() {
	glm_mat4_mul ( g_cam_projection, g_cam_view, g_VP );
}

// ------------------------------------------------------- //
// ----- getter	------------------------------------------

void gl_get_mvp( const mat4 model, mat4 result ) {
	glm_mat4_mul ( g_VP, model, result );
}

// ------------------------------------------------------- //
