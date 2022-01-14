
#include "Cylindre.h"
using namespace std;
using namespace glm;
    
  void Cylindre::init(GLfloat R, int nbtgr,int nbtpr)
  {
    nom="Cylindre";
   
    GLfloat theta, phi;
    theta = 1/((GLfloat)nbtgr);
    phi = ((GLfloat)(radians(360.f)))/((GLfloat)nbtpr);
  	
    for (int i =-1;i<=nbtgr;i++ )
      for (int j =0;j<=nbtpr;j++ )
      {
        //calcule des sommets et normal
        GLfloat a=(GLfloat)j*phi;
      
        Sommet s;
        if(i==-1||i==nbtgr)
        {
                  s.x =0.;
                  if(i==-1)
        s.y =(i+1)*theta;
        else
        s.y =(i-1)*theta;
        s.z =0.;
        
        addSommet(s);
        Normale n;
        n.x =0;
        n.y =i*theta;
        n.z =0;
        addNormale(n);
        }
        else
        {
        s.x =R*cos(a);
        s.y =i*theta;
        s.z =(R*sin(a));
        
        addSommet(s);
        Normale n;
        n.x =(cos(a));
        n.y =i*theta;
        n.z =(sin(a));
        addNormale(n);
        }
      }

//calcules des faces
    for (int i =-1;i<=nbtgr;i++)
      for (int j =0;j<nbtpr;j++) 
      { 	
        Face f;
        Face f2;
        f.indiceS1=(unsigned int)((i*(nbtpr+1))+ j);   
        f.indiceS2=(unsigned int)((i+1)*(nbtpr+1)+ (j));
        f.indiceS3=(unsigned int)(((i+1)*(nbtpr+1))+ (j+1));
        f2.indiceS1=(unsigned int)((i*(nbtpr+1))+ j);
        f2.indiceS2=(unsigned int)(((i+1)*(nbtpr+1))+ (j+1));
        f2.indiceS3=(unsigned int)(((i)*(nbtpr+1))+ (j+1));
        addFace(f);
        addFace(f2);
      }
    
}

        
          
  


      



