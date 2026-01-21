#include "Application.h"

#include <glm/glm.hpp>

#include <cassert>
#include <iostream>

namespace Core {

	static Application* s_Application = nullptr;

	Application::Application(const ApplicationSpecification& specification)
		: m_specification(specification)
	{
		s_Application = this;

		// Set window title to app name if empty
		if (m_specification.WindowSpec.Title.empty())
			m_specification.WindowSpec.Title = m_specification.Name;

		m_window = std::make_shared<Window>(m_specification.WindowSpec);
		m_window->Create();
	}

	Application::~Application()
	{
		m_window->Destroy();

		s_Application = nullptr;
	}

	void Application::Run()
	{
		m_Running = true;

		float lastTime = GetTime();

		// Main Application loop
		while (m_Running)
		{
			while (std::optional<sf::Event> event = m_window->GetHandle()->pollEvent())
			{
				if (event->is<sf::Event::Closed>())
					m_window->Close();
				
				for (const std::unique_ptr<Layer>& layer : m_layerStack)
					layer->OnEvent(*event);
			}			

			if (m_window->ShouldClose())
			{
				Stop();
				break;
			}

			const float currentTime = GetTime();
			const float dt = glm::clamp(currentTime - lastTime, 0.001f, 0.1f);
			lastTime = currentTime;

			// Main layer update here
			for (const std::unique_ptr<Layer>& layer : m_layerStack)
				layer->OnUpdate(dt);
			
			
			m_window->Clear();
			
			// NOTE: rendering can be done elsewhere (e.g. render thread)
			for (const std::unique_ptr<Layer>& layer : m_layerStack)
				layer->OnRender();

			m_window->Display();
		}
	}

	void Application::Stop()
	{
		m_Running = false;
	}

	glm::vec2 Application::GetFrameSize() const
	{
		return m_window->GetWindowSize();
	}

	Application& Application::Get()
	{
		assert(s_Application);
		return *s_Application;
	}

	float Application::GetTime()
	{
		static sf::Clock clock;
		return clock.getElapsedTime().asSeconds();		
	}
}
