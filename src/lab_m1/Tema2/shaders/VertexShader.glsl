#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Damage variable
uniform int dmg;

// Output values to fragment shader
out vec3 world_position;
out vec3 world_normal;

void main()
{
    // Compute world space vertex position and normal
    vec3 adjusted_position = v_position + dmg * 0.01 * normalize(v_normal); // Adjust based on damage (modify as needed)
    world_position = vec3(Model * vec4(adjusted_position, 1));
    world_normal = normalize(vec3(Model * vec4(v_normal, 0)));

    // Apply the standard transformation
    gl_Position = Projection * View * Model * vec4(adjusted_position, 1.0);
}
