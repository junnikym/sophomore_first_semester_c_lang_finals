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
	
	printf("pos: %f      %f     %f\n", g_cam_view[0], g_cam_view[1], g_cam_view[2]);
	printf("lookat [0]: %f      %f     %f     %f \n",
		   	g_cam_view[0][0], g_cam_view[0][1], g_cam_view[0][2], g_cam_view[0][3]);
	printf("lookat [1]: %f      %f     %f     %f \n",
			g_cam_view[1][0], g_cam_view[1][1], g_cam_view[1][2], g_cam_view[1][3]);
	printf("lookat [2]: %f      %f     %f     %f \n",
			g_cam_view[2][0], g_cam_view[2][1], g_cam_view[2][2], g_cam_view[2][3]);
	printf("lookat [3]: %f      %f     %f     %f \n",
			g_cam_view[3][0], g_cam_view[3][1], g_cam_view[3][2], g_cam_view[3][3]);
	printf("\n\n");
	
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



