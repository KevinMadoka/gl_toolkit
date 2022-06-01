
#include <string>


#include "renderer/renderer.h"





int main()
{
    std::string shader_path;
    std::string vertex_shader;
    std::string fragment_shader;

    shader_path = "/Users/kevinmadoka/Documents/Programming/c++/gl_toolkit/src/data/";

    vertex_shader = shader_path + "vert1.vert";
    fragment_shader = shader_path + "frag1.frag";

    gl_toolkit::Renderer renderer(vertex_shader, fragment_shader);
    renderer.rendering();
    return 0;
}
