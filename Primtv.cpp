#include "Primtv.h"

using namespace std;
using namespace glm;

     
       Primtv::Primtv()
        {
            
            
        }

  
        vector<Sommet> Primtv::getPositions()
        {
            return positions;
        }

        vector<Face> Primtv:: getFaces()
        {
            return faces;
        }

        vector<Normale> Primtv::getNormales()
        {
            return normales;
        }
          

        void Primtv::afficher()
        {
            cout<<"-----------Les Coordonnées des points----------" <<endl;

            for(Sommet i:positions)
                cout << i.x<<"  "<<i.y<<" "<<i.z<< endl;

            cout<<"-------------Les indices par faces-------------" <<endl;
            
            for(Face i:faces)
                cout << i.indiceS1<<"  "<<i.indiceS2<<" "<<i.indiceS3<< endl;
            
            cout<<"-----------------Le normales------------------" <<endl;

            for(Normale i:normales)
                cout << i.x<<"  "<<i.y<<" "<<i.z<< endl;

        }


        void Primtv::addSommet(Sommet s)
        {
            positions.push_back(s);

        }
        
        void Primtv::addFace(Face f)
        {
            faces.push_back(f);
            
        }

        void Primtv::addNormale(Normale n)
        {
            normales.push_back(n);
    
        }

        void Primtv::miaech(glm::vec3 scamat )
        {
            scamodel=scale(scamodel,scamat);

        }



        void Primtv::translater(glm::vec3 transvect)
        {
            transmodel=translate(transmodel,transvect);
        
        }

    
        void Primtv::roter(float angle,glm::vec3 rotmat )
        {
             rotmodel=rotate(rotmodel,glm::radians(angle),rotmat);

        }

        void Primtv::echeller(glm::vec3 scalemat) {
            echellemodel=scale(echellemodel, scalemat);
            cout<<"HEYYY"<<endl;
        }

        mat4 Primtv::getmodel()
        {
            return scamodel*transmodel*rotmodel*echellemodel ;
        }
