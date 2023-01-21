TARGET 				= exe
IMGUI_DIR 		= imgui/
GEOMETRY_DIR 	= geometry/

SRC_FILES =		$(wildcard *.cpp)			
SRC_FILES += 	$(wildcard $(IMGUI_DIR)*.cpp)		# compile imgui/*.cpp files
SRC_FILES += 	$(wildcard $(GEOMETRY_DIR)*.cpp)	# compile geometry/*.cpp files

OBJ_FILES = 	$(patsubst %.cpp, %.o, $(SRC_FILES))

CXX_FLAGS 		= -std=c++14 -Wall
OPENGL_FLAGS 	= -lGL -lglfw -lX11 -lGLEW


all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	g++ $^ $(OPENGL_FLAGS) -o $@

%.o: %.cpp
	g++ $(CXX_FLAGS) -c $< -o $@

.PHONY: clean all


clean:
# remove all object files excluding the imgui/ dir
	rm -v  *.o geometry/*.o $(TARGET)

clean-all:
#remove all
	rm -v $(OBJ_FILES) $(TARGET)