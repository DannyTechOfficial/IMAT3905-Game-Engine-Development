/* \file GLFW_OpenGL_GC.h */
#pragma once



#include "core/graphicsContext.h"
#include <glfw/glfw3.h>

namespace Engine
{
	class GLFW_OpenGL_GC : public GraphicsContext
	{
		public:
			GLFW_OpenGL_GC(GLFWwindow* win) : m_window(win) {}  
			virtual void init() override;
			virtual void swapBuffers() override;
	private:
		GLFWwindow * m_window; //!< Pointer to window.
	};
}