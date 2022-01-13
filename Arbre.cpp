#include "Arbre.h"
using namespace std;
using namespace glm;
        Arbre::Arbre()
        {

        }

        Groupe Arbre::getGroupe(int i)
        {

        return lesGroupe[i];

        }
          int Arbre::getTaille()
        {
                return lesGroupe.size();
        }

        void Arbre::addGroupe( Groupe p)
        {
         lesGroupe.push_back(p);
        }

        void Arbre::removeGroupe(int i)
        {
          lesGroupe.erase(lesGroupe.begin()+i);
        }


        void Arbre:: removeAll()
        {
         lesGroupe.clear(); 

        } 

    void Arbre::Changeshow(int i)
        {
            if(lesGroupe[i].show==1)
                lesGroupe[i].show=0;
            else
                lesGroupe[i].show=1;
        }






        void Arbre::addPrimtv( Primtv p,int j)
        {
           lesGroupe[j].addPrimtv(p);
        }

        void Arbre::removePrimtv(int i,int j)
        {
          lesGroupe[i].removePrimtv(j);
        }


        void Arbre:: removeAllPrimtiv(int j)
        {
          lesGroupe[j].removeAll(); 

        } 

    void Arbre::ChangeshowPrimtv(int i,int j)
        {
          lesGroupe[i].Changeshow(j);
        }


        void Arbre::translater(vec3 vec,int i,int j)
        {
          lesGroupe[i].translater(vec,j);

        }   
        void Arbre::roter(float angle,glm::vec3 rotmat,int i,int j) 
        {

          lesGroupe[i].roter(angle,rotmat,j);
        }
      

       void Arbre::scaler(glm::vec3 scamat,int i,int j)
       {
         lesGroupe[i].scaler(scamat,j);
       }



        void Arbre::translaterg(vec3 vec,int i)
        {
          lesGroupe[i].translaterg(vec);

        }   
        void Arbre::roterg(float angle,glm::vec3 rotmat,int i) 
        {

          lesGroupe[i].roterg(angle,rotmat);
        }
      

       void Arbre::scalerg(glm::vec3 scamat,int i)
       {
         lesGroupe[i].scalerg(scamat);
       }
       
        //cstr from string to char 