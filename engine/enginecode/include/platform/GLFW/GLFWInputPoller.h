/* \ file GLFWInputPoller.h */
#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Engine 
{
	/* \Class GLFWInputPoller
		Input poller using GLFW.
	*/

	class GLFWInputPoller
	{
	public:
		static bool isKeyPressed(int32_t keyCode); //!< Is Key Pressed
		static bool isMouseButtonPressed(int32_t mouseButton); //!< is Mouse Button Pressed
		static glm::vec2 getMousePosition(); //!< Gets the mouses current position
		static void setCurrentWindow(GLFWwindow* newWin) { s_window = newWin; } //!< Retrieves current window

	private:
		static GLFWwindow* s_window;

	};


}