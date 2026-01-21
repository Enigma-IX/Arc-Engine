#pragma once

#include "Layer.h"
#include "Window.h"

#include <string>
#include <memory>
#include <vector>

namespace Core {

	struct ApplicationSpecification
	{
		std::string Name = "Application";
		WindowSpecification WindowSpec;
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& specification = ApplicationSpecification());
		~Application();

		void Run();
		void Stop();

		template<typename TLayer>
		requires(std::is_base_of_v<Layer, TLayer>)
		void PushLayer()
		{
			m_layerStack.push_back(std::make_unique<TLayer>());
			m_layerStack.back()->OnAttach();			
		}
		
		template<typename TLayer>
		requires(std::is_base_of_v<Layer, TLayer>)
		void PopLayer()
		{
			for (auto it = m_layerStack.begin(); it != m_layerStack.end(); ++it)
			{
				if (dynamic_cast<TLayer*>(it->get()))
				{
					(*it)->OnDetach();
					m_layerStack.erase(it);
					return;
				}
			}
		}
		
		template<typename TLayer>
		requires(std::is_base_of_v<Layer, TLayer>)
		TLayer* GetLayer()
		{
			for (const auto& layer : m_layerStack)
			{
				if (typeid(*layer.get()) == typeid(TLayer))
					return static_cast<TLayer*>(layer.get());
			}
			return nullptr;
		}
		
		std::shared_ptr<Window> GetWindow() const { return m_window; }
		glm::vec2 GetFrameSize() const;

		static Application& Get();
		static float GetTime();
	private:
		ApplicationSpecification m_specification;
		std::shared_ptr<Window> m_window;
		bool m_Running = false;

		std::vector<std::unique_ptr<Layer>> m_layerStack;
	};

}