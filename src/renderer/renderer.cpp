
#include "renderer/renderer.h"


#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

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

// Vertex data and buffer
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};


void
gl_toolkit::Renderer::
init()
{
    // Set callback for errors
    glfwSetErrorCallback(errorCallback);

    // Initialize the library
    if (!glfwInit())
        std::cerr << "glfwInit() failure!" << std::endl;

    set_gl_version();   /* Make openGL version 4.1 */
    create_window();
    set_callback();

    // Make the window's context current
    glfwMakeContextCurrent(this->window);

    // Used to avoid screen tearing
    glfwSwapInterval(1);

    init_opengl();
}


gl_toolkit::Renderer::
Renderer(const std::string& vert_path, const std::string& frag_path)
{
    Loader loader;

    // Load the shader source from another files
    loader.load_from_file(vert_path);
    this->vertex_shader_src = loader.get_content();

    loader.load_from_file(frag_path);
    this->fragment_shader_src = loader.get_content();

    init();
}

void
gl_toolkit::Renderer::
init_vertex_array_object()
{
    /* Vertex array object*/
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);
}

void
gl_toolkit::Renderer::
buffer_binding()
{
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void
gl_toolkit::Renderer::
init_opengl()
{
    //OpenGL initializations start from here
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    init_vertex_array_object();


    buffer_binding();

    // Creating shader and program objects
    init_program();
    glUseProgram(this->program);

    // Formating  buffers' data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //OpenGL initializations end here
}

GLuint
gl_toolkit::Renderer::
create_shader(GLenum eShaderType, const std::string &strShaderFile)
{
    GLuint shader = glCreateShader(eShaderType);
    const char *strFileData = strShaderFile.c_str();
    glShaderSource(shader, 1, &strFileData, NULL);

    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

        const char *strShaderType = NULL;
        switch(eShaderType)
        {
        case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
        case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
        case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
        }

        fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
        delete[] strInfoLog;
    }

    return shader;
}

GLuint
gl_toolkit::Renderer::
create_program(const std::vector<GLuint> &shaderList)
{
    GLuint program = glCreateProgram();

    for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
        glAttachShader(program, shaderList[iLoop]);

    glLinkProgram(program);

    GLint status;
    glGetProgramiv (program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }

    for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
        glDetachShader(program, shaderList[iLoop]);

    return program;
}

void
gl_toolkit::Renderer::
init_program()
{
    std::vector<GLuint> shaderList;

    // Using loader/loader.h to load vertex shader and fragment shader files

    shaderList.push_back(create_shader(GL_VERTEX_SHADER, this->vertex_shader_src));
    shaderList.push_back(create_shader(GL_FRAGMENT_SHADER, this->fragment_shader_src));

    this->program = create_program(shaderList);

    std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
}

void
gl_toolkit::Renderer::
set_callback()
{
    // Set callback for window
    glfwSetKeyCallback(this->window, keyCallback);

    // Set callback fro framebuffer
    glfwSetFramebufferSizeCallback(this->window, frameBufferResizeCallback);
}

void
gl_toolkit::Renderer::
create_window()
{
    // Create a windowed mode window and its OpenGL context
    this->window = glfwCreateWindow(640, 480, "Running OpenGL on Mac", NULL, NULL);
    if (!this->window)
    {
        glfwTerminate();
        std::cerr << "glfwCreateWindow() failure!" << std::endl;
    }
}

void
gl_toolkit::Renderer::
set_gl_version()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Without these two hints, nothing above OpenGL version 2.1 is supported
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void
gl_toolkit::Renderer::
errorCallback(int error, const char* description)
{
    std::cerr << description  << std::endl;
    //fputs(description, stderr);
}

void
gl_toolkit::Renderer::
keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void
gl_toolkit::Renderer::
frameBufferResizeCallback(GLFWwindow* window, int width, int height)
{
   glViewport(0, 0, width, height);
}

void
gl_toolkit::Renderer::
rendering()
{
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(this->window))
    {
        // Resize the viewport
        int width, height;
        glfwGetFramebufferSize(this->window, &width, &height);
        glViewport(0, 0, width, height);

        // OpenGL Rendering related code
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(this->program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap front and back buffers
        glfwSwapBuffers(this->window);

        // Poll for and process events
        glfwPollEvents();
    }
    terminating();
}

void
gl_toolkit::Renderer::
terminating()
{
    glfwDestroyWindow(this->window);
    glfwTerminate();
    std::cout << "Termiate rendering!" << std::endl;
}



