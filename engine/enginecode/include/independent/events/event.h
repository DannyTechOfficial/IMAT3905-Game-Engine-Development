/* \file event.h */
#pragma once

#include <intTypes.h>

namespace Engine
{
	/** \enum EventType
	* An enum for event types */

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/** \enum Event Category
	* Enum for type category flags
	*/

	enum EventCategory
	{
		None = 0,
		EventCategoryWindow = 1 << 0, //00000001
		EventCategoryInput = 1 << 1, //00000010
		EventCategoryKeyboard = 1 << 2, //00000100
		EventCategoryMouse = 1 << 3, //00001000
		EventCategoryMouseButton = 1 << 4, //00010000
	};

	/**
	* \class Event
	* Event base class
	*/

	class Event
	{
	public:
		virtual EventType getEventType() const = 0;
		virtual int32_t getCategoryFlags() const = 0; //!< Get the event type
		bool handled() const {
			return m_handled;
		};
		void handle(bool isHandled) { m_handled = isHandled; }
		inline bool isInCateogory(EventCategory category) const { return getCategoryFlags() & category; } //!< Is Event in cateory
	protected:
		bool m_handled = false;
	};
}
