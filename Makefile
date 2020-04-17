CC=nvcc

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./ -g
IGNORE_WARNING_FLAGS= -Xcudafe --diag_suppress=esa_on_defaulted_function_ignored
ARMA_FLAGS = -DARMA_DONT_USE_WRAPPER

BIN_RENDER = bin/render
BIN_PHYSICS = bin/physics
BIN_GRAVITON = bin/graviton

SRC_RENDER = src/renderer/test.cpp src/renderer/object.cpp src/renderer/models.cpp src/renderer/mesh.cpp src/renderer/gl_util.cpp src/renderer/shader.cpp 
INC_RENDER = src/renderer/object.h src/renderer/models.h src/renderer/mesh.h src/renderer/gl_util.hpp src/renderer/shader.hpp


SRC_GRAVITON = src/main.cpp src/renderer/object.cpp src/renderer/models.cpp src/renderer/mesh.cpp src/renderer/gl_util.cpp src/renderer/shader.cpp
INC_GRAVITON = src/renderer/object.h src/renderer/models.h src/renderer/mesh.h src/renderer/gl_util.hpp src/renderer/shader.hpp

SRCS=src/test.cu src/gl_framework.cpp src/shader_util.cpp src/class.cpp
INCLUDES=src/gl_framework.hpp src/shader_util.hpp src/test.hpp src/class.hpp
OUT_DIR = bin

all: directories $(BIN)
# all: $(BIN)


render:
	$(BIN): $(SRC_RENDER) $(INC_RENDER)
	$(CC)  $(CPPFLAGS) $(SRC_RENDER) -o $(BIN_RENDER) $(LDFLAGS) $(LIBS) $(IGNORE_WARNING_FLAGS)

graviton:
	$(BIN): $(SRC_GRAVITON) $(INC_GRAVITON)
	$(CC)  $(CPPFLAGS) $(SRC_GRAVITON) -o $(BIN_GRAVITON) $(LDFLAGS) $(LIBS) $(IGNORE_WARNING_FLAGS) $(ARMA_FLAGS)

clean:
	rm -f *~ *.o $(BIN)

MKDIR_P = mkdir -p

.PHONY: directories

directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}
