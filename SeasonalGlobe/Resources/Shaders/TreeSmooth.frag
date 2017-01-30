uniform float uShine;
uniform vec4 uDif;
uniform vec4 uSpec;
uniform vec4 uAmb;

varying vec3  vNormal;
varying vec3  vLightVec;
varying vec3  vViewVec;

void main(void)
{
  // Compute the reflection vector:
   vec3 vReflect = normalize( 2.0 * dot( vNormal, vLightVec) * vNormal - vLightVec );       

   // Compute ambient term:
   vec4 AmbientColor = uAmb;

   // Compute diffuse term:
   vec4 DiffuseColor = uDif * max( 0.0, dot( vNormal, vLightVec ));

   // Compute specular term:
   vec4 SpecularColor = uSpec * pow( max( 0.0, dot(vReflect, vViewVec)), uShine );
   
   vec4 FinalColor = AmbientColor + DiffuseColor + SpecularColor;
   
   gl_FragColor = FinalColor;
}