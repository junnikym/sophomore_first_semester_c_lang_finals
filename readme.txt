[ STYLE ] 

-- naming --

- 스네이크 표기법 사용 :    단어사이에 언더바(_) 삽입
		예) p_out, gl_system_init
- 변수와 파일명은 소문자사용

enum :    typedef enum { ... } _NAME_; // upper case

struct :    typedef struct { ... } NAME; // upper case

openGL 관련 함수 :    gl_... 로 시작

-- TODO --

 - object, entity 구동법	-> object는 여러개의 entity로 이루어져 있음
			    그 중 대표가되는 center entity에 물리적인 요소를 종합하여 저장
			    나머지는 entity는 center entity를 기준으로 어디에 어느방향으로 
			    위치되어있는지, 개별적으로 작동하는 force 등 을 저장

 	-> create function : run_entity(); // center_entity만을 위한 함수
	-> create function : run_object(); // entity 종합 -> run_entity는 center_entity만 적용할 것

 - graphics - object 크기 조절 	-> z축 위치를 이용하여 크기를 조절 ( 원근법 이용 )