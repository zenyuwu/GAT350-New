#include "World04.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/color_space.hpp>
#define INTERLEAVE
namespace nc
{
    bool World04::Initialize()
    {
        //auto material = GET_RESOURCE(Material, "materials/multi_grid.mtrl");
        //m_model = std::make_shared<Model>();
        //m_model->SetMaterial(material);
        //m_model->Load("models/plane.obj", glm::vec3{0, -3, -5}, glm::vec3{90, 0, 0});

        m_material = GET_RESOURCE(Material, "materials/multi_grid.mtrl");
        m_model = std::make_shared<Model>();
        m_model->Load("models/plane.obj", glm::vec3{ 0, -0.7f, 0 }, glm::vec3{ 0 }, glm::vec3{ 0.4f });

        std::cout << m_lights.size() << "\n";
        m_lights.push_back(light_t{});

        std::cout << "numLights: " + std::to_string(numLights) + "\n";
        std::cout << m_lights.size() << "\n";

        for (int i = 0; i < numLights; i++) {
            m_lights[i].type = light_t::eType::Point;
            m_lights[i].position = glm::vec3{ randomf(-5, 5), randomf(1, 8), randomf(-5, 5) };
            m_lights[i].direction = glm::vec3{ 0, -1, 0 };
            m_lights[i].color = glm::rgbColor(glm::vec3{ randomf(), 1, 1 });
            m_lights[i].intensity = randomf(0.1f, 9.9f);
            m_lights[i].range = 12;
            m_lights[i].innerAngle = 10.0f;
            m_lights[i].outerAngle = 30.0f;
        }

        ambientLight = glm::vec3{ 0 };
        return true;
    }
    void World04::Shutdown()
    {
    }
    void World04::Update(float dt)
    {
        ENGINE.GetSystem<Gui>()->BeginFrame();
        //OBJECT
        ImGui::Begin("Scene");
        ImGui::ColorEdit3("Ambient Color", glm::value_ptr(ambientLight));
        ImGui::Separator();

        int lightToRemove = -1;
        for (int i = 0; i < numLights; i++)
        {
            std::string name = "light" + std::to_string(i);
            if (ImGui::Selectable(name.c_str(), m_selected == i)) m_selected = i;
            if (ImGui::Button(("X" + std::to_string(i)).c_str()) && numLights > 1) {
                lightToRemove = i;
            }
            ImGui::Separator();
        }
        if (ImGui::Button("Add Light") && numLights < 9) {
            m_lights.push_back(light_t{});
            m_lights.back().type = light_t::eType::Spot;
            m_lights.back().position = glm::vec3{ -0.09f, 3.0f, -3.3f };
            m_lights.back().direction = glm::vec3{ 0.0f, -1.0f, 0.0f };
            m_lights.back().color = glm::vec3{ 1.0f, 1.0f, 1.0f };
            m_lights.back().intensity = 1.0f;
            m_lights.back().range = 10.0f;
            m_lights.back().innerAngle = 10.0f;
            m_lights.back().outerAngle = 30.0f;
            numLights++;
        }
        ImGui::End();

        if (lightToRemove != -1) {
            m_lights.erase(m_lights.begin() + lightToRemove);
            numLights--;
            m_selected = 0;
        }

        //LIGHT
        ImGui::Begin("Light");
        const char* types[] = { "Point", "Directional", "Spot" };
        ImGui::Combo("Type", (int*)&m_lights[m_selected].type, types, 3);
        if (m_lights[m_selected].type != light_t::Directional) ImGui::DragFloat3("Position", glm::value_ptr(m_lights[m_selected].position), 0.1f);
        if (m_lights[m_selected].type != light_t::Point) ImGui::DragFloat3("Direction", glm::value_ptr(m_lights[m_selected].direction), 0.1f);
        if (m_lights[m_selected].type == light_t::Spot) {
            ImGui::DragFloat("Intensity", &m_lights[m_selected].intensity, 0.1f, 0, 10);
            ImGui::DragFloat("Range", &m_lights[m_selected].range, 0.1f, 0, 20);
            ImGui::DragFloat("Inner Angle", &m_lights[m_selected].innerAngle, 1, 0, 90);
            ImGui::DragFloat("Outer Angle", &m_lights[m_selected].outerAngle, 1, 0, 90);
        }
        ImGui::ColorEdit3("Color", glm::value_ptr(m_lights[m_selected].color));
        //ImGui::ColorEdit3("AmbientColor", glm::value_ptr(ambientLight));
        ImGui::End();
        //uhh setting stuff in the material?
        m_material->ProcessGui();
        m_material->Bind();

        m_material->GetProgram()->SetUniform("numLights", numLights);

        //light uniforms
        for (int i = 0; i < numLights; i++) {
            std::string name = "lights[" + std::to_string(i) + "]";
            m_material->GetProgram()->SetUniform(name + ".type", m_lights[i].type);
            m_material->GetProgram()->SetUniform(name + ".position", m_lights[i].position);
            m_material->GetProgram()->SetUniform(name + ".direction", m_lights[i].direction);
            m_material->GetProgram()->SetUniform(name + ".color", m_lights[i].color);
            m_material->GetProgram()->SetUniform(name + ".intensity", m_lights[i].intensity);
            m_material->GetProgram()->SetUniform(name + ".range", m_lights[i].range);
            m_material->GetProgram()->SetUniform(name + ".innerAngle", glm::radians(m_lights[i].innerAngle));
            m_material->GetProgram()->SetUniform(name + ".outerAngle", glm::radians(m_lights[i].outerAngle));
        }
        m_material->GetProgram()->SetUniform("ambientLight", ambientLight);
        //model matrix
        m_material->GetProgram()->SetUniform("model", m_transform.GetMatrix());
        //view matrix
        glm::mat4 view = glm::lookAt(glm::vec3{ 0, 0, 3 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 });
        m_material->GetProgram()->SetUniform("view", view);
        //projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(70.0f), ENGINE.GetSystem<Renderer>()->GetWidth() / (float)ENGINE.GetSystem<Renderer>()->GetHeight(), 0.01f, 100.0f);
        m_material->GetProgram()->SetUniform("projection", projection);
        ENGINE.GetSystem<Gui>()->EndFrame();
    }

    void World04::Draw(Renderer & renderer)
    {
        // pre-render
        renderer.BeginFrame();
        // render
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        m_material->Bind();
        m_model->Draw();
        ENGINE.GetSystem<Gui>()->Draw();
        // post-render
        renderer.EndFrame();
    }
}