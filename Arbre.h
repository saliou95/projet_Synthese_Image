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
           
           void Changeshow(int i); // change l'affichage ou non dun groupe

           void addPrimtv(Primtv p,int j);//ajouter une primitive a au groupe j
          
           void removePrimtv (int i,int j); //enleve la pimitive i dans le groupe j
         
           void removeAllPrimtiv(int j); //supprime toutes les primitives de j
           
           void ChangeshowPrimtv(int i,int j);// change l'affichage ou non affcihage de la primitive i du groupe j

           void translater(glm::vec3,int i,int j);//translation de la primitive i du groupe j
       
           void roter(float angle,glm::vec3 rotmat,int i ,int j);//rotaion de la primitive i du groupe j
         
           void scaler(glm::vec3 scamat,int i,int j);//mise a echelle de la primitive i du groupe j

           void translaterg(glm::vec3,int i);//translation  du groupe i
       
           void roterg(float angle,glm::vec3 rotmat,int i );//rotation du groupe i

           void scalerg(glm::vec3 scamat,int i);//mise a echelle du groupe i
    protected:
             std::vector<Groupe> lesGroupe;
            
       
           
                 
};

#endif