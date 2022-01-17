/* \file OpenGLTexture.h */

#pragma once

#include <cstdint>
#include "rendering/texture.h"

namespace Engine
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const char * filepath);
		OpenGLTexture(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data);
		~OpenGLTexture();
		void edit(int32_t xOffset, int32_t yOffset, uint32_t width, uint32_t height, unsigned char * data) override;
		inline uint32_t getID() override { return m_OpenGL_ID; }
		inline uint32_t getWidth() override { return m_width; }
		inline uint32_t getHeight() override { return m_height; }
		inline uint32_t getWidthf() override { return static_cast<float>(m_width); }
		inline uint32_t getHeightf() override { return static_cast<float>(m_height); }
		inline uint32_t getChannels() override { return m_channels; }
		void bindToUnit(uint32_t unit) override;
	private:
		uint32_t m_OpenGL_ID;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_channels;
		void init(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data);
	};
}
