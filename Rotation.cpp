#include "Rotation.h"
using namespace std;
using namespace glm;

mat4 Rotation::Roter(glm::mat4 lemodel,float angle,glm::vec3 rotmat )
{
   model=rotate(lemodel,angle,rotmat);
return model;
   
}