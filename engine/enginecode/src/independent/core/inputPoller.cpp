#include "engine_pch.h"
#include "independent/core/inputPoller.h"
#include "platform/GLFW/GLFWInputPoller.h"

namespace Engine //!< Used to track / check key / mouse inputs
{
	bool InputPoller::isKeyPressed(int32_t keyCode)
	{
		return GLFWInputPoller::isKeyPressed(keyCode);
	}

	bool InputPoller::isMouseButtonPressed(int32_t mouseButton)
	{
		return GLFWInputPoller::isMouseButtonPressed(mouseButton);
	}

	glm::vec2 InputPoller::getMousePos()
	{
		return GLFWInputPoller::getMousePosition();
	}

	void InputPoller::setNative(void * window)
	{
		GLFWInputPoller::setCurrentWindow(reinterpret_cast<GLFWwindow*>(window));
	}
}

