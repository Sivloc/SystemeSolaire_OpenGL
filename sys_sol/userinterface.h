#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "pointlight.h"
#include "object.h"
#include "shader.h"
#include "imgui/imgui.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class UserInterface
{
public:
    UserInterface(PointLight Light,Object o,GLFWwindow window);
    void Bind(Shader shader);
    void Draw();
private:
    PointLight m_pl;
    Object m_o;
    glm::vec3 m_ambientLightColor;
};

#endif // USERINTERFACE_H
