#version 430 core

out vec4 color;

in vec2 frag_uv;

layout(binding = 0) uniform sampler2D screen_texture;

void main() { color = vec4(texture(screen_texture, frag_uv).rgb, 1.0); }
