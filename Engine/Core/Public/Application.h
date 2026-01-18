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
			m_LayerStack.push_back(std::make_unique<TLayer>());
			m_LayerStack.back()->OnAttach();			
		}
		
		template<typename TLayer>
		requires(std::is_base_of_v<Layer, TLayer>)
		void PopLayer()
		{
			for (auto it = m_LayerStack.begin(); it != m_LayerStack.end(); ++it)
			{
				if (dynamic_cast<TLayer*>(it->get()))
				{
					(*it)->OnDetach();
					m_LayerStack.erase(it);
					return;
				}
			}
		}
		
		template<typename TLayer>
		requires(std::is_base_of_v<Layer, TLayer>)
		TLayer* GetLayer()
		{
			for (const auto& layer : m_LayerStack)
			{
				if (auto casted = dynamic_cast<TLayer*>(layer.get()))
					return casted;
			}
			return nullptr;
		}
		
		std::shared_ptr<Window> GetWindow() const { return m_Window; }
		glm::vec2 GetFrameSize() const;

		static Application& Get();
		static float GetTime();
	private:
		ApplicationSpecification m_Specification;
		std::shared_ptr<Window> m_Window;
		bool m_Running = false;

		std::vector<std::unique_ptr<Layer>> m_LayerStack;
	};

}