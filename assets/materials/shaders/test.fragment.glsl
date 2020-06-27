#version 330 core
in vec3 frag_pos;
in vec3 frag_normal;
in vec2 frag_uv;

out vec4 FragColor;

void main()
{
    vec3 light_pos = vec3(2.0f, -2.0f, 2.0f);
    vec3 light_color = vec3(1.0f, 1.0f, 1.0f);

    vec3 normal = normalize(frag_normal);
    vec3 light_dir = normalize(light_pos - frag_pos);

    float diff = max(dot(normal, light_dir), 0.0);
    vec3 diffuse = diff * light_color;

    vec3 ambient = 0.1f * light_color;

    vec3 obj_color = vec3(1.0f, 0.5f, 0.2f);

    vec3 final = (ambient + diffuse) * obj_color;
    FragColor = vec4(final, 1.0f);
}
