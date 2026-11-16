#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform samplerBuffer positionBuffer;
uniform samplerBuffer colorBuffer;

uniform mat4 mv_matrix;
uniform mat3 normal_matrix;
uniform vec3 cameraPosition;

out vec4 vs_color;
out vec3 vs_normal;
void main()
{
  vec4 posPlayer = texelFetch(positionBuffer,0);
  vec4 pos = texelFetch(positionBuffer,gl_InstanceID);
  vec4 col = texelFetch(colorBuffer,gl_InstanceID);

  vs_normal = normalize(normal_matrix * normal);
  gl_Position = mv_matrix * vec4(pos.xyz + position,1.0);

  float gradient1 = 1.0;
  if(position.y < 0.5)
  {
    gradient1 = 0.7;
  }
  float gradient2 = float(pos.y)/50.0f;
  float d = distance(posPlayer.xyz,pos.xyz + position);
  float gradient3 = min(1.0,32.0/d);

	if(gl_InstanceID != 0)
	{
		if(pos.y < 5)
		{
			vs_color = col * (gradient1+gradient2) * gradient3;
		}
		else
		{
			vs_color = col * (gradient1+gradient2) * gradient3;
		}
	}
	else
	{
		vs_color = col * gradient1;
	}
}