#pragma once

#include <glm/glm.hpp>

namespace Engine 
{
	class InputPoller
	{
	public:
		static bool isKeyPressed(int32_t keyCode);
		static bool isMouseButtonPressed(int32_t mouseButton);
		static glm::vec2 getMousePos();
		static void setNative(void* window);
		inline static float getMX() { return getMousePos().x; }
		inline static float getMY() { return getMousePos().y; }
	};
}