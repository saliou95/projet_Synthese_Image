#version 450



uniform mat4 MVP;//recuperation de la matrice mvp

layout(location = 0) in vec3 position; // le location permet de dire de quel flux/canal on récupère les données (doit être en accord avec le location du code opengl)
layout (location =3) in vec3 normale;//recuperation des normale
out vec4 color ;
out vec4 fragPosition;
out vec4 fragNormale;
out mat4 mvp;
void main(){

    color=vec4(position,1.0);

    gl_Position= MVP* vec4(position,1.0);
	mvp=MVP;
    fragPosition =MVP* vec4(position,1.0);
	fragNormale =vec4(normalize(normale),1.0);

}


