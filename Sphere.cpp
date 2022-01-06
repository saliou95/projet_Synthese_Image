#define _USE_MATH_DEFINES
#include <cmath>
#include "Sphere.h"
using namespace std;
using namespace glm;
#ifndef PI
#define PI 3.14159265358979323846
#endif
  void Sphere::init(GLfloat rayon,int pas, int sectors) // pour tester prendre par exemple rayon = 1, pas= 50 et sectors = 50
  {
    float p = 1./(float)(pas-1);
    float S = 1./(float)(sectors-1);
    Sommet sommet;
    for(int r=0; r<pas;++r) {
        for(int s=0;s<sectors;++s) {
            GLfloat y = rayon*sin(-M_PI_2 + M_PI *r*p);
            GLfloat x = rayon*cos(2*PI*s*S)*sin(PI*r*p );
            GLfloat z = rayon*sin(2*PI*s*S)*sin(PI*r*p );
            sommet.x=x;
            sommet.y=y;
            sommet.z=z;
            addSommet(sommet);
            int curRow = r * sectors;
            int nextRow = (r+1) * sectors;
            if(r<pas-1) {
              Face face;
              face.indiceS1 = curRow + s;
              face.indiceS2 = nextRow + s;
              face.indiceS3 = nextRow + (s+1);
              Face face2;
              addFace(face);
              face2.indiceS1 = curRow + s;
              face2.indiceS2 = nextRow + (s+1);
              face2.indiceS3 = curRow + (s+1);
              addFace(face2);
            }
            
        }
    }
}

        
          
  


      



