/* \file Shader.h */
#pragma once

#include <cstdint>
#include <glm/glm.hpp>

namespace Engine
{
	class Shader //!< Shader Agnostic class
	{
	public:
		virtual ~Shader() = default;

		static Shader* create(const char* vertexFilepath, const char* fragmentFilepath); //!< Two Shader Contstructors depending on requirements
		static Shader* create(const char* filepath);

		virtual inline uint32_t getID() const = 0;

		virtual void uploadInt(const char* name, int value) = 0;
		virtual void uploadFloat(const char* name, float value) = 0;
		virtual void uploadFloat2(const char* name, const glm::vec2& value) = 0;
		virtual void uploadFloat3(const char* name, const glm::vec3& value) = 0;
		virtual void uploadFloat4(const char* name, const glm::vec4& value) = 0;
		virtual void uploadMat4(const char* name, const glm::mat4& value) = 0;
	private:
		//virtual inline uint32_t m_OpenGL_ID;
		virtual void compileAndLink(const char * vertexShaderSrc, const char * fragmentShaderSrc) = 0;
	};
}