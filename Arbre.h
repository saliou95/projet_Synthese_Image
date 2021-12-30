#ifndef DEF_ARBRE
#define DEF_ARBRE

#include <iostream>
#include <math.h>
#include <cstdlib>
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
          
           void afficherArbre();
           
           void afficherLesPrimtv();
           
           
           
    protected:
             std::vector<Primtv> lesPrimitives;

             
       
           
                 
};

#endif