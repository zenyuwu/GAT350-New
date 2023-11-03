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
        //m_scene->Load("scenes/scene.json");
        m_scene->Load("scenes/test.json");
        m_scene->Initialize();

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

        //{ //creating squirrel
        //    auto actor = CREATE_CLASS(Actor);
        //    actor->name = "actor1";
        //    actor->transform.position = glm::vec3{ 0, 0, 0 };
        //    auto modelComponent = CREATE_CLASS(ModelComponent);
        //    modelComponent->model = std::make_shared<Model>();
        //    modelComponent->model->SetMaterial(GET_RESOURCE(Material, "materials/phong.mtrl"));
        //    modelComponent->model->Load("models/squirrel.glb", glm::vec3{ 0, -0.7f, 0 }, glm::vec3{ 0 }, glm::vec3{ 0.4f });
        //    actor->AddComponent(std::move(modelComponent));
        //    m_scene->Add(std::move(actor));
        //}

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
        //weirdge maple testing
        m_time += dt;

        ENGINE.GetSystem<Gui>()->BeginFrame();

        m_scene->Update(dt);
        m_scene->ProcessGui();

        auto actor = m_scene->GetActorByName<Actor>("actor1");

        //add in the transforms based on user input
        //actor->transform.position.x etcetc

        //broken :((
        auto model = actor->GetComponent<ModelComponent>()->model;
        auto material = model->GetMaterial();

        material->ProcessGui();
        material->Bind();

        material = GET_RESOURCE(Material, "materials/refraction.mtrl");
        if (material) {
            ImGui::Begin("Refraction");

            //weirdge maple testing
            m_refraction = 1 + std::fabs((std::sin(m_time)));

            ImGui::DragFloat("IOR", &m_refraction, 0.01f, 1, 3);
            auto program = material->GetProgram();
            program->Use();
            program->SetUniform("ior", m_refraction);

            ImGui::End();
        }

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
