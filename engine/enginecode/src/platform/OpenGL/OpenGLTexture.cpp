/* \file OpenGLTexture.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "platform/OpenGL/OpenGLTexture.h"
#include "rendering/texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


namespace Engine
{
	OpenGLTexture::OpenGLTexture(const char * filepath) //!< Constructors for an OpenGL Texture
	{
		int width, height, channels;
		unsigned char *data = stbi_load(filepath, &width, &height, &channels, 0);

		if (data) init(width, height, channels, data);

		//stbi_image_free(data);

	}

	OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data)
	{

		if (data) init(width, height, channels, data);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_OpenGL_ID);
	}

	void OpenGLTexture::edit(int32_t xOffset, int32_t yOffset, uint32_t width, uint32_t height, unsigned char * data) //!< Enables modifying texture
	{
		glBindTexture(GL_TEXTURE_2D, m_OpenGL_ID);
		if (data)
		{
			if (m_channels == 3) glTextureSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
			else if (m_channels == 4) glTextureSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
	}

	void OpenGLTexture::bindToUnit(uint32_t unit) //!< Binds unit to rendering
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, m_OpenGL_ID);
	}

	void OpenGLTexture::init(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data) //!< Initialises Open GL Textures to GPU
	{
		glGenTextures(1, &m_OpenGL_ID);
		glBindTexture(GL_TEXTURE_2D, m_OpenGL_ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (channels == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else if (channels == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else return;
		glGenerateMipmap(GL_TEXTURE_2D);

		//stbi_image_free(data);
		m_width = width;
		m_height = height;
		m_channels = channels;
	}

}