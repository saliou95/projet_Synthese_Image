#include "Arbre.h"

        Arbre::Arbre()
        {

        }

        Primtv Arbre::getPrimtv(int i)
        {

        return lesPrimitives[i];

        }
          int Arbre::getTaille()
        {
                return lesPrimitives.size();
        }

        void Arbre::addPrimtv( Primtv p)
        {
         lesPrimitives.push_back(p);
        }

        void Arbre::Changeshow(int i)
        {
            if(lesPrimitives[i].show==1)
                lesPrimitives[i].show=0;
            else
                lesPrimitives[i].show=1;
        }

        void Arbre::removePrimtv(int i)
        {
          lesPrimitives.erase(lesPrimitives.begin()+i);
        }

        void Arbre:: removeAll()
        {
         lesPrimitives.clear(); 

        } 


      
        void Arbre::afficherLesPrimtv()
        {




        }
        //cstr from string to char 