/** \file GLFWWindoooooowImpl.h */
#pragma once

#include "core/window.h"
#include <GLFW/glfw3.h>

namespace Engine
{
	/** \Class GLFWWindowImpl
	* Implementation of a window with GLFW
	*/

	class GLFWWindowImpl : public Window
	{
	public:

		GLFWWindowImpl(const WindowProperties& properties); //!< Window Constructor
		virtual void init(const WindowProperties& properties) override; //!< initialise the window
		virtual void close() override; //!< Close the window
		//virtual ~Window() {}; //!< Deinitialize Window
		virtual void onUpdate(float timestep) override; //!< Update contstructor
		virtual void setVSync(bool VSync) override; //!< VSync retrievel constructor
		virtual inline unsigned int getWidth() const override { return m_props.width; } //!< Width retrievel constructor
		virtual inline unsigned int getHeight() const override { return m_props.height;  } //!< Height retrievel constructor
		virtual inline void* getNativeWindow() const override { return m_native; } //!< Window retrievel constructor
		virtual inline bool isFullScreenMode() const override { return m_props.isFullScreen;  } //!< Window full screen retrievel constructor
		virtual inline bool isVSync() const override { return m_props.isVSync;  } //!< Window VSync retrievel constructor.


	private:
		WindowProperties m_props; //<! List Properties
		GLFWwindow * m_native; //!< Native GLFW window
		float m_aspectRation; //!< Aspect ratio
	};
}