#version 430 core
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
layout(location = 10) uniform mat4 model;
layout(location = 11) uniform mat3 model_normal;

void main()
{
    frag_pos = (model * vec4(pos, 1.0)).xyz;
    frag_normal = model_normal * normal;
    frag_uv = uv;
    gl_Position = projection * view * model * vec4(pos, 1.0);
}
