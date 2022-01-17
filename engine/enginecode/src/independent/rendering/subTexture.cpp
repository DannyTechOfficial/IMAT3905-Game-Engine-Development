/* \file subTexture.cpp */

#include "engine_pch.h"
#include "rendering/subTexture.h"

namespace Engine
{
	SubTexture::SubTexture(const std::shared_ptr<Texture>& texture, const glm::vec2 & UVStart, const glm::vec2 & UVEnd) : //!< Simple version of Texture
		m_texture(texture),
		m_UVStart(UVStart),
		m_UVEnd(UVEnd)
	{
		m_size.x = static_cast<int>((m_UVEnd.x - m_UVStart.x) * m_texture->getWidthf());
		m_size.y = static_cast<int>((m_UVEnd.y - m_UVStart.y) * m_texture->getHeightf());
	}

	float SubTexture::transformU(float U)
	{
		return m_UVStart.x + ((m_UVEnd.x - m_UVStart.x) * U);
	}

	float SubTexture::transformV(float V)
	{
		return m_UVStart.y + ((m_UVEnd.y - m_UVStart.y) * V);
	}

	glm::vec2 SubTexture::tramsformUV(glm::vec2 UV)
	{
		return m_UVStart + ((m_UVEnd - m_UVStart) * UV);
	}

	SubTexture::SubTexture()
	{

	}

}