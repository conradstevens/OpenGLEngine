#version 410 core
layout (location = 0) in vec2 aPos;

uniform mat3 u_move;
uniform mat3 u_rotation;

void main()
{
    vec3 translated = vec3(aPos, 1.0) * u_rotation * u_move;
    gl_Position = vec4(translated.xy, 0.0, 1.0);
}