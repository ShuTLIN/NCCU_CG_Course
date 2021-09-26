#version 330

layout(location=0) in vec4 vPosition;
layout(location=1) in vec4 vColor;

uniform mat4 uViewProjMatrix;
uniform mat4 uModelMatrix;

out vec4 color;

void main () {
	gl_Position = uViewProjMatrix * uModelMatrix * vPosition;
	color = vColor;
}
