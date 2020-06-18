#include "system.h"

int gl_system_init(WINDOW* p_out, int width, int height, const char* title) {
	// GLFW 초기화
	if ( !glfwInit() ) {
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}
		
	glfwWindowHint(GLFW_SAMPLES, 4);										// 멀티 샘플링 x4로 설정
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);							// 화면크기 설정 불가
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						// OpenGL 최대 요구 버전
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);						// OpenGL 최소 요구 버전
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);				// 맥을 위한 설정
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// 구 버전을 사용하지 않음
	
	// 윈도우 생성 및 OpenGL 내용 생성
	p_out->window = glfwCreateWindow( width, height, title, NULL, NULL);
	if( p_out->window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. \n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(p_out->window);

	// GLEW 초기화
	glewExperimental = GL_TRUE; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	
	// callback 함수 등록 : 키보드의 변화, 오류 내용 등을 다음 함수를 통해 전달
	glfwSetKeyCallback(p_out->window, key_callback);
	glfwSetCursorPosCallback(p_out->window, mouse_cursor_callback);
	glfwSetScrollCallback(p_out->window, mouse_scroll_callback);
	glfwSetFramebufferSizeCallback(p_out->window, gl_frame_buf_size_callback);
	
	// 버퍼 스와핑이 일어나기 전까지 기다려야하는 프레임 수
	glfwSwapInterval(1);
	
	// --- camera setting	:: camera.h 에 정의된 함수 사용
	
	gl_set_FOV(18.0f);		// 시야각 설정
	
	gl_set_projection();	// 원근법을 적용한 투사를 구현하기위해 값을 셋팅
	  
	gl_set_view (
		(vec3) { 0, 0, g_cam_dist } ,	// 카메라의 위치
		(vec3) { 0, 0, -1 },			// 초점 방향
		(vec3) { 0, 1, 0 }		// 카메라 방향
	);
  
	return 0;
}

void gl_system_run(WINDOW* window) {
	VEC2 user_pos = V2_ZERO;
	VEC2 update_section = V2_ZERO;
	
	gl_clear_screen();			// 화면의 모든 요소를 지워 검정화면으로 만든다.
	
	glEnable(GL_DEPTH_TEST);	// 화면의 깊이값을 측정하여 프레그먼트를 사용할지
	glDepthFunc(GL_LESS);		// 폐기할지 지정한다.
	
	int is_collision = 0;
	
	do {

		// 화면과 깊이 버퍼를 비워줌
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// 키보드나 마우스에 이벤트가 발생했는지 체크
		glfwPollEvents();
		
		if ( is_g_user_obj_setted() ) {
			game_control_non_callback();	// 유저의 컨트롤을 위한 함수
		}
		
		user_pos = g_obj_get_position ( __CENTER_I );
		// 게임에 사용될 객체들을 모두 업데이트 시켜줌
		//g_world_update(update_section.x, update_section.y);
		update_g_obj();		

		// 화면에 표시될 뷰를 업데이트된 위치로 적용
		user_pos = g_obj_get_position ( __CENTER_I );
		gl_set_view_pos( (vec3){user_pos.x, user_pos.y, g_cam_dist} );

		is_collision = g_obj_is_collision ( 0, 1 );
		printf ( "collision : %d \n", is_collision );

		gl_rander();			// 그래픽에 필요한 함수들을 실행시켜줌
		
		// 스왑 체인 / back buffer를 front buffer로 swap 시켜줌
		glfwSwapBuffers(window->window);

	} while ( !glfwWindowShouldClose(window->window) );	// 종료 명령이 발생할 때 까지 루프

}

void gl_system_shutdown(WINDOW* window) {		// 종료함수
	glfwTerminate();		// GLFW와 관련된 요소들을 해제
}




  
