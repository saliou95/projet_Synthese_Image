#version 450
uniform struct Light {vec3 position ; vec3 intensities; float ambientCoefficient;float attenuation ;} light;
uniform vec3 cameraPosition;
//uniform mat4 MODEL;
in vec4 fragPosition;
in vec4 fragNormale;
out vec4 finalColor;
in vec4 color;
vec4 ambient;
vec4 difuse ;
vec4 speculaire;
in mat4 mvp;
void main() 
{
    //calcule de lumiere avec phong 
    vec4 dirdif= normalize(fragPosition)-normalize(mvp*vec4(light.position,1.0));
    float angledif=dot(dirdif,fragNormale);
    float anglespecN=acos(max(dot(dirdif,fragNormale),0));
    vec4 dirspec=normalize(fragPosition)-normalize(mvp*vec4(cameraPosition,1.0));
    float anglespec=abs(acos(max(dot(dirspec,fragNormale),0)) -anglespecN);
    difuse=vec4(light.intensities,1.0)*light.attenuation*max(angledif,0)  ;
    ambient=vec4(light.intensities,1.0)*light.ambientCoefficient;
    speculaire=vec4(light.intensities,1.0)*light.attenuation*pow(cos(anglespec),4);
    finalColor=color*(ambient+difuse+speculaire);
}

