/* \file renderer2D.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "rendering/Renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	std::shared_ptr <Renderer2D::InternalData> Renderer2D::s_data = nullptr;


	void Renderer2D::init() //!< Initializes 2D Rendering ready for data
	{

		s_data.reset(new InternalData);
		
		unsigned char whitePx[4] = { 255, 255, 255, 255 };
		s_data->defaultTexture.reset(Texture::create(1, 1, 4, whitePx));

		s_data->defaultTint = { 1.f, 1.f, 1.f, 1.f };

		s_data->model = glm::mat4(1.f);

		s_data->shader.reset(Shader::create("./assets/shaders/quad1.glsl"));

		float vertices[4 * 4] = {
			-0.5f, -0.5f, 0.f, 0.f,
			-0.5f, 0.5f, 0.f, 1.f,
			0.5f, 0.5f, 1.f, 1.f,
			0.5f, -0.5f, 1.f, 0.f
		};

		uint32_t indices[4] = { 0, 1, 2, 3 };

		std::shared_ptr<VertexBuffer> VBO;
		std::shared_ptr<IndexBuffer> IBO;

		s_data->VAO.reset(VertexArray::create()); //!< Creating necessary buffers and index for 2D Render.
		VBO.reset(VertexBuffer::create(vertices, sizeof(vertices), BufferLayout({ ShaderDataType::Float2, ShaderDataType::Float2 })));
		IBO.reset(IndexBuffer::create(indices, 4));
		s_data->VAO->addVertextBuffer(VBO);
		s_data->VAO->setIndexBuffer(IBO);

		glBindVertexArray(s_data->VAO->getID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIBOID());

	}

	void Renderer2D::begin(const SceneWideUniforms& swu) //!< Stores all the SWU ready for uploading
	{
		// Bind the shader
		glUseProgram(s_data->shader->getID());

		//Apply sceneWideUniforms
		for (auto& dataPair : swu)
		{
			const char * nameofUniform = dataPair.first;
			ShaderDataType sdt = dataPair.second.first;
			void* addressOfValue = dataPair.second.second;

			switch (sdt)
			{
			case ShaderDataType::Int:
				s_data->shader->uploadInt(nameofUniform, *(int *)addressOfValue);
				break;
			case ShaderDataType::Float3:
				s_data->shader->uploadFloat3(nameofUniform, *(glm::vec3 *)addressOfValue);
				break;
			case ShaderDataType::Float4:
				s_data->shader->uploadFloat4(nameofUniform, *(glm::vec4 *)addressOfValue);
				break;
			case ShaderDataType::Mat4:
				s_data->shader->uploadMat4(nameofUniform, *(glm::mat4 *)addressOfValue);
				break;

			}
		}
		// Bind the geometry
		glBindVertexArray(s_data->VAO->getID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIBOID()); //getIndexBuffer needs to be implemented into vertex Array
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4 & tint) //!< Submits render to shader with quad and tint
	{
		Renderer2D::submit(quad, tint, s_data->defaultTexture);
		/*
		glBindTexture(GL_TEXTURE_2D, s_data->defaultTexture->getID());
		s_data->model = glm::scale(glm::translate(glm::mat4(1.f), quad.m_translate), quad.m_scale);
		
		s_data->shader->uploadInt("u_textData", 0);
		s_data->shader->uploadFloat4("u_tint", tint);
		s_data->shader->uploadMat4("u_model", s_data->model);

		glBindVertexArray(s_data->VAO->getID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIBOID());

		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
		*/
	}

	void Renderer2D::submit(const Quad & quad, const std::shared_ptr<Texture>& texture)  //!< Submits render to shader with quad and texture
	{
		Renderer2D::submit(quad, s_data->defaultTint, texture);
		/*
		glBindTexture(GL_TEXTURE_2D, texture->getID());
		s_data->model = glm::scale(glm::translate(glm::mat4(1.f), quad.m_translate), quad.m_scale);

		s_data->shader->uploadInt("u_textData", 0);
		s_data->shader->uploadFloat4("u_tint", s_data->defaultTint);
		s_data->shader->uploadMat4("u_model", s_data->model);

		glBindVertexArray(s_data->VAO->getID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIBOID());

		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
		*/
	}

	void Renderer2D::submit(const Quad & quad, const glm::vec4 & tint, const std::shared_ptr<Texture>& texture)  //!< Submits render to shader with quad, tint and texture.
	{
		glBindTexture(GL_TEXTURE_2D, texture->getID());
		s_data->model = glm::scale(glm::translate(glm::mat4(1.f), quad.m_translate), quad.m_scale);

		s_data->shader->uploadInt("u_textData", 0);
		s_data->shader->uploadFloat4("u_tint", tint);
		s_data->shader->uploadMat4("u_model", s_data->model);

		glBindVertexArray(s_data->VAO->getID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIBOID());

		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer2D::submit(const Quad & quad, const std::shared_ptr<Texture>& texture, float angle, bool degrees)  //!< Submits render to shader with quad, texture, angle
	{
		Renderer2D::submit(quad, s_data->defaultTint, texture, angle, degrees);
	}

	void Renderer2D::submit(const Quad & quad, const glm::vec4 & tint, float angle, bool degrees) //!< Submits render to shader with quad, tint, angle
	{
		Renderer2D::submit(quad, tint, s_data->defaultTexture, angle, degrees);
	}

	void Renderer2D::submit(const Quad & quad, const glm::vec4 & tint, const std::shared_ptr<Texture>& texture, float angle, bool degrees) //!< Submits render to shader with quad, tint, texture and angle
	{
		if (degrees) angle = glm::radians(angle);

		glBindTexture(GL_TEXTURE_2D, texture->getID());
		s_data->model = glm::scale(glm::rotate(glm::translate(glm::mat4(1.f), quad.m_translate), angle, {0.f, 0.f, 1.f}), quad.m_scale);

		s_data->shader->uploadInt("u_textData", 0);
		s_data->shader->uploadFloat4("u_tint", tint);
		s_data->shader->uploadMat4("u_model", s_data->model);

		glBindVertexArray(s_data->VAO->getID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIBOID());

		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer2D::end()
	{
	}

	Quad Quad::createCentreHalfExtents(const glm::vec2 & centre, const glm::vec2 & halfExtents)  //!< Creates quad for 2D
	{
		Quad result;

		result.m_translate = glm::vec3(centre, 0.f);
		result.m_scale = glm::vec3(halfExtents * 2.f, 1.f);

		return result;
	}

}