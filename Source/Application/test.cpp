//void World04::Update(float dt)
//    {
//        ENGINE.GetSystem<Gui>()->BeginFrame();
//
//        ImGui::Begin("Transform");
//        ImGui::DragFloat3("Position", &m_transform.position[0], 0.1f);
//        ImGui::DragFloat3("Rotation", &m_transform.rotation[0], 0.1f);
//        ImGui::DragFloat3("Scale", &m_transform.scale[0], 0.1f);
//        ImGui::End();
//
//        ImGui::Begin("Light");
//        const char* types[] = { "Point", "Directional", "Spot" };
//        ImGui::Combo("Type", (int*)&m_lights[m_selected].type, types, 3);
//
//        if(m_lights[m_selected].type != light_t::Directional) ImGui::DragFloat3("Position", glm::value_ptr(m_lights[m_selected].position), 0.1f);
//        if (m_lights[m_selected].type != light_t::Point) ImGui::DragFloat3("Direction", glm::value_ptr(m_lights[m_selected].direction), 0.1f);
//        if (m_lights[m_selected].type == light_t::Spot) {
//            ImGui::DragFloat("Inner Angle", &m_lights[m_selected].innerAngle, 1, 0, 90);
//            ImGui::DragFloat("Outer Angle", &m_lights[m_selected].outerAngle, 1, 0, 90);
//        }
//        ImGui::ColorEdit3("Color", glm::value_ptr(m_lights[m_selected].color));
//        ImGui::DragFloat("Intensity", &m_lights[m_selected].intensity, 1, 0, 90);
//        if(m_lights[m_selected].type != light_t::Directional) ImGui::DragFloat("Range", &m_lights[m_selected].range, 0.1f, 0.1f, 50);
//        ImGui::ColorEdit3("AmbientColor", glm::value_ptr(ambientLight));
//        ImGui::End();
//
//        m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? m_speed * -dt : 0;
//        m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? m_speed * +dt : 0;
//        m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? m_speed * -dt : 0;
//        m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? m_speed * +dt : 0;
//
//        m_transform.rotation += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_RIGHT) ? m_speed * + dt : 0;
//        m_transform.rotation += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_LEFT) ? m_speed * - dt : 0;
//        m_time += dt;
//
//        auto material = m_model->GetMaterial();
//        material->ProcessGui();
//        material->Bind();
//
//        for (int i = 0; i < 3; i++) {
//            std::string name = "lights[" + std::to_string(i) + "].";
//            material->GetProgram()->SetUniform(name + ".type", m_lights[m_selected].type);
//            material->GetProgram()->SetUniform(name + ".position", m_lights[m_selected].position);
//            material->GetProgram()->SetUniform(name + ".direction", m_lights[m_selected].direction);
//            material->GetProgram()->SetUniform(name + ".color", m_lights[m_selected].color);
//            material->GetProgram()->SetUniform(name + ".intensity", m_lights[m_selected].intensity);
//            material->GetProgram()->SetUniform(name + ".innerAngle", glm::radians(m_lights[m_selected].innerAngle));
//            material->GetProgram()->SetUniform(name + ".outerAngle", glm::radians(m_lights[m_selected].outerAngle));
//        }
//
//
//        material->GetProgram()->SetUniform("ambientLight", ambientLight);
//        //model matrix
//        material->GetProgram()->SetUniform("model", m_transform.GetMatrix());
//
//        //view matrix
//        glm::mat4 view = glm::lookAt(glm::vec3{ 0, 0, 3 }, glm::vec3{0, 0, 0}, glm::vec3{ 0, 1, 0 });
//        material->GetProgram()->SetUniform("view", view);
//
//        //projection matrix
//        glm::mat4 projection = glm::perspective(glm::radians(70.0f), ENGINE.GetSystem<Renderer>()->GetWidth() / (float)ENGINE.GetSystem<Renderer>()->GetHeight(), 0.01f, 100.0f);
//        material->GetProgram()->SetUniform("projection", projection);
//
//        ENGINE.GetSystem<Gui>()->EndFrame();
//    }