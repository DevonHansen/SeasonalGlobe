#version 130
uniform sampler2D uTexture;

in float vPercent;

void main(void)
{
	vec4 colour = vec4(1.0, (1.0-(2.0*vPercent)), 0, (1.0-vPercent));

	gl_FragColor = texture2D(uTexture, gl_PointCoord.st) * colour;
}