/* \file mouseEvents.h*/
#pragma once

#include "event.h"
#include <glm/glm.hpp>

namespace Engine {

	class e_Mouse : public Event
	{
		virtual inline int32_t getCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
	};

	class e_MouseMoved : public e_Mouse
	{
	public:
		e_MouseMoved(float x, float y) : m_mouseX(x), m_mouseY(y) {}

		static EventType getStaticType() { return EventType::MouseMoved;  }
		virtual inline EventType getEventType() const override { return getStaticType(); }
		inline float getX() const { return m_mouseX;  }
		inline float getY() const { return m_mouseY;  }
		inline glm::vec2 getPos() const { return glm::vec2(m_mouseX, m_mouseY); }

	private:
		float m_mouseX, m_mouseY;
	};

	class e_MouseScrolled : public e_Mouse
	{

	public:
		e_MouseScrolled(float xOffset, float yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {}

		static EventType getStaticType() { return EventType::MouseScrolled;  }
		virtual EventType getEventType() const override { return getStaticType(); }
		inline float getXOffset() const { return m_xOffset;  }
		inline float getYOffset() const { return m_yOffset;  }

	private:
		float m_xOffset, m_yOffset;
	};

	class e_MouseButtonPressed : public e_Mouse
	{
	public:
		e_MouseButtonPressed(int32_t button) : m_button(button) {  }

		static EventType getStaticType() { return EventType::MouseButtonPressed;  }
		virtual EventType getEventType() const override { return getStaticType();  }
		inline int32_t getButton() const { return m_button;  }

	private:
		int32_t m_button;
	};

	class e_MouseButtonReleased : public e_Mouse
	{
	public:
		e_MouseButtonReleased(int32_t button) : m_button(button) {}

		static EventType getStaticType() { return EventType::MouseButtonReleased; }
		virtual EventType getEventType() const override { return getStaticType(); }
		inline int32_t getButton() const { return m_button;  }
	private:
		int32_t m_button;
	};
}