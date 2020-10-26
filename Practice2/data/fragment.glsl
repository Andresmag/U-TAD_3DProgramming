uniform sampler2D texSampler;
varying vec2 ftext;

void main() {
	gl_FragColor = texture2D(texSampler, ftext);
}
