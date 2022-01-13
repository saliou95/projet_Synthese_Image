#include "Groupe.h"

using namespace std;
using namespace glm;
        Groupe::Groupe()
        {
            nom="groupe";
        }

        Groupe::Groupe(std::string n)
        {
            nom=n;
        }
        void Groupe::setNom(std::string s) {
              nom = s;
        }

        Primtv Groupe::getPrimtv(int i)
        {

        return lesPrimitives[i];

        }
          int Groupe::getTaille()
        {
                return lesPrimitives.size();
        }

        void Groupe::addPrimtv( Primtv p)
        {
         lesPrimitives.push_back(p);
        }

        void Groupe::removePrimtv(int i)
        {
          lesPrimitives.erase(lesPrimitives.begin()+i);
        }


        void Groupe:: removeAll()
        {
         lesPrimitives.clear(); 

        } 

    void Groupe::Changeshow(int i)
        {
            if(lesPrimitives[i].show==1)
                lesPrimitives[i].show=0;
            else
                lesPrimitives[i].show=1;
        }
        void Groupe::translater(vec3 vec,int i)
        {
          lesPrimitives[i].translater(vec);

        }   
        void Groupe::roter(float angle,glm::vec3 rotmat,int i) 
        {

          lesPrimitives[i].roter(angle,rotmat);
        }
      

       void Groupe::scaler(glm::vec3 scamat,int i)
       {
         lesPrimitives[i].miaech(scamat);
       }
    


 void Groupe::scalerg(glm::vec3 scamat )
        {
            scamodel=scale(scamodel,scamat);

        }



        void Groupe::translaterg(glm::vec3 transvect)
        {
            transmodel=translate(transmodel,transvect);
        
        }

    
        void Groupe::roterg(float angle,glm::vec3 rotmat )
        {
             rotmodel=rotate(rotmodel,glm::radians(angle),rotmat);

        }

        mat4 Groupe::getmodel()
        {


            return scamodel*transmodel*rotmodel ;
        }
        //cstr from string to char 