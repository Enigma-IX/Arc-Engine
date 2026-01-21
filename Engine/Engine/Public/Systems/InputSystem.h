#pragma once
#include "SFML/Window/Event.hpp"

namespace Engine
{
    class InputSystem
    {
    public:
        InputSystem() {};
        ~InputSystem() = default;
        
        void ProcessEvent(const sf::Event& event);
        
    private:
        //PlayerController* m_activePlayerController;
    
    };
}


