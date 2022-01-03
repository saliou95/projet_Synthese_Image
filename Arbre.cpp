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



        void Arbre::afficherLesPrimtv()
        {




        }
        //cstr from string to char 