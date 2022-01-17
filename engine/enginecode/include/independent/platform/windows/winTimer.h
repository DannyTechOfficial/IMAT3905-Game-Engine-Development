/** \file windTimer */
#pragma once

#include <Windows.h>
#include "core/timer.h"

namespace Engine
{
	/** \class WinTimer
	* Windows based timer which uses PerformanceCount
	*/

	class WinTimer : public Timer
	{
	public:
		virtual void start() override 
		{
			QueryPerformanceFrequency(&m_frequency);
			QueryPerformanceCounter(&m_startTime);
		};

		virtual void reset() override 
		{
			QueryPerformanceCounter(&m_startTime);
		};

		virtual float getElapsedTime() override 
		{
			QueryPerformanceCounter(&m_endTime);
			float result = (m_endTime.QuadPart - m_startTime.QuadPart) * 1000.0 / m_frequency.QuadPart;
			result /= 1000.f;
			return result;
		};

	private:
		LARGE_INTEGER m_startTime; //!< Start time for the timer
		LARGE_INTEGER m_endTime; //!< End time for the timer
		LARGE_INTEGER m_frequency; //!< Ticks per second of the cpu
	};
}