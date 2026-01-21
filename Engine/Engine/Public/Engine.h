#pragma once

#include "Layer.h"
#include "Systems/InputSystem.h"

namespace Engine
{
    class Engine : public Core::Layer
    {
    public:
        Engine();
        virtual ~Engine() override = default;

        virtual void OnUpdate(float dt) override;
        virtual void OnRender() override;
        virtual void OnEvent(sf::Event& event) override;
        
    private:
        std::unique_ptr<InputSystem> m_InputSystem;
        //RendererSystem* m_RendererSystem;
        //PhysicsSystem* m_PhysicsSystem;
        //TimeSystem* m_TimeSystem;

    };
}
