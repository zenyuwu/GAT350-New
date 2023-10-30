#include "World05.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/color_space.hpp>

#define INTERLEAVE

namespace nc
{
    bool World05::Initialize()
    {
        m_scene = std::make_unique<Scene>();

        { //creating camera
            auto actor = CREATE_CLASS(Actor);
            actor->name = "camera1";
            actor->transform.position = glm::vec3{ 0, 0, 18 };
            actor->transform.rotation = glm::vec3{ 0, 180, 0 };

            auto cameraComponent = CREATE_CLASS(CameraComponent);
            cameraComponent->SetPerspective(70.0f, (float)ENGINE.GetSystem<Renderer>()->GetWidth() / (float)ENGINE.GetSystem<Renderer>()->GetHeight(), 0.1f, 100.0f);
            actor->AddComponent(std::move(cameraComponent));

            m_scene->Add(std::move(actor));
        }

        { //creating squirrel
            auto actor = CREATE_CLASS(Actor);
            actor->name = "actor1";
            actor->transform.position = glm::vec3{ 0, 0, 0 };
            auto modelComponent = CREATE_CLASS(ModelComponent);
            modelComponent->model = std::make_shared<Model>();
            modelComponent->model->SetMaterial(GET_RESOURCE(Material, "materials/squirrel.mtrl"));
            modelComponent->model->Load("models/squirrel.glb", glm::vec3{ 0, -0.7f, 0 }, glm::vec3{ 0 }, glm::vec3{ 0.4f });
            actor->AddComponent(std::move(modelComponent));
            m_scene->Add(std::move(actor));
        }

        { //creating light
            auto actor = CREATE_CLASS(Actor);
            actor->name = "light1";
            actor->transform.position = glm::vec3{ 3, 3, 3 };
            auto lightComponent = CREATE_CLASS(LightComponent);
            lightComponent->type = LightComponent::eType::Point;
            lightComponent->color = glm::rgbColor(glm::vec3{ randomf() * 360, 1, 1 });
            lightComponent->intensity = 1;
            lightComponent->range = 20;
            lightComponent->innerAngle = 10.0f;
            lightComponent->outerAngle = 30.0f;
            actor->AddComponent(std::move(lightComponent));
            m_scene->Add(std::move(actor));
        }

        return true;
    }

    void World05::Shutdown()
    {

    }

    void World05::Update(float dt)
    {
        ENGINE.GetSystem<Gui>()->BeginFrame();

        m_scene->Update(dt);

        ImGui::Begin("Scene");
        ImGui::ColorEdit3("Ambient", glm::value_ptr(ambientColor));
        ImGui::Separator();



        for (auto& actor : m_actors)
        {
            if (ImGui::Selectable(actor->name.c_str(), actor->guiSelect))
            {
                std::for_each(m_actors.begin(), m_actors.end(), [](auto& a) { a->guiSelect = false; });
                actor->guiSelect = true;
            }
        }
        ImGui::End();



        ImGui::Begin("Inspector");
        auto iter = std::find_if(m_actors.begin(), m_actors.end(), [](auto& a) { return a->guiSelect; });
        if (iter != m_actors.end())
        {
            (*iter)->ProcessGui();
        }
        ImGui::End();

        //m_scene->ProcessGui();

        auto actor = m_scene->GetActorByName<Actor>("actor1");

        //add in the transforms based on user input
        //actor->transform.position.x etcetc

        //uhh setting stuff in the material?
        auto material = actor->GetComponent<ModelComponent>()->model->GetMaterial();
        material->ProcessGui();
        material->Bind();

        material->GetProgram()->SetUniform("ambientLight", ambientColor);

        ENGINE.GetSystem<Gui>()->EndFrame();
    }

    void World05::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();

        // render
        m_scene->Draw(renderer);
        ENGINE.GetSystem<Gui>()->Draw();

        // post-render
        renderer.EndFrame();
    }
}
