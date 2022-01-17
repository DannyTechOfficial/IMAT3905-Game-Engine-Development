/* \file subTexture.h */

#pragma once

#include <rendering/texture.h>
#include <memory>
#include <glm/glm.hpp>

namespace Engine
{
	class SubTexture
	{
	public:
		SubTexture();
		SubTexture(const std::shared_ptr<Texture>& texture, const glm::vec2& UVStart, const glm::vec2& UVEnd);
		inline glm::vec2 getUVStart() { return m_UVStart; }
		inline glm::vec2 getUVEnd() { return m_UVEnd; }
		glm::ivec2 getSize() { return m_size; }
		glm::vec2 getSizeF() { return { static_cast<float>(m_size.x), static_cast<float>(m_size.y) }; }
		inline uint32_t getWidth() { return m_size.x; }
		inline uint32_t getHeight() { return m_size.y; }
		inline uint32_t getWidthf() { return static_cast<float>(m_size.x); }
		inline uint32_t getHeightf() { return static_cast<float>(m_size.y); }
		float transformU(float U); //!< Transform original to atlased co-ords
		float transformV(float V);
		glm::vec2 tramsformUV(glm::vec2 UV);
	private:
		std::shared_ptr<Texture> m_texture;
		glm::vec2 m_UVStart;
		glm::vec2 m_UVEnd;
		glm::ivec2 m_size;
	};
}