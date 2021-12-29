#ifndef DEF_ROTATION
#define DEF_ROTATION
#include "Transformation.h"

class Rotation: public Transformation
{
    public:
          glm::mat4 Roter(glm::mat4 lemodel,float angle,glm::vec3 rotmat );
        
    protected:
            
};

#endif