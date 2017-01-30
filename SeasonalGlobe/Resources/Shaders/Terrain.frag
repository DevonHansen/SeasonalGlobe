uniform sampler2D texSampler;

varying vec2 texCoords;
varying vec4 diffuse;
varying vec4 specular;
varying float displacement;

void main(void)
{
	if(displacement > 1)
	{
		gl_FragColor = vec4(1.0,1.0,1.0,1.0)* diffuse;
	}
	else
	{
   gl_FragColor = texture2D(texSampler, texCoords) * diffuse + specular;
   }
}