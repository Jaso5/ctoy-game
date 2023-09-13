#ifdef GL_ES
precision mediump float;
#endif
varying vec3 fCol;

void main() {
    gl_FragColor = vec4(fCol, 1.0) + 0.3;
}