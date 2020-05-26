CXX				= gcc
BUILD_OPTION	= -g -framework OpenGL -framework GLUT

BUILD_EXT_REG	= c
BUILD_PATH		= ./bin/
SRC_PATH		= .
TARGET			= out
EXEPTIONS_PATH	= ./direct_x
#EXEPTIONS_FILE	=

SRCS			= $(shell find -E . -regex '(.+\.$(BUILD_EXT_REG)$$)' -not -path "*direct_x/*" )
OBJS			= $($(OBJS):.c=.o)

$(TARGET) :
	@mkdir -p ${BUILD_PATH}

	@echo =======================================
	@echo ========== compile file list ==========
	@echo =======================================
	@echo "\n * (files) \n"

	@for src in $(SRCS); do \
		echo  \\t- $$src; \
	done
	@echo "\n \n * (compile) \n"

	${CXX} ${SRCS} -o ${BUILD_PATH}/${TARGET} ${BUILD_OPTION}

	@echo "\n \n * (result) \n"
	${BUILD_PATH}/${TARGET}

clean :
	rm -f ${BUILD_PATH}/${TARGET}
	rm -f OBJS