attribute vec3 aVertex;
attribute vec2 aTexCoord;

varying vec2 texCoords;
varying vec4 vPos;

void main(void)
{	
   texCoords = vec2(aTexCoord);
   vPos = gl_ModelViewProjectionMatrix * vec4(aVertex,1.0);
   gl_Position = vPos;
}