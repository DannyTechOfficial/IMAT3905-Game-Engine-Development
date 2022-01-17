/* \file Renderer3D.h */
#pragma once

#include "rendering/RenderAPI.h"
#include "rendering/RendererCommon.h"

namespace Engine
{
	
	/** \class Material
	* \brief Holds shaders and the uniform data associated with that shader
	*/
	class Material
	{
	public:
		Material(const std::shared_ptr<Shader>& shader) : //!< Material constructor for shader
			m_shader(shader), m_flags(0), m_texture(nullptr), m_tint(glm::vec4(0.f)) 
		{}
		
		Material(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, const glm::vec4& tint) ://!< Material constructor for shader, texture & tint
			m_shader(shader), m_texture(texture), m_tint(tint)
		{
			setFlag(flag_texture | flag_tint);
		}
		
		Material(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture) : //!< Material constructor for shader and texture
			m_shader(shader), m_texture(texture), m_tint(glm::vec4(0.f))
		{
			setFlag(flag_texture);
		}

		Material(const std::shared_ptr<Shader>& shader, const glm::vec4& tint) : //!< Material constructor for shader and tint
			m_shader(shader), m_texture(nullptr), m_tint(tint)
		{
			setFlag(flag_tint);
		}

		inline std::shared_ptr<Shader> getShader() const { return m_shader; }
		inline std::shared_ptr<Texture> getTexture() const { return m_texture; }
		inline glm::vec4 getTint() const { return m_tint; }
		bool isFlagSet(uint32_t flag) const { return m_flags & flag; }

		void setTexture(const std::shared_ptr<Texture>& texture) { m_texture = texture; }
		void setTint(const glm::vec4& tint) { m_tint = tint; }

		constexpr static uint32_t flag_texture = 1 << 0; //!< 00000001
		constexpr static uint32_t flag_tint = 1 << 1; //!< 00000010

	private:
		uint32_t m_flags = 0; //!< Bitfield representation of the shader settings
		std::shared_ptr<Shader> m_shader; //!< The Materials Shader
		std::shared_ptr<Texture> m_texture; //!< Texture for the material
		glm::vec4 m_tint; //!< Colour tint for geometry
		void setFlag(uint32_t flag) { m_flags = m_flags | flag; }
	};

	/** \class Renderer3D 
	** \brief A class which renders 3D geometry without batching
	*/
	class Renderer3D
	{
	public:
		static void init(); //!< Init the renderer
		static void begin(const SceneWideUniforms& sceneWideUniforms); //!< Begin a new 3D scene
		static void submit(const std::shared_ptr<VertexArray>& geometry, const std::shared_ptr<Material>& material, const glm::mat4& model); //!< Submit a piece of geometry to be rendered
		static void end(); //!< End the current 3D Scene
	private:
		struct InternalData
		{
			SceneWideUniforms sceneWideUniforms; //!< Replace with UBO
			std::shared_ptr<Texture> defaultTexture; //!< Empty white texture
			glm::vec4 defaultTint; //!< Default White tint
		};

		static std::shared_ptr<InternalData> s_data; //!< Data internal to the renderer
	};
}