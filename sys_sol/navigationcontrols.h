#ifndef NAVIGATIONCONTROLS_H
#define NAVIGATIONCONTROLS_H
#include "imgui/imgui.h"
#include "controls.h"
#include "userinterface.h"

class NavigationControls : public Controls
{
public:
    NavigationControls(GLFWwindow* window, Camera *camera);
    void update(float deltaTime, Shader *shader,float &PSpeed);
private:
    glm::vec2 lastPosCursor;
};

#endif // NAVIGATIONCONTROLS_H
