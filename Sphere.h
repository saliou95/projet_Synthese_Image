#ifndef DEF_SPHERE
#define DEF_SPHERE
#include "Primtv.h"

class Sphere: public Primtv
{
    public:
        //    void init(GLfloat R,int nbPoints, float z0, float z1);
           void init(GLfloat R,int pas, int sectors);
    protected:
            
};

#endif