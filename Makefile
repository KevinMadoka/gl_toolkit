# g++ -o renderer src/main.cpp src/renderer/renderer.cpp -Iinclude -Isrc -Llib -lglfw -framework OpenGL

target := renderer
build_dir := build
src_dir := src
inc_dir := include
lib_dir := lib
lib_used := glfw

gl_framework := -framework OpenGL

CXX := g++

sources := $(shell find $(src_dir) -name '*.cpp' -or -name '*.c' -or -name '*.cc')
objects := $(sources:%=$(build_dir)/%.o)
depends := $(objects:.o=.d)

INC_FLAGS := $(addprefix -I,$(shell find $(src_dir) -type d))
INC_FLAGS += $(addprefix -I,$(inc_dir))

LIB_FLAGS := $(addprefix -L,$(lib_dir)) $(addprefix -l,$(lib_used)) $(gl_framework)

CPPFLAGS := $(INC_FLAGS) -MMD -MP


$(build_dir)/$(target): $(objects)
	$(CXX) $(objects) -o $@ $(INC_FLAGS) $(LIB_FLAGS)

$(build_dir)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) -c $< -o $@




.PHONY: clean

clean:
	rm -r $(build_dir)


-include $(depends)
