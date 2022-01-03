#version 450
uniform struct Light {vec3 position ; vec3 intensities; float ambientCoefficient;float attenuation ;} light;





uniform vec3 cameraPosition;

uniform sampler2D myTextureSampler;
uniform mat4 MODEL;

in vec4 fragPosition;
in vec4 fragNormale;
out vec4 finalColor;
in vec4 color;
vec4 ambient;
vec4 difuse ;

void main() {

vec4 dirdif= normalize(fragPosition)-normalize(vec4(light.position,1.0));

float angledif=dot(dirdif,fragNormale);

difuse=vec4(light.intensities,1.0)*light.attenuation*max(angledif,0)  ;
ambient=vec4(light.intensities,1.0)*light.ambientCoefficient;

finalColor=color;//*(ambient +difuse);
}