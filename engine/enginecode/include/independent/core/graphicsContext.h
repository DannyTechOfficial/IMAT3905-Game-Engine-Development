/* \file graphicsContext.h */
#pragma once

namespace
{
	class GraphicsContext
	{
	public:
		virtual void init() = 0; //!<Initiates Graphics context for window.
		virtual void swapBuffers() = 0; //!< Swaps front and back buffers (double buffer)
	};
}