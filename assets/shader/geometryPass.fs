#version 450 core

in vec3 vs_pos;
in vec3 vs_normal;
in vec3 vs_color;

layout(location = 0) out vec3 WorldPosOut;
layout(location = 1) out vec3 DiffuseOut;
layout(location = 2) out vec3 NormalOut;


void main()
{
	WorldPosOut = vs_pos;
	DiffuseOut = vs_color;
	NormalOut = vs_normal;
}
