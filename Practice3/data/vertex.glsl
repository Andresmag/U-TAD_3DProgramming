uniform mat4 mvp;
attribute vec3 vpos;
attribute vec2 vtex;
varying vec2 ftext;

void main() {
	gl_Position = mvp * vec4(vpos, 1);
	ftext = vtex;
}