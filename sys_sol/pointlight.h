#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include"glm/glm.hpp"
#include"shader.h"
class PointLight
{
public:
    PointLight(glm::vec3 vec1,glm::vec3 vec2,float f);
    void Bind(Shader shader);
    void Unbind();
    glm::vec3 position;
    glm::vec3 color;
    float power;

};

#endif // POINTLIGHT_H
