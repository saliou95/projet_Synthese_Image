#include "Arbre.h"

        Arbre::Arbre()
        {

        }

        Primtv Arbre::getPrimtv(int i)
        {

        return lesPrimitives[i];

        }

        void Arbre::addPrimtv( Primtv p)
        {
        lesPrimitives.push_back(p);

        }

        int Arbre::getTaille()
        {
                return lesPrimitives.size();
        }

        void Arbre::afficherArbre()

        {


        }

        void Arbre::afficherLesPrimtv()
        {




        }