#ifndef DEF_TRANSLATION
#define DEF_TRANSLATION
#include "Transformation.h"

class Translation: public Transformation
{
    public:
           
        glm::mat4 translater(glm::mat4 lemodel,glm::vec3 transvect );
    protected:
            
};

#endif