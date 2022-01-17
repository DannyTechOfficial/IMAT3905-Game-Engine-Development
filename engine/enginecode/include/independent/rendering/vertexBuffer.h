/* \file vertexBuffer.h */
#pragma once

#include "bufferLayout.h"
#include <cstdint>

namespace Engine
{
	class VertexBuffer //!< Vertex Buffer Agnostic class
	{
	public:
		virtual ~VertexBuffer() = default;

		static VertexBuffer* create(void * vertices, uint32_t size, BufferLayout layout);

		virtual inline uint32_t getRenderID() const = 0;
		virtual const BufferLayout& getLayout() const = 0;
		
		virtual void edit(void* vertices, uint32_t size, int32_t offset) = 0;
	private:

	};
}