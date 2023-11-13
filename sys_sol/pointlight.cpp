#include "pointlight.h"

PointLight::PointLight(glm::vec3 col,glm::vec3 pos,float pow)
{
    color = col;
    position = pos;
    power = pow;
}
void PointLight::Bind(Shader shader){
    shader.setUniform3fv("lightcolor",color);
    shader.setUniform3fv("lightpos",position);
    shader.setUniform1f("lightpow",power);
}
void PointLight::Unbind(){

}
