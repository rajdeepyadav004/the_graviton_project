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

SRC_RENDER = src/renderer/test.cpp src/renderer/render_component.cpp src/renderer/models.cpp src/renderer/mesh.cpp src/renderer/gl_util.cpp src/renderer/shader.cpp src/renderer/camera.cpp
INC_RENDER = src/renderer/render_component.h src/renderer/models.h src/renderer/mesh.h src/renderer/gl_util.hpp src/renderer/shader.hpp src/renderer/camera.hpp


SRC_PHYSICS = src/physics_engine/test.cpp src/physics_engine/rigidBody.cpp 
INC_PHYSICS = src/physics_engine/rigidBody.hpp

SRC_GRAVITON = src/main.cpp src/renderer/render_component.cpp src/renderer/models.cpp\
			   src/renderer/mesh.cpp src/renderer/gl_util.cpp src/renderer/shader.cpp\
			   src/renderer/camera.cpp\
			   src/physics_engine/rigidBody.cpp\
			   src/world.cpp 
INC_GRAVITON = src/renderer/render_component.h src/renderer/models.h src/renderer/mesh.h\
			   src/renderer/gl_util.hpp src/renderer/shader.hpp src/renderer/camera.cpp\
			   src/physics_engine/rigidBody.hpp\
			   src/world.hpp




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

physics:
	$(BIN): $(SRC_PHYSICS) $(INC_PHYSICS)
	$(CC)  $(CPPFLAGS) $(SRC_PHYSICS) -o $(BIN_PHYSICS) $(LDFLAGS) $(LIBS) $(IGNORE_WARNING_FLAGS) $(ARMA_FLAGS)


clean:
	rm -rf $(OUT_DIR)

MKDIR_P = mkdir -p

.PHONY: directories

directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}
