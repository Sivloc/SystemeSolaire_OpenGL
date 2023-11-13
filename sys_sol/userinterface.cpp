#include "userinterface.h"

UserInterface::UserInterface(PointLight Light, Object o, GLFWwindow window)
    : m_pl(Light), m_o(o), m_window(window)
{
    m_ambientLightColor = glm::vec3(1.0f, 1.0f, 1.0f); // Exemple de couleur ambiante
}

void UserInterface::Bind(Shader shader)
{
    // Bind des éléments nécessaires
}

void UserInterface::Draw()
{
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_Once);

    ImGui::Text("Hello, world %d", 123);
    if (ImGui::Button("Save"))
        MySaveFunction();
    ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

    // Ajoutez d'autres éléments d'interface utilisateur ImGui ici selon vos besoins

    ImGui::End();
}
