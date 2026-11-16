#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;

uniform mat4 vp_mat;

out vec4 Color;
out vec3 normal0;
out vec3 WorldPos0;

void main()
{
        Color = vec4(color,1.0);
        normal0 = normal;
        gl_Position = vp_mat * vec4(position,1.0);
        WorldPos0 = position;
}
