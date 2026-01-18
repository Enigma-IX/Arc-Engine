#include "Window.h"

#include <glm/glm.hpp>

#include <iostream>
#include <cassert>

namespace Core {

	Window::Window(const WindowSpecification& specification)
		: m_Specification(specification)
	{
	}

	Window::~Window()
	{
		Destroy();
	}

	void Window::Create()
	{
		m_Handle = new sf::RenderWindow(
			sf::VideoMode({m_Specification.Width, m_Specification.Height}),
			m_Specification.Title.c_str());

		if (!m_Handle)
		{
			std::cerr << "Failed to create window!\n";
			assert(false);
		}

		m_Handle->setVerticalSyncEnabled(m_Specification.VSync);
		m_Handle->setFramerateLimit(m_Specification.UseFramerateLimit ? m_Specification.FramerateLimit : 0);
	}

	void Window::Close()
	{
		if (m_Handle)
			m_Handle->close();
	}

	void Window::Destroy()
	{
		if (m_Handle)
		{
			m_Handle->close();
			delete m_Handle;
			m_Handle = nullptr;
		}
	}

	void Window::Clear() const
	{
		m_Handle->clear();
	}
	
	void Window::Display() const
	{
		m_Handle->display();
	}

	glm::vec2 Window::GetWindowSize() const 
	{
		sf::Vector2u size = m_Handle->getSize();
		int width = size.x;
		int height = size.y;
		return { width, height };
	}

	bool Window::ShouldClose() const
	{
		return !m_Handle || !m_Handle->isOpen();
	}

}