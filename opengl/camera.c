#include "camera.h"

// ------------------------------------------------------- //
// ----- setter	------------------------------------------

void gl_set_FOV ( GLfloat angle ) {
	g_FOV = angle;
}

void gl_add_FOV ( GLfloat how_much ) {
	
	if(g_FOV >= 10.0f && g_FOV <= 45.0f)
		g_FOV += how_much;
	
	printf("now zoom : %lf \n", g_FOV);
	
	if(g_FOV <= 10.0f)
		g_FOV = 10.0f;
	if(g_FOV >= 45.0f)
		g_FOV = 45.0f;
}

void gl_set_projection() {
	// ! TODO : Change screen ratio
	
	glm_perspective ( glm_rad(g_FOV), 1024.0f / 768.0f, 0.1f, 300.0f, g_cam_projection );
}

void gl_set_view ( vec3 pos, vec3 at, vec3 up_vec ) {
	vec3 pos_at;
	
	glm_vec3_copy(pos, g_cam_view_pos);
	glm_vec3_copy(at, g_cam_view_at);
	glm_vec3_copy(up_vec, g_cam_view_up);
	
	glm_vec3_add(g_cam_view_pos, g_cam_view_at, pos_at);
	
	glm_lookat (
		g_cam_view_pos,
		pos_at,
		g_cam_view_up,
		g_cam_view
	);
	
}

void gl_set_view_mat ( mat4 look_at ) {
	glm_mat4_copy(look_at, g_cam_view);
}

void gl_set_view_pos ( vec3 pos ) {
	vec3 pos_at;
	
	glm_vec3_copy(pos, g_cam_view_pos);
	
	glm_vec3_add(g_cam_view_pos, g_cam_view_at, pos_at);
	
	glm_lookat (
		g_cam_view_pos,
		pos_at,
		g_cam_view_up,
		g_cam_view
	);
	
	gl_update_cam();
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



