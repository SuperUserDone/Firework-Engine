#version 430 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec3 tangent;

out vec3 frag_pos;
out vec3 frag_normal;
out vec2 frag_uv;
out vec3 frag_campos;
out mat3 frag_tangent_basis;

layout(std140) uniform camera
{
    mat4 projection;
    mat4 view;
    vec3 cam_pos;
};
layout(location = 10) uniform mat4 model;
layout(location = 11) uniform mat3 model_normal;

void main()
{
    vec3 T = normalize(vec3(model * vec4(tangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(normal, 0.0)));
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);

    frag_pos = (model * vec4(pos, 1.0)).xyz;
    frag_normal = model_normal * normal;
    frag_tangent_basis = mat3(T, B, N);
    frag_uv = vec2(uv.x, 1.0 - uv.y);
    frag_campos = cam_pos;

    gl_Position = projection * view * model * vec4(pos, 1.0);
}
