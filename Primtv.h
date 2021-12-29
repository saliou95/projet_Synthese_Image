#ifndef DEF_PRIMTV
#define DEF_PRIMTV
#include <GL/glew.h>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Transformation.h"
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
            
           void afficher();
           void addSommet(Sommet s);
           void addFace(Face f);
           void addNormale(Normale n);
           
    protected:
             std::vector<Sommet> positions;
             std::vector<Face> faces;
             std::vector<Normale> normales; 
             std::vector<Transformation> transformations;
                 
};

#endif