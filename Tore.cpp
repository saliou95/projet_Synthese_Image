
#include "Tore.h"
using namespace std;
using namespace glm;
    
  void Tore::init(GLfloat R, GLfloat r,int nbtgr,int nbtpr)
  {
    GLfloat theta, phi;
    theta = ((GLfloat)radians(360.f))/((GLfloat)nbtgr);
    phi = ((GLfloat)(radians(360.f)))/((GLfloat)nbtpr);
  	
    for (int i =0;i<=nbtgr;i++ )
      for (int j =0;j<=nbtpr;j++ )
      {
        GLfloat a=(GLfloat)j*phi;
        GLfloat b=(GLfloat)i*theta;
        Sommet s;

        s.x =(R+r*cos(a))*cos(b);
        s.y =(R+r*cos(a))*sin(b);
        s.z =(r*sin(a));
        addSommet(s);
        Normale n;
        n.x =(cos(a))*cos(b);
        n.y =(cos(a))*sin(b);
        n.z =(sin(a));
        addNormale(n);
      }

    for (int i =0;i<nbtgr;i++)
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

        
          
  


      



