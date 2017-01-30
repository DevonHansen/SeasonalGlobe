uniform sampler2D texSampler;
uniform float percThroughSeason;

varying vec2 texCoords;
varying vec4 diffuse;
varying vec4 specular;
varying vec3 normals;

void main(void)
{
	float col = percThroughSeason;
	if(normals.y > 0.5)
	{
		gl_FragColor = (texture2D(texSampler, texCoords) + vec4(col,col,col,0.0)) * diffuse + specular;
	}
	else
	{
		gl_FragColor = texture2D(texSampler, texCoords) * diffuse + specular;
	}
}