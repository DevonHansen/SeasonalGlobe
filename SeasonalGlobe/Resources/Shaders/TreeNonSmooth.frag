varying vec2 texCoords;
varying vec4 diffuse;
varying vec4 specular;

void main(void)
{
   gl_FragColor = diffuse + specular;
}