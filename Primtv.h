#ifndef DEF_PRIMTV
#define DEF_PRIMTV

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
typedef struct {

        float x;
        float y;
        float z;
       
} Sommet ;

typedef struct {

        int  indiceS1;
        int  indiceS2;
        int  indiceS3;
           
} Face ;

typedef struct {
        float x;
        float y;
        float z;
       
} Normale ;


class Primtv
{
    public:
           Primtv();
           std::vector<Sommet> getPositions();
           std::vector<Face> getFaces();
           std::vector<Normale> getNormales();
           void addSommet(Sommet s);
           void addFace(Face f);
           void addNormale(Normale n);
           void afficher();
    protected:
             std::vector<Sommet> positions;
             std::vector<Face> faces;
             std::vector<Normale> normales; 

    
};

#endif