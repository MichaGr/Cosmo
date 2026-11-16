#version 450 core

layout(location = 0) in vec3 Position;
layout(location = 3) in vec3 Color;
layout(location = 2) in vec3 Normal;

uniform mat4 mv_matrix;

out vec3 vs_pos;
out vec3 vs_color;
out vec3 vs_normal;

void main()
{
    vec4 realPos = vec4(Position,1.0);
    gl_Position = mv_matrix * realPos;
    vs_pos = realPos.xyz;
    vs_color = Color;
    vs_normal = normalize(Normal);
}
