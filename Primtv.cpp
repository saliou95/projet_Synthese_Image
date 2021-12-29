#include "Primtv.h"
using namespace std;


     
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
            cout<<"-----------Les Coordonner des points----------" <<endl;

            for(Sommet i:positions)
                cout << i.x<<"  "<<i.y<<" "<<i.z<< endl;

            cout<<"-------------Les indice par faces-------------" <<endl;
            
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




