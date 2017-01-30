uniform sampler2D uTexture;

varying vec2 texCoords;

void main(void)
{
	gl_FragColor = texture2D(uTexture, texCoords);
}