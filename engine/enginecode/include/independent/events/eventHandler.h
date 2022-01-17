/** \file eventHandler.h*/
#pragma once

#include "events.h"

#include <functional>

namespace Engine
{
	class EventHandler
	{
	public:
		void setOnCloseCallback(const std::function<bool(WindowCloseEvent&)>& fn) { m_onCloseCallback = fn; }
		void setOnResizeCallback(const std::function<bool(WindowResizeEvent&)>& fn) { m_onResizeCallback = fn; }
		void setOnFocusCallback(const std::function<bool(e_WindowFocus&)>& fn) { m_onFocusCallback = fn; }
		void setOnLostFocusCallback(const std::function<bool(e_WindowLostFocus&)>& fn) {m_onLostFocusCallback = fn; }
		void setOnWindowMovedCallback(const std::function<bool(e_WindowMoved&)>& fn) { m_onWindowMovedCallback = fn; }
		void setOnKeyPressedCallback(const std::function<bool(e_KeyPressed&)>& fn) { m_onKeyDownCallback = fn; }
		void setOnKeyReleasedCallback(const std::function<bool(e_KeyReleased&)>& fn) {m_onKeyUpCallback = fn; }
		void setOnKeyTypedCallback(const std::function<bool(e_KeyTyped&)>& fn) {m_onKeyTypedCallback = fn; }
		void setOnButtonPressedCallback(const std::function<bool(e_MouseButtonPressed&)>& fn) {m_onMouseDownCallback = fn; }
		void setOnButtonReleasedCallback(const std::function<bool(e_MouseButtonReleased&)>& fn) {m_onMouseUpCallback = fn; }
		void setOnMouseMovedCallback(const std::function<bool(e_MouseMoved&)>& fn) {m_onMouseMovedCallback = fn; }
		void setOnMouseWheelCallback(const std::function<bool(e_MouseScrolled&)>& fn) {m_onMouseWheelCallback = fn; }


		std::function<bool(WindowCloseEvent&)>& getOnCloseCallback() { return m_onCloseCallback; }
		std::function<bool(WindowResizeEvent&)>& getOnResizeCallback() { return m_onResizeCallback; }
		std::function<bool(e_WindowFocus&)>& getOnFocusCallback() { return m_onFocusCallback; }
		std::function<bool(e_WindowLostFocus&)>& getOnLostFocusCallback() { return m_onLostFocusCallback; }
		std::function<bool(e_WindowMoved&)>& getOnWindowMovedCallback() { return m_onWindowMovedCallback; }
		std::function<bool(e_KeyPressed&)>& getOnKeyDownCallback() { return m_onKeyDownCallback; }
		std::function<bool(e_KeyReleased&)>& getOnKeyUpCallback() { return m_onKeyUpCallback; }
		std::function<bool(e_KeyTyped&)>& getOnKeyTypedCallback() { return m_onKeyTypedCallback; }
		std::function<bool(e_MouseButtonPressed&)>& getOnMouseDownCallback() { return m_onMouseDownCallback; }
		std::function<bool(e_MouseButtonReleased&)>& getOnMouseUpCallback() { return m_onMouseUpCallback; }
		std::function<bool(e_MouseMoved&)>& getOnMouseMovedCallback() { return m_onMouseMovedCallback; }
		std::function<bool(e_MouseScrolled&)>& getOnMouseWheelCallback() { return m_onMouseWheelCallback; }

	private:
		std::function<bool(WindowCloseEvent&)> m_onCloseCallback = std::bind(&EventHandler::defaultOnClose, this, std::placeholders::_1);
		std::function<bool(WindowResizeEvent&)> m_onResizeCallback = std::bind(&EventHandler::defaultOnResize, this, std::placeholders::_1);;
		std::function<bool(e_WindowFocus&)> m_onFocusCallback = std::bind(&EventHandler::defaultOnFocus, this, std::placeholders::_1);;;
		std::function<bool(e_WindowLostFocus&)> m_onLostFocusCallback = std::bind(&EventHandler::defaultOnLostFocus, this, std::placeholders::_1);;;
		std::function<bool(e_WindowMoved&)> m_onWindowMovedCallback = std::bind(&EventHandler::defaultOnWindowMoved, this, std::placeholders::_1);;;
		std::function<bool(e_KeyPressed&)> m_onKeyDownCallback = std::bind(&EventHandler::defaultOnKeyPressed, this, std::placeholders::_1);;;
		std::function<bool(e_KeyReleased&)> m_onKeyUpCallback = std::bind(&EventHandler::defaultOnKeyReleased, this, std::placeholders::_1);;;
		std::function<bool(e_KeyTyped&)> m_onKeyTypedCallback = std::bind(&EventHandler::defaultOnKeyTyped, this, std::placeholders::_1);;;
		std::function<bool(e_MouseButtonPressed&)> m_onMouseDownCallback = std::bind(&EventHandler::defaultOnMouseButtonPressed, this, std::placeholders::_1);;;
		std::function<bool(e_MouseButtonReleased&)> m_onMouseUpCallback = std::bind(&EventHandler::defaultOnMouseButtonReleased, this, std::placeholders::_1);;;
		std::function<bool(e_MouseMoved&)> m_onMouseMovedCallback = std::bind(&EventHandler::defaultOnMouseMoved, this, std::placeholders::_1);;;
		std::function<bool(e_MouseScrolled&)> m_onMouseWheelCallback = std::bind(&EventHandler::defaultOnMouseScrolled, this, std::placeholders::_1);;;
		
		bool defaultOnClose(WindowCloseEvent& e) { return false; }
		bool defaultOnResize(WindowResizeEvent& e) { return false; }
		bool defaultOnFocus(e_WindowFocus& e) { return false; }
		bool defaultOnLostFocus(e_WindowLostFocus& e) { return false; }
		bool defaultOnWindowMoved(e_WindowMoved& e) { return false; }
		bool defaultOnKeyPressed(e_KeyPressed& e) { return false; }
		bool defaultOnKeyReleased(e_KeyReleased& e) { return false; }
		bool defaultOnKeyTyped(e_KeyTyped& e) { return false; }
		bool defaultOnMouseButtonPressed(e_MouseButtonPressed& e) { return false; }
		bool defaultOnMouseButtonReleased(e_MouseButtonReleased& e) { return false; }
		bool defaultOnMouseMoved(e_MouseMoved& e) { return false; }
		bool defaultOnMouseScrolled(e_MouseScrolled& e) { return false; }
	};
}