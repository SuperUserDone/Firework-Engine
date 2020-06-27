#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

out vec3 frag_pos;
out vec3 frag_normal;
out vec2 frag_uv;

layout(std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
uniform mat4 model;

void main()
{
    frag_pos = pos;
    frag_normal = normal;
    frag_uv = uv;
    gl_Position = projection * view * vec4(pos, 1.0);
    // gl_Position = vec4(pos, 1.0);
}
