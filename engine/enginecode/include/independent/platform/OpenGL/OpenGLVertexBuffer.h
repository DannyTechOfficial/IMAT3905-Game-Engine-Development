/* \OpenGLVertexBuffer.h */
#pragma once

#include "rendering/bufferLayout.h"
#include "rendering/vertexBuffer.h"

namespace Engine 
{
	class OpenGLVertexBuffer : public VertexBuffer //!< Open GL VertexBuffer class
	{
	public:
		OpenGLVertexBuffer(void* vertices, uint32_t size, BufferLayout layout);
		~OpenGLVertexBuffer();
		void edit(void* vertices, uint32_t size, int32_t offset) override;
		inline uint32_t getRenderID() const override { return m_OpenGL_ID; }
		inline const BufferLayout& getLayout() const override { return m_layout; }

	private:
		uint32_t m_OpenGL_ID; //!< OpenGL ID
		BufferLayout m_layout;
	};
}