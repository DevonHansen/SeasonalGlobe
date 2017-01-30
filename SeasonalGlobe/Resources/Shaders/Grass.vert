attribute vec3 aVertex;
attribute vec2 aTexCoords;
attribute vec3 aPosition;

varying vec2 texCoords;

void main(void)
{
	texCoords = aTexCoords;
	vec3 inPos = vec3(aVertex.x + aPosition.x, aVertex.y, aVertex.z+aPosition.y);

	gl_Position = gl_ModelViewProjectionMatrix * vec4(inPos,1.0);
}