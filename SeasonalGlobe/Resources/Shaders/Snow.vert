#version 130
uniform float uScale;
uniform vec3 uCamPos;

out vec4 vPosition;

void main(void)
{
	// Using screen ratio as 1
	vec3 pos = uCamPos - vec3(gl_ModelViewMatrix*gl_Vertex);
	vPosition = vec4(pos,1.0);
	pos.y = 1.0;
	float distance = length(pos);
	float size = uScale*(1.0/(1.0*(distance*distance)));
	gl_PointSize = size;

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}