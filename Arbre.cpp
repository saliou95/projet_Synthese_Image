#include "Arbre.h"
using namespace std;
using namespace glm;
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

        void Arbre::removePrimtv(int i)
        {
          lesPrimitives.erase(lesPrimitives.begin()+i);
        }


        void Arbre:: removeAll()
        {
         lesPrimitives.clear(); 

        } 

    void Arbre::Changeshow(int i)
        {
            if(lesPrimitives[i].show==1)
                lesPrimitives[i].show=0;
            else
                lesPrimitives[i].show=1;
        }
        void Arbre::translater(vec3 vec,int i)
        {
          lesPrimitives[i].translater(vec);

        }   
        void Arbre::roter(float angle,glm::vec3 rotmat,int i) 
        {

          lesPrimitives[i].roter(angle,rotmat);
        }
      

       void Arbre::scaler(glm::vec3 scamat,int i)
       {
         lesPrimitives[i].miaech(scamat);
       }
        void Arbre::afficherLesPrimtv()
        {




        }
        //cstr from string to char 