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

    ImGui::Begin("Interface Graphique");

    ImGui::Text("Texte Simple");

    // Ajoutez d'autres éléments d'interface utilisateur ImGui ici selon vos besoins

    ImGui::End();
}
