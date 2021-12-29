#include "Translation.h"
using namespace std;
using namespace glm;

mat4 Translation::translater(glm::mat4 lemodel,glm::vec3 transvect)
{
   model=translate(lemodel,transvect);
return model;
   
}