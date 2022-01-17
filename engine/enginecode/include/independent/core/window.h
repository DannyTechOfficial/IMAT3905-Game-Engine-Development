/* \file window.h */
#pragma once

#include "events/eventHandler.h"
#include "core/graphicsContext.h"

namespace Engine
{
	/** \class Window
	* Abstract windows base class. All implemented windows should code to this interface.
	*/

	struct WindowProperties
	{
		char * title;
		uint32_t width;
		uint32_t height;
		bool isFullScreen;
		bool isVSync;

		WindowProperties(char * title = "My Window", uint32_t width = 800, uint32_t height = 600, bool fullscreen = false) : title(title), width(width), height(height), isFullScreen(fullscreen) {}

	};

	class Window
	{
	public:
		virtual void init(const WindowProperties& properties) = 0; //!< initialise the window
		virtual void close() = 0; //!< Close the window
		virtual ~Window() {}; //!< Deinitialize Window
		virtual void onUpdate(float timestep) = 0; //!< Update contstructor
		virtual void setVSync(bool VSync) = 0; //!< VSync retrievel constructor
		virtual unsigned int getWidth() const = 0; //!< Width retrievel constructor
		virtual unsigned int getHeight() const = 0; //!< Height retrievel constructor
		virtual void* getNativeWindow() const = 0; //!< Window retrievel constructor
		virtual bool isFullScreenMode() const = 0; //!< Window full screen retrievel constructor
		virtual bool isVSync() const = 0; //!< Window VSync retrievel constructor.

		inline EventHandler& getEventHandler() { return m_handler; }

		static Window* create(const WindowProperties& properties = WindowProperties());
	protected:
		EventHandler m_handler; //!< Event Handler
		std::shared_ptr<GraphicsContext> m_graphicsContext;
	};
}