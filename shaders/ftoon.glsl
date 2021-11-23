#version 330

in vec4 color;
in vec4 normal;
in mat4 viewMatrix;
in vec3 posInView;

uniform vec3 u_lightDir;

out vec4 frag_color;

void main () {
	

	frag_color = color;
}
