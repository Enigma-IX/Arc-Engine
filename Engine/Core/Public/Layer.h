#pragma once

#include "SFML/Window/Event.hpp"

namespace Core {

	class Layer
	{
	public:
		virtual ~Layer() = default;
		
		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnEvent(sf::Event& event) {}

		virtual void OnUpdate(float dt) {}
		virtual void OnRender() {}
	};

}
