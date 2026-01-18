#pragma once

#include <string>
#include <glm/glm.hpp>

#include "SFML/Graphics.hpp"

namespace Core {

	struct WindowSpecification
	{
		std::string Title;
		uint32_t Width = 1280;
		uint32_t Height = 720;
		bool UseFramerateLimit = false;
		int FramerateLimit = 120;
		bool IsResizeable = true;
		bool VSync = false;
	};

	class Window
	{
	public:
		Window(const WindowSpecification& specification = WindowSpecification());
		~Window();

		void Create();
		void Close();
		void Destroy();
		void Clear() const;

		void Display() const;

		glm::vec2 GetWindowSize() const ;

		bool ShouldClose() const;

		sf::RenderWindow* GetHandle() const { return m_Handle; }
	private:
		WindowSpecification m_Specification;

		sf::RenderWindow* m_Handle = nullptr;

	};

}
