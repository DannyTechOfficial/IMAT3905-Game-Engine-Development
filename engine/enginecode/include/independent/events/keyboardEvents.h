/* \file keyboardEvents.h */
#pragma once

#include "event.h"

namespace Engine {
	/**
\class e_Key
Keyboard Event Class for different possible events.
*/


	class e_Key : public Event 
	{
	protected:
		e_Key(int32_t keycode) : m_keyCode(keycode) {}
		int32_t m_keyCode;

	public:
		inline int32_t getKeyCode() const { return m_keyCode;  }
		virtual inline int32_t getCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

	};

	class e_KeyPressed : public e_Key
	{
	private:
		int32_t m_repeatCount;
	public:
		e_KeyPressed(int32_t keycode, int32_t repeatCount) : e_Key(keycode), m_repeatCount(repeatCount) {}

		inline int32_t getRepeatCount() const { return m_repeatCount;  }
		static EventType getStaticType() { return EventType::KeyPressed;  }
		virtual inline EventType getEventType() const override { return getStaticType(); }
	};

	class e_KeyReleased : public e_Key
	{
	public:
		e_KeyReleased(int32_t keycode) : e_Key(keycode) {}
		static EventType getStaticType() { return EventType::KeyReleased;  }
		virtual inline EventType getEventType() const override { return getStaticType(); }

	};

	class e_KeyTyped : public e_Key
	{
	public:
		e_KeyTyped(int32_t keycode) : e_Key(keycode) {}
		static EventType getStaticType() { return EventType::KeyTyped;  }
		virtual inline EventType getEventType() const override { return getStaticType(); }
	};
}