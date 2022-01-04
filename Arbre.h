#ifndef DEF_ARBRE
#define DEF_ARBRE

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Primtv.h"


class Arbre 
{
    public:
           Arbre();

           Primtv getPrimtv(int i);

           int getTaille();

           void addPrimtv(Primtv p);
          
           void removePrimtv (int i); 
         
           void removeAll(); 
           
           void Changeshow(int i);

           void afficherLesPrimtv();
           
           void translater(glm::vec3,int i);
              
         
           
    protected:
             std::vector<Primtv> lesPrimitives;
            
       
           
                 
};

#endif