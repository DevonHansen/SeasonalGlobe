attribute vec3 aVertex;
attribute vec3 aNormal;
attribute vec2 aTexCoord;

uniform vec3 uLightDir;

varying vec2  vTexCoord;
varying vec3  vNormal;
varying vec3  vLightVec;
varying vec3  vViewVec;

void main(void)
{   
   // Output transformed vertex position:
   gl_Position = gl_ModelViewProjectionMatrix * vec4(aVertex,1.0);  // Compute the light vector (view space):
   vLightVec   = -uLightDir.xyz;

   // Transform vertex position into view space:
   vec3 Pview =  vec3(gl_ModelViewMatrix * vec4(aVertex,1.0));

   // Transform normal into view space:        
   vNormal = normalize( gl_NormalMatrix * aNormal);

   // Compute view vector (view space):
   vViewVec = -normalize(Pview);  
   
   vTexCoord = aTexCoord;
}