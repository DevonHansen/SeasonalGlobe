uniform sampler2D uTexture;

varying vec2 texCoords;
varying vec4 diffuse;
varying vec4 specular;

void main(void)
{
   gl_FragColor = texture2D(uTexture, texCoords) * diffuse + specular;
}