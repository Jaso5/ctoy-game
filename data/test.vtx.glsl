#version 100

attribute vec3 vPos;
attribute vec3 vCol;

varying vec3 fCol;

uniform mat4 camView;
uniform mat4 camProj;


void main() {
    gl_Position = camProj * camView * vec4(vPos, 1.0); // camProj *
    fCol = vCol;
}