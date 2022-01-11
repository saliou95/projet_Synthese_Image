#ifndef DEF_GROUPE
#define DEF_GROUPE


#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Primtv.h"
#include <string>

class Groupe 
{
    public:
           Groupe();
           Groupe(std::string n);
           glm::mat4 getmodel();
           Primtv getPrimtv(int i);

           void setNom(std::string s);

           int getTaille();

           void addPrimtv(Primtv p);
          
           void removePrimtv (int i); 
         
           void removeAll(); 
           
           void Changeshow(int i);

           void afficherLesPrimtv();
           
           void translater(glm::vec3,int i);
       
           void roter(float angle,glm::vec3 rotmat,int i );
         
           void scaler(glm::vec3 scamat,int i);

           void translaterg(glm::vec3);
       
           void roterg(float angle,glm::vec3 rotmat);
         
           void scalerg(glm::vec3 scamat);
    protected:
             std::vector<Primtv> lesPrimitives;

              glm::mat4 rotmodel=glm::mat4(1.0f);
             glm::mat4 transmodel=glm::mat4(1.0f);
             glm::mat4 scamodel=glm::mat4(1.0f);
    public:
             int show=1;
             std::string nom;
           
                 
};

#endif