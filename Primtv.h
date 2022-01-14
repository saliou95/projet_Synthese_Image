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

// Classe générique d'une primitive
class Primtv
{
    public:
           Primtv();

           std::vector<Sommet> getPositions(); // Récupére la liste des sommets de la primitive
           std::vector<Face> getFaces(); // Récupére liste des faces de la primitive
           std::vector<Normale> getNormales(); // Récupère la liste des Normales de la primitives
           glm::mat4 getmodel();
       
           void afficher();
           void addSommet(Sommet s);    // Ajoute un sommet à la liste des sommets
           void addFace(Face f);        // Ajout une face à la liste des faces
           void addNormale(Normale n);  // Ajoute une normale à la liste des normales
           void miaech(glm::vec3 scamat );
           void translater(glm::vec3 transvect ); // Appliquer une translation du la primitive
           void roter(float angle,glm::vec3 rotmat ); // Appliquer une rotation sur la primitive
           void Changeshow();                         // Afficher ou cacher la primitive
    protected:
             std::vector<Sommet> positions; // la liste des sommets de la primitive
             std::vector<Face> faces;       // liste des faces de la primitive
             std::vector<Normale> normales; // liste des Normales de la primitives
          
           //  glm::mat4 model=glm::mat4(1.0);
             glm::mat4 rotmodel=glm::mat4(1.0f);        // Initialisation de la matrice de rotation
             glm::mat4 transmodel=glm::mat4(1.0f);      
             glm::mat4 scamodel=glm::mat4(1.0f);
    public:
             int show=1;
             std::string nom;
};

#endif