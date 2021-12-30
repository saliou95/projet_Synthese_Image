
#include "Cube.h"
using namespace std;
using namespace glm;
Sommet creerSommet(float x, float y, float z);
static int facesIndices[] = { 
         0,2,1,
         1,2,6,
         3,4,7,
         7,4,5,
         7,5,2,
         2,5,6,
         3,0,4,
         4,0,1,
         3,7,0,
         0,7,2,
         4,1,5,
         5,1,6
         }; 
  void Cube::init(GLfloat L,GLfloat l)
  {
    static const GLfloat vertex3d[] = {

        -1*L, -1*l,  1*l, //0
        -1*L,  1*l,  1*l, //1
         1*L, -1*l,  1*l, //2
        -1*L, -1*l, -1*l, //3
        -1*L,  1*l, -1*l, //4
         1*L,  1*l, -1*l, //5      
         1*L,  1*l,  1*l, //6
         1*L, -1*l, -1*l  //7
         };
    for(int i=0; i<32; i=i+3) {
      Sommet s = creerSommet(vertex3d[i], vertex3d[i+1], vertex3d[i+2]);
      addSommet(s);
      cout<<i<<" "<<vertex3d[i]<<" "<<vertex3d[i+1]<<" "<< vertex3d[i+2]<<" "<<endl;
    }
    for(int i=0; i<36; i=i+3) {
      Face face;
      face.indiceS1=facesIndices[i];
      face.indiceS2=facesIndices[i+1];
      face.indiceS3=facesIndices[i+2];
      addFace(face);
    }


  }
  Sommet creerSommet(float x, float y, float z) {
    Sommet s;
    s.x=x;
    s.y=y;
    s.z=z;
    return s;
  }


        
          
  


      



