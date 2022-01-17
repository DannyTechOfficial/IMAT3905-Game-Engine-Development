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