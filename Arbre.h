#ifndef DEF_ARBRE
#define DEF_ARBRE

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Groupe.h"


class Arbre 
{
    public:
           Arbre();

           Groupe getGroupe(int i); // Récupérer l'identifiant de l'arbre

           int getTaille();        // Récupérer la taille de l'arbre (Nombre de groupe de l'arbre)

           void addGroupe(Groupe p); // Ajouter un groupe à l'arbre
          
           void removeGroupe (int i); // Supprimer un groupe de l'arbre
         
           void removeAll(); // Supprimer tous les groupes de l'arbre
           
           void Changeshow(int i); // 

           void addPrimtv(Primtv p,int j);
          
           void removePrimtv (int i,int j); 
         
           void removeAllPrimtiv(int j); 
           
           void ChangeshowPrimtv(int i,int j);

           void translater(glm::vec3,int i,int j);
       
           void roter(float angle,glm::vec3 rotmat,int i ,int j);
         
           void scaler(glm::vec3 scamat,int i,int j);

           void translaterg(glm::vec3,int i);
       
           void roterg(float angle,glm::vec3 rotmat,int i );
         
           void scalerg(glm::vec3 scamat,int i);
    protected:
             std::vector<Groupe> lesGroupe;
            
       
           
                 
};

#endif