/* \file OpenGLShader.h */
#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include "rendering/shader.h"

namespace Engine {
	class OpenGLShader : public Shader //!< Shader class to manage shader uploads etc.
	{
	public:
		OpenGLShader(const char* vertexFilepath, const char* fragmentFilepath);
		OpenGLShader(const char* filepath);
		~OpenGLShader();
		uint32_t getID() const override { return m_OpenGL_ID; }

		void uploadInt(const char* name, int value) override;
		void uploadFloat(const char* name, float value) override;
		void uploadFloat2(const char* name, const glm::vec2& value) override;
		void uploadFloat3(const char* name, const glm::vec3& value) override;
		void uploadFloat4(const char* name, const glm::vec4& value) override;
		void uploadMat4(const char* name, const glm::mat4& value) override;
	private:
		uint32_t m_OpenGL_ID;
		void compileAndLink(const char * vertexShaderSrc, const char * fragmentShaderSrc) override;
	};
}
