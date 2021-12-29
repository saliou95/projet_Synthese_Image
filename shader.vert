#version 430


layout(location = 0) in vec3 position; // le location permet de dire de quel flux/canal on récupère la données


void main(){

        gl_Position = vec4(position, 1.0);
     

}


