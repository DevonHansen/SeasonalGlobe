uniform sampler2D texSampler;
uniform float uTimeInSeason;
uniform float uTime;

varying vec2 texCoords;
varying vec4 vPos;

void main(void)
{
	vec4 colour;
	if(uTime <= 0.0)
	{
		colour = vec4(1.0,1.0,0.0,1.0);
		gl_FragColor = texture2D(texSampler, texCoords) * colour;
	}
	else if (uTime >= uTimeInSeason)
	{
		colour = vec4(1.0,0.5,0.0,1.0);
		gl_FragColor = texture2D(texSampler, texCoords) * colour;
	}
	else
	{
		colour = vec4(1.0, min(1.0, (0.5+((uTimeInSeason - uTime)/uTimeInSeason))),0.0,1.0);
		gl_FragColor = texture2D(texSampler, texCoords) * colour;
	}
}