#version 330

layout( location = 0 ) in vec4 v_Position;
layout( location=1) in vec4 v_Color;
layout(location =2) in vec4 v_Normal;

uniform mat4 uProjMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;


out vec4 color;
out vec4 normal;
out vec3 posInView;
out mat4 viewMatrix;


void main () {
	gl_Position = uProjMatrix * uViewMatrix * uModelMatrix * v_Position;
	color = v_Color;
	posInView = normalize(vec3(uViewMatrix * uModelMatrix * v_Position));
	
	normal =  transpose(inverse(uViewMatrix * uModelMatrix)) * v_Normal;
	viewMatrix = uViewMatrix;
}
