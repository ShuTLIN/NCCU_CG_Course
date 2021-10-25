#version 330

in vec4 color;
in vec4 normal;
in mat4 viewMatrix;

uniform vec3 u_lightDir;

out vec4 frag_color;

void main () {
	vec3 lightColor=vec3(1.0);
	vec4 unitLightDir=viewMatrix * vec4(u_lightDir,0.0);
	vec3 unitNormal=normalize(vec3(normal));

	float ka = 0.3; 
	float kd = max(dot(-1.0 * normalize(vec3(unitLightDir)), unitNormal) , 0.0);
	
	vec3 phongShadingColor=kd *  vec3(color) + ka * lightColor * vec3(color);
	frag_color = vec4(phongShadingColor ,1.0);
}
