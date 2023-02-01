TARGET 				= app.exe
IMGUI_DIR 		= imgui/

SRC_FILES =		$(wildcard *.cpp)			
SRC_FILES += 	$(wildcard $(IMGUI_DIR)*.cpp)		# compile imgui/*.cpp files

OBJ_FILES = 	$(patsubst %.cpp, %.o, $(SRC_FILES))

CXX_FLAGS 		= -std=c++17 -Wall
OPENGL_FLAGS 	= -lGL -lglfw -lX11 -lGLEW


all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	g++ $^ $(OPENGL_FLAGS) -o $@

%.o: %.cpp
	g++ $(CXX_FLAGS) -c $< -o $@

.PHONY: clean all


clean:
# remove all object files excluding the imgui/ dir
	rm -v  *.o $(TARGET)

clean-all:
#remove all
	rm -v $(OBJ_FILES) $(TARGET)