#include "texture.h"

GLuint gl_load_BMP(const char * imagepath){

	printf("Reading image %s\n", imagepath);

	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height;
	// Actual RGB data
	unsigned char * data;
	
	GLuint textureID = 0;
	
	FILE * file = NULL;
	
	file = fopen(imagepath,"rb");		// 이미지 파일을 바이러니 읽기 전용으로 읽어들임
	if (!file) {	// 읽지 못했을 시
		printf("%s could not be opened. Are you in the right directory? \n", imagepath);
		getchar();
		return 0;
	}

	// Read the header, i.e. the 54 first bytes

	// 비트맵 파일은 최소 54byte 이상이여야 됨
	if ( fread(header, 1, 54, file)!=54 ){
		printf("Not a correct BMP file : read header\n");
		return 0;
	}
	// 비트맵은 항상 "BM" 으로 시작됨
	if ( header[0]!='B' || header[1]!='M' ) {
		printf("Not a correct BMP file : not begins with \"BM\"\n");
		return 0;
	}
	 
	// Make sure this is a 24bpp file
	/*
	if ( *(int*)&(header[0x1E])!=0  ) {
		printf("Not a correct BMP file : not 24bpp (1)\n");
	 	return 0;
	}
	if ( *(int*)&(header[0x1C])!=24 ) {
		printf("Not a correct BMP file : not 24bpp (2)\n");
	 	return 0;
	}
	*/
	
	// 이미지의 정보를 읽어들임
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
  
	// 몇몇 비트맵 파일의 경우 이미지 정보가 없을 수도 있다. 따라서 일부 정보를 토대로 다음과 같이 이미지 정보를 완성해 준다.
	if (imageSize==0)    imageSize=width*height*3; // 마지막 3은 R,G,B 3가지 요소를 뜻함.
	if (dataPos==0)      dataPos=54; 				// 비트맵 정보의 크기는 총 54byte

	// 데이터를 넣어줄 메모리를 할당해준다.
	data = (unsigned char*)malloc(imageSize);

	// 이미지로부터 데이터를 읽어들인다.
	fread(data,1,imageSize,file);

	// 데이터를 다 불러 들였으니 파일은 닫아줌.
	fclose (file);

	// OpenGL의 텍스쳐 객체를 하나 만들어 줌.
	glGenTextures(1, &textureID);
	
	// 방금 새로 생성한 텍스쳐를 프로그램으로 바인드해주어 프로그램에서 사용 할 수 있도록 만듦
	glBindTexture(GL_TEXTURE_2D, textureID);

	// 이미지 데이터를 OpenGL에게 넘겨준다.
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	// 할당한 메모리는 해제 시켜준다.
	free ( data );

	// trilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glGenerateMipmap(GL_TEXTURE_2D);

	// 생성된 텍스쳐 객체는 함수 밖으로 반환된다.
	return textureID;
}

GLuint gl_load_DDS(const char * imagepath){

	unsigned char header[124];
	unsigned int components  = 0;

	unsigned char * buffer = NULL;
	unsigned int bufsize = 0;
	
	GLuint textureID = 0;
	
	unsigned int blockSize = 0;
	unsigned int offset = 0;
	
	FILE *fp = NULL;
	fp = fopen(imagepath, "rb"); 		// 비트맵과 동일하게 파일을 읽어들임
	if (fp == NULL){
		printf("%s could not be opened. Are you in the right directory? \n", imagepath);
		getchar();
		return 0;
	}
   
	// 파일의 타입을 확인
	char filecode[4]; 
	fread(filecode, 1, 4, fp); 
	if (strncmp(filecode, "DDS ", 4) != 0) { 
		fclose(fp); 
		return 0; 
	}
	
	// DDS파일의 표면 정보를 알아옴
	fread(&header, 124, 1, fp); 

	unsigned int height      	= *(unsigned int*)&(header[8 ]);
	unsigned int width	    = *(unsigned int*)&(header[12]);
	unsigned int linearSize	= *(unsigned int*)&(header[16]);
	unsigned int mipMapCount 	= *(unsigned int*)&(header[24]);
	unsigned int fourCC      	= *(unsigned int*)&(header[80]);
	
	// 밉맵을 포함한 사이즈를 얻어와 데이터를 저장할 버퍼에 메모리를 할당
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize; 
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char)); 
	fread(buffer, 1, bufsize, fp);
	fclose(fp);

	components = (fourCC == FOURCC_DXT1) ? 3 : 4;		// 압축방식을 얻어와 지정해줌
	unsigned int format;
	switch(fourCC) 
	{ 
	case FOURCC_DXT1: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; 
		break; 
	case FOURCC_DXT3: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; 
		break; 
	case FOURCC_DXT5: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; 
		break; 
	default: 
		free(buffer);
		return 0; 
	}

	// OpenGL의 텍스쳐 객체를 생성하여 OpenGL에게 넘겨줌
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);	
	
	
	blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;

	// 밉맵을 불러옴.
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) 
	{
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize; 
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,  
			0, size, buffer + offset); 
	 
		offset += size; 
		width  /= 2; 
		height /= 2; 

		// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
		if(width < 1) width = 1;
		if(height < 1) height = 1;

	} 

	free(buffer); 

	return textureID;


}
