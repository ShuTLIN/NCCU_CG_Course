#version 330

layout(location=0) in vec4 v_Position;

uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;

out vec3 position;
out mat4 viewMatrix;
out mat4 projMatrix;

void main () {
    position=v_Position.xyz;
    viewMatrix=uViewMatrix;
    projMatrix=uProjMatrix;
    gl_Position = v_Position; // using directly the clipped coordinates
}



