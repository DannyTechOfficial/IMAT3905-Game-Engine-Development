/* \file OpenGLVertexArray */
#pragma once

#include <vector>
#include <memory>
#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"
#include "rendering/vertexArray.h"

namespace Engine
{
	class OpenGLVertexArray : public VertexArray //!< VertexArray Class to contstruct an Open GL vertex array.
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		void addVertextBuffer (const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
		inline uint32_t getID()  const override { return m_OpenGL_ID; }
		inline uint32_t getDrawCount() const override {
			if (m_indexBuffer) { return m_indexBuffer->getCount(); } else { return 0; }
		};
		inline uint32_t getIBOID()const override {
			if (m_indexBuffer) { return m_indexBuffer->getID(); }
			else { return -1; }
		};
	private:
		uint32_t m_OpenGL_ID;
		uint32_t m_attributeIndex = 0;

	};
}