#include "Engine.h"

namespace Engine
{
	Engine::Engine()
	{
		m_InputSystem = new InputSystem();
	}

	void Engine::OnUpdate(float dt)
	{
		// m_TimeSystem->Update(dt);
		// m_PhysicsSystem->Update(*m_ActiveScene, dt);
		// m_ActiveScene->Update(dt);
	}

	void Engine::OnRender()
	{
		// m_RendererSystem->Render();
	}

	void Engine::OnEvent(sf::Event& event)
	{
		m_InputSystem->ProcessEvent(event);
	}
}
	
