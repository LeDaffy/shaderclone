#version 460 core
in vec4 coord;
out vec4 fragColor;

uniform float iTime;
uniform uvec2 iResolution;


#define MAX_STEPS = 100;
#define MAX_DISTANCE = 100.0f;
#define SURFACE_DISTANCE = 0.01f;

float ray_march (vec3 ro, vec3 rd)
{
    float distance_from_origin = 0.0f;

    // for (int i = 0; i < MAX_STEPS; i++) {
    //     vec3 p = ro + rd * distance_from_origin;
    // }

    return distance_from_origin;
}

void main()
{
    vec2 uv = coord.xy * iResolution / iResolution.y;

    vec3 ro = vec3(0, 1, 0);
    vec3 rd = normalize(vec3(uv.x, uv.y, 1));

    fragColor = vec4(1.0, 0.4, 1.0f, 1.0f);
} 
