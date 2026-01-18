#include "Application.h"

#include <glm/glm.hpp>

#include <cassert>
#include <iostream>

namespace Core {

	static Application* s_Application = nullptr;

	Application::Application(const ApplicationSpecification& specification)
		: m_Specification(specification)
	{
		s_Application = this;

		// Set window title to app name if empty
		if (m_Specification.WindowSpec.Title.empty())
			m_Specification.WindowSpec.Title = m_Specification.Name;

		m_Window = std::make_shared<Window>(m_Specification.WindowSpec);
		m_Window->Create();
	}

	Application::~Application()
	{
		m_Window->Destroy();

		s_Application = nullptr;
	}

	void Application::Run()
	{
		m_Running = true;

		float lastTime = GetTime();

		// Main Application loop
		while (m_Running)
		{
			while (std::optional<sf::Event> event = m_Window->GetHandle()->pollEvent())
			{
				if (event->is<sf::Event::Closed>())
					m_Window->Close();
				
				for (const std::unique_ptr<Layer>& layer : m_LayerStack)
					layer->OnEvent(*event);
			}			

			if (m_Window->ShouldClose())
			{
				Stop();
				break;
			}

			float currentTime = GetTime();
			float dt = glm::clamp(currentTime - lastTime, 0.001f, 0.1f);
			lastTime = currentTime;

			// Main layer update here
			for (const std::unique_ptr<Layer>& layer : m_LayerStack)
				layer->OnUpdate(dt);
			
			
			m_Window->Clear();
			
			// NOTE: rendering can be done elsewhere (eg. render thread)
			for (const std::unique_ptr<Layer>& layer : m_LayerStack)
				layer->OnRender();

			m_Window->Display();
		}
	}

	void Application::Stop()
	{
		m_Running = false;
	}

	glm::vec2 Application::GetFrameSize() const
	{
		return m_Window->GetWindowSize();
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
