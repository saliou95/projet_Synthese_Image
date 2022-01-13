#define _USE_MATH_DEFINES
#include <cmath>
#include "Sphere.h"
using namespace std;
using namespace glm;


  void Sphere::init(GLfloat rayon,int pas) // pour tester prendre par exemple rayon = 1, pas= 50 et sectors = 50
  {
     nom="Sphere";

    float p =((GLfloat)radians(360.f))/(float)(pas);
    float S = ((GLfloat)radians(180.f))/(float)(pas);
    Sommet sommet;

    
      for (int j =0;j<=pas;j++ )
      for (int i =0;i<=pas;i++ )
      {
            float pp=-((GLfloat)radians(180.f))+(p*i);
            float SS=-((GLfloat)radians(90.f))+S*j;
            GLfloat y = rayon*sin(pp)*cos(SS);
            GLfloat x = rayon*cos(pp)*cos(SS);
            GLfloat z = rayon*sin(SS);
           
        
            sommet.x=x;
            sommet.y=y;
            sommet.z=z;
            addSommet(sommet);

            Face f;
        Face f2;
        f.indiceS1=(unsigned int)((i*(pas))+ j);   
        f.indiceS2=(unsigned int)((i+1)*(pas)+ (j));
        f.indiceS3=(unsigned int)(((i+1)*(pas))+ (j+1));

        f2.indiceS1=(unsigned int)((i*(pas))+ j);
        f2.indiceS2=(unsigned int)(((i+1)*(pas))+ (j+1));
        f2.indiceS3=(unsigned int)(((i)*(pas))+ (j+1));

          Normale n;
        n.x =(cos(pp))*cos(SS);
        n.y =(cos(pp))*cos(SS);
        n.z =(sin(SS));
        addNormale(n);
        addFace(f);
        addFace(f2);

      }
   
 
    
            
 }
    


        
          
  


      



