#include "engine_pch.h"
#include "platform/GLFW/GLFWInputPoller.h"
#include "platform/GLFW/GLFWCodes.h"
#include <GLFW/glfw3.h>

namespace Engine {

	GLFWwindow* GLFWInputPoller::s_window = nullptr;

	bool GLFWInputPoller::isKeyPressed(int32_t keyCode)
	{
		//return glfwGetKey(s_window, keyCode);
		//return(&s_window);
		if (s_window)
		{
			auto state = glfwGetKey(s_window, keyCode);
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		}
		else return false;
	}

	bool GLFWInputPoller::isMouseButtonPressed(int32_t mouseButton)
	{
		if (s_window)
		{
			auto state = glfwGetMouseButton(s_window, mouseButton);
			return state == GLFW_PRESS;
		}
		return false;
	}

	glm::vec2 GLFWInputPoller::getMousePosition()
	{
		double x, y;
		if (s_window)
		{
			glfwGetCursorPos(s_window, &x, &y);
			return glm::vec2(x, y);
		}
		else return glm::vec2(-1, -1);
	}
}
