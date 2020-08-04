#version 430 core
in vec3 frag_pos;
in vec3 frag_normal;
in vec2 frag_uv;
in vec3 frag_campos;
in mat3 frag_tangent_basis;

layout(location = 0) out vec4 color;

layout(binding = 0) uniform sampler2D albedo_map;
layout(binding = 1) uniform sampler2D normal_map;
layout(binding = 2) uniform sampler2D metallic_map;
layout(binding = 3) uniform sampler2D roughness_map;
layout(binding = 4) uniform samplerCube specular_map;
layout(binding = 5) uniform samplerCube irradiance_map;
layout(binding = 6) uniform sampler2D specularBRDF_LUT;

const float PI = 3.141592;

vec3 light_pos[4] = {
    vec3(2.0, 0.0, 1.0),  //
    vec3(2.0, 0.0, -1.0), //
    vec3(0.0, 2.0, 1.0),  //
    vec3(0.0, 2.0, -1.0)  //
};

vec3 light_col[4] = {
    vec3(10.47, 11.31, 10.79), //
    vec3(10.47, 11.31, 10.79), //
    vec3(10.47, 11.31, 10.79), //
    vec3(10.47, 11.31, 10.79)  //
};

vec3 fresnelSchlick(float cosTheta, vec3 F0);
float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySchlickGGX(float NdotV, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);

void main()
{
    vec3 N = texture(normal_map, frag_uv).rgb;
    N = N * 2.0 - 1.0;
    N = normalize(frag_tangent_basis * N);

    vec3 V = normalize(frag_campos - frag_pos);

    vec3 albedo = pow(texture(albedo_map, frag_uv).rgb, vec3(2.2));
    float metalness = texture(metallic_map, frag_uv).r;
    float roughness = texture(roughness_map, frag_uv).r;
    float ao = 1.0;

    vec3 Lo = vec3(0.0);
    for (int i = 0; i < 4; ++i)
    {
        vec3 L = normalize(light_pos[i] - frag_pos);
        vec3 H = normalize(V + L);

        float distance = length(light_pos[i] - frag_pos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = light_col[i] * attenuation;

        vec3 F0 = vec3(0.04);
        F0 = mix(F0, albedo, metalness);
        vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);

        float NDF = DistributionGGX(N, H, roughness);
        float G = GeometrySmith(N, V, L, roughness);

        vec3 numerator = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
        vec3 specular = numerator / max(denominator, 0.001);

        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;

        kD *= 1.0 - metalness;

        float NdotL = max(dot(N, L), 0.0);

        Lo += (kD * albedo / PI + specular) * radiance * NdotL;
    }
    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 output_color = ambient + Lo;

    output_color = output_color / (output_color + vec3(1.0));
    output_color = pow(output_color, vec3(1.0 / 2.2));

    color = vec4(output_color, 1.0);
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float num = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;

    float num = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return num / denom;
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
