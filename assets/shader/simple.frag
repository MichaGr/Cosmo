#version 450 core

in vec4 vs_color;
in vec3 vs_normal;
out vec4 out_color;

void main(){
 vec3 ambient = vec3(0.35,0.2,0.1);
 vec3 lightDirection = normalize(vec3(5,10,5));
 vec3 lightColor = vec3(0.6,0.5,0.5);

 float diffuse = max(0.0,dot(vs_normal,lightDirection));

 vec3 scatteredLight = ambient + lightColor * diffuse;
 out_color = vec4(min(scatteredLight * vs_color.rgb,vec3(1.0)),vs_color.a);
}