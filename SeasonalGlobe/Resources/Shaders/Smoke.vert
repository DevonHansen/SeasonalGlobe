#version 130
uniform float uScale;
uniform vec3 uCamPos;

out float vPercent;

void main(void)
{
	// Use gl_Color.xy for orgTTL and curTTL respectively
	vec2 TTL = gl_MultiTexCoord0.xy;

	vPercent = (TTL.x - TTL.y)/TTL.x;

	// Using screen ratio as 1
	vec3 pos = uCamPos - vec3(gl_ModelViewMatrix*gl_Vertex);
	pos.y = 1.0;
	float distance = length(pos);
	float size = (uScale/2)+(uScale*(1.0/(1.0*(distance*distance)))) * vPercent;
	gl_PointSize = size;

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}