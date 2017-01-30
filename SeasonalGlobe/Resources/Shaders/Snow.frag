#version 130
uniform sampler2D uTexture;

in vec4 vPosition;

void main(void)
{
	if(sqrt((vPosition.y*vPosition.y)+(vPosition.x*vPosition.x)) < 0.8)
	{
		if(sqrt((vPosition.y*vPosition.y)+(vPosition.z*vPosition.z)) < 0.8)
		{
			gl_FragColor = texture2D(uTexture, gl_PointCoord.st);
		}
		else
		{
			gl_FragColor = vec4(0,0,0,0);
		}
	}
	else
	{
		gl_FragColor = vec4(0,0,0,0);
	}
}