attribute vec3 aVertex;

void main(void)
{
	gl_Position = gl_ModelViewProjectionMatrix * vec4(aVertex,1.0);
}