## Welcome to Game Engine

Here at Danny Tech, I am looking to branch out with my Computer knowledge to share and use within my career.

Today I have a demonstration of my initial Game Engine that I developed for my first semester at University. The engine available to you is built are OpenGL but has been made to be easy to add other renderers like DirectX / Vulcan if I so wished.
The Engine was built using C++, with the functionality to render 2D & 3D into the scene made.

This was a very basic Engine I was tasked to make but with it came a lot of programming skills and styles that I have learned to adapt into my work.
i.e. Agnostic Code, Documentation, Encapsulation.

### V 1

Version 1 was designed on building the foundations of the engine so that it could be built upon to make more features as well as improve existing ones.
My personal favourite code from this assignment was the Renderer with its API, 2D & 3D functionality.
```markdown
#RenderAPI

/* \file renderAPI.cpp */

#include "engine_pch.h"

#include "rendering/RenderAPI.h"
#include "rendering/indexBuffer.h"
#include "rendering/vertexBuffer.h"
#include "rendering/vertexArray.h"
#include "rendering/texture.h"
#include "rendering/shader.h"

#include "platform/OpenGL/OpenGLIndexBuffer.h"
#include "platform/OpenGL/OpenGLVertexBuffer.h"
#include "platform/OpenGL/OpenGLVertexArray.h"
#include "platform/OpenGL/OpenGLTexture.h"
#include "platform/OpenGL/OpenGLShader.h"

#include "systems/log.h"

namespace Engine //!< Agnostic templates of original code. When run it directs the code to the necessary renderer i.e. Open GL / Direct X
{
	RenderAPI::API Engine::RenderAPI::s_API = RenderAPI::API::OpenGL;

	IndexBuffer * IndexBuffer::create(uint32_t * indices, uint32_t count)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No supported Rendering API");

		case RenderAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);

		case RenderAPI::API::Direct3D:
			Log::error("Direct3D not currently Supported!");

		case RenderAPI::API::Vulkan:
			Log::error("Vulkan not currently Supported!");


		}
		
	}

	VertexBuffer * VertexBuffer::create(void * vertices, uint32_t size, BufferLayout layout)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No Supported Rendering API");

		case RenderAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size, layout);

		case RenderAPI::API::Direct3D:
			Log::error("Direct3D not currently Supported!");

		case RenderAPI::API::Vulkan:
			Log::error("Vulkan not currently Supported!");
		}
	}

	VertexArray * VertexArray::create()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No Supported Rendering API");

		case RenderAPI::API::OpenGL:
			return new OpenGLVertexArray();

		case RenderAPI::API::Direct3D:
			Log::error("Direct3D not currently Supported!");

		case RenderAPI::API::Vulkan:
			Log::error("Vulkan not currently Supported!");
		}
	}

	Texture * Texture::create(const char * filepath)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No Supported Rendering API");

		case RenderAPI::API::OpenGL:
			return new OpenGLTexture(filepath);

		case RenderAPI::API::Direct3D:
			Log::error("Direct3D not currently Supported!");

		case RenderAPI::API::Vulkan:
			Log::error("Vulkan not currently Supported!");
		}
	}

	Texture * Texture::create(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No Supported Rendering API");

		case RenderAPI::API::OpenGL:
			return new OpenGLTexture(width, height, channels, data);

		case RenderAPI::API::Direct3D:
			Log::error("Direct3D not currently Supported!");

		case RenderAPI::API::Vulkan:
			Log::error("Vulkan not currently Supported!");
		}
	}

	Shader * Shader::create(const char * vertexFilepath, const char * fragmentFilepath)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No Supported Rendering API");

		case RenderAPI::API::OpenGL:
			return new OpenGLShader(vertexFilepath, fragmentFilepath);

		case RenderAPI::API::Direct3D:
			Log::error("Direct3D not currently Supported!");

		case RenderAPI::API::Vulkan:
			Log::error("Vulkan not currently Supported!");
		}
	}

	Shader * Shader::create(const char * filepath) 
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None:
			Log::error("No Supported Rendering API");

		case RenderAPI::API::OpenGL:
			return new OpenGLShader(filepath);

		case RenderAPI::API::Direct3D:
			Log::error("Direct3D not currently Supported!");

		case RenderAPI::API::Vulkan:
			Log::error("Vulkan not currently Supported!");
		}
	}


}

```

```markdown
#Render2D

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

```

```markdown
#Render3D

/** \file renderer3D.cpp */

#include "engine_pch.h"
#include "rendering/Renderer3D.h"
#include "glad/glad.h"

namespace Engine
{
	std::shared_ptr<Renderer3D::InternalData> Renderer3D::s_data = nullptr;

	void Renderer3D::init() //!< Initializes the renderer
	{
		s_data.reset(new InternalData);

		unsigned char whitePx[4] = { 255, 255, 255, 255 };
		s_data->defaultTexture.reset(Texture::create(1, 1, 4, whitePx));

		s_data->defaultTint = { 1.f, 1.f, 1.f, 1.f };

	}

	void Renderer3D::begin(const SceneWideUniforms & sceneWideUniforms) //!< sets the scene wide uniforms.
	{
		s_data->sceneWideUniforms = sceneWideUniforms;
	}

	void Renderer3D::submit(const std::shared_ptr<VertexArray>& geometry, const std::shared_ptr<Material>& material, const glm::mat4 & model) //!< for each scenewideuniform uploads content to shader.
	{
		//Bind Shader
		glUseProgram(material->getShader()->getID());
		//Apply sceneWideUniforms
		for (auto& dataPair : s_data->sceneWideUniforms)
		{
			const char * nameofUniform = dataPair.first;
			ShaderDataType& sdt = dataPair.second.first;
			void * addressOfValue = dataPair.second.second;

			switch (sdt)
			{
			case ShaderDataType::Int:
				material->getShader()->uploadInt(nameofUniform, *(int *)addressOfValue);
				break;
			case ShaderDataType::Float3:
				material->getShader()->uploadFloat3(nameofUniform, *(glm::vec3 *)addressOfValue);
				break;
			case ShaderDataType::Float4:
				material->getShader()->uploadFloat4(nameofUniform, *(glm::vec4 *)addressOfValue);
				break;
			case ShaderDataType::Mat4:
				material->getShader()->uploadMat4(nameofUniform, *(glm::mat4 *)addressOfValue);
				break;

			}
		}

		//Apply material uniforms (per draw uniforms)
		material->getShader()->uploadMat4("u_model", model);

		if (material->isFlagSet(Material::flag_texture)) glBindTexture(GL_TEXTURE_2D, material->getTexture()->getID());
		else glBindTexture(GL_TEXTURE_2D, s_data->defaultTexture->getID());
		material->getShader()->uploadInt("u_texData", 0);

		if (material->isFlagSet(Material::flag_tint)) material->getShader()->uploadFloat4("u_tint", material->getTint());
		else material->getShader()->uploadFloat4("u_tint", s_data->defaultTint);

		//Bind the geometry (VAO and IBO)
		glBindVertexArray(geometry->getID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->getIBOID()); //getIndexBuffer needs to be implemented into vertex Array
		//Submit the Draw#
		glDrawElements(GL_TRIANGLES, geometry->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer3D::end() //!< Clears the scenewideuniforms variable ready for next render.
	{
		s_data->sceneWideUniforms.clear();
	}

}

```

## Check it Out

If you want to see more of the Engine, please follow the link at the top of the page to look over the code on GitHub.
