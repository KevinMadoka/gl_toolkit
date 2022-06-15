
#ifndef GLTOOLKIT_RENDERER_RENDERER_H_
#define GLTOOLKIT_RENDERER_RENDERER_H_

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define GL_SILENCE_DEPRECATION
/* Without this gl.h gets included instead of gl3.h */
#define GLFW_INCLUDE_NONE
#ifdef __APPLE__
#include <OpenGL/gl3.h>
/* For includes related to OpenGL, make sure their are included after glfw3.h */
#include <GLFW/glfw3.h>
#else
#include <GL/gl3.h>
#include <GL/glfw3.h>
#endif  /* ifdef __APPLE__ */

#include "loader/loader.h"

namespace gl_toolkit {

class Renderer
{
private:
    GLFWwindow  *window;
    GLuint      program;
    GLuint      vao;        /* vertex array object */
    GLuint      vbo;        /* vertex buffer object */
    std::string vertex_shader_src;
    std::string fragment_shader_src;
    void init();
public:
    Renderer();
    Renderer(const std::string& vert_path, const std::string& frag_path);
    static void errorCallback(int error, const char *description);
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void frameBufferResizeCallback(GLFWwindow *window, int width, int height);
    void set_gl_version();  /* Initialization used only */
    void create_window();   /* Create a windowed mode window and its openGL context */
    void set_callback();
    void init_vertex_array_object();
    void init_opengl();
    void buffer_binding();
    GLuint create_shader(GLenum eShaderType, const std::string &strShaderFile);
    GLuint create_program(const std::vector<GLuint> &shaderList);
    void init_program();

    void rendering();
    void terminating();


    // For moving triangle tutorial
};



} /* namespace gl_toolkit */


#endif  /* GLTOOLKIT_RENDERER_RENDERER_H_ */
