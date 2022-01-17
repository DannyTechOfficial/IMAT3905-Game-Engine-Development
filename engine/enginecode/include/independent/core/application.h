/** \file application.h
*/
#pragma once

#include "systems/log.h"
#include "core/timer.h"
#include "events/events.h"
#include "events/eventHandler.h"
#include "core/window.h"
#include "independent/core/inputPoller.h"

namespace Engine {

	/**
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Provides ...
	*/

	class Application
	{
	protected:
		Application(); //!< Constructor
#		
		std::shared_ptr<Log> m_logSystem; //!< Log System
		std::shared_ptr<Timer> m_timer; //!< Timer
		std::shared_ptr<System> m_windowSystem; //!< Windows System

		std::shared_ptr<Window> m_window; //!< Window

		bool onClose(WindowCloseEvent& e); //!< Window Events
		bool onResize(WindowResizeEvent& e);
		bool onFocus(e_WindowFocus& e);
		bool onLostFocus(e_WindowLostFocus& e);
		bool onMoved(e_WindowMoved& e);
		
		bool onKeyPressed(e_KeyPressed& e);
		bool onKeyReleased(e_KeyReleased& e);

		bool onButtonPressed(e_MouseButtonPressed& e);
		bool onButtonReleased(e_MouseButtonReleased& e);
		bool onMouseMoved(e_MouseMoved& e);
		bool onMouseWheel(e_MouseScrolled& e);
	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Is the application running?
	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void run(); //!< Main loop
		
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}