#include "Scale.h"
using namespace std;
using namespace glm;

mat4 Scale::miaech(glm::mat4 lemodel,glm::vec3 scamat )
{

 model=scale(lemodel,scamat);
return model;
   


}