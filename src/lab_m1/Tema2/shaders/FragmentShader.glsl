#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_position[999];

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform int total_lights;

uniform int hp;

// Additional Uniforms
uniform int spot_light_yes;

uniform vec3 object_color;

// Output
layout(location = 0) out vec4 out_color;

float point_light_contribution(vec3 light_position, vec3 world_position, vec3 world_normal, vec3 object_color) {
    float ambient_light = 0.25;
    float diffuse_light = 0;
    float specular_light = 0;

    world_normal = normalize(world_normal);

    vec3 L = normalize(light_position - world_position);
    vec3 R = reflect(-L, world_normal);
    vec3 H = normalize(L + vec3(0, 0, 0)); // Assuming no eye_position, set to a fixed value

    float globalAmbientalColor = 0.25f;
    float dist = distance(light_position, world_position);
    float constant_att_fact = 0.25f;
    float liniar_att_fact = 0.5f;
    float square_att_fact = 0.75f;

    float attenuation_factor = 1 / (constant_att_fact + dist * liniar_att_fact + dist * dist * square_att_fact);

    float emissive_light = 0;

    // Ambient light component
    ambient_light = 1 * 1;

    // Compute diffuse light component
    diffuse_light = material_kd * max(dot(world_normal, L), 0);

    // Compute specular light component
    specular_light = 0;

    if (diffuse_light > 0) {
        specular_light = material_ks * pow(max(dot(vec3(0, 0, 0), R), 0), material_shininess); // Assuming no eye_position, set to a fixed value
        specular_light = material_ks * pow(max(dot(world_normal, H), 0), material_shininess);
    }

    float light_color;

    // If the light is a spotlight, do additional things.
    if (spot_light_yes == 1) {
        float spot_light = dot(-L, normalize(light_position));
        float spot_light_limit = cos(radians(45.0)); // Adjust the angle as needed

        if (spot_light > spot_light_limit) {
            // Quadratic attenuation
            float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
            attenuation_factor *= pow(linear_att, 2);
        } else {
            attenuation_factor = 0;
        }
    }

    // Compute the total light.
    light_color = (diffuse_light + specular_light) * attenuation_factor;

    if (light_color >= 0.6)
        light_color = 0.5f;
    else if (light_color >= 0.2)
        light_color = 0.3f;
    else if (light_color >= 0.01)
        light_color = 0.1f;
    else
        light_color = 0.01f;

    return light_color;
}

void main() {
    float light_color = 0;

    for (int i = 0; i < total_lights; i++) {
        light_color += point_light_contribution(light_position[i], world_position, world_normal, object_color);
    }

    float globalAmbientalColor = 0.25f;
    float ambient_color = material_kd * globalAmbientalColor;
    light_color += ambient_color;

    out_color = vec4(light_color * object_color, 1) - vec4(0.25f * hp, 0.25f * hp, 0.25f * hp, 1);
}
