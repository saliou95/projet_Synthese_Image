#ifndef DEF_PRIMTV
#define DEF_PRIMTV

#include <GL/glew.h>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <GL/glui.h>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
typedef struct {

        GLfloat x;
        GLfloat y;
        GLfloat z;
       
} Sommet ;

typedef struct {

        int  indiceS1;
        int  indiceS2;
        int  indiceS3;
           
} Face ;

typedef struct {
        GLfloat x;
        GLfloat y;
        GLfloat z;
       
} Normale ;


class Primtv
{
    public:
           Primtv();

           std::vector<Sommet> getPositions();
           std::vector<Face> getFaces();
           std::vector<Normale> getNormales();
           glm::mat4 getmodel();
       
           void afficher();
           void addSommet(Sommet s);
           void addFace(Face f);
           void addNormale(Normale n);
           void miaech(glm::vec3 scamat );
           void translater(glm::vec3 transvect );
           void roter(float angle,glm::vec3 rotmat );
    protected:
             std::vector<Sommet> positions;
             std::vector<Face> faces;
             std::vector<Normale> normales; 
          
           //  glm::mat4 model=glm::mat4(1.0);
             glm::mat4 rotmodel=glm::mat4(1.0f);
             glm::mat4 transmodel=glm::mat4(1.0f);
             glm::mat4 scamodel=glm::mat4(1.0f);
    public:
             int* show;
             std::string nom;
             int ID;
            
};

#endif