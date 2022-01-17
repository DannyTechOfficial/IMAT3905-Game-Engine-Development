/** \file Renderer2D.h */
#pragma once

#include <glm/glm.hpp>
#include "rendering/RendererCommon.h"

namespace Engine
{
	/**
\class Quad
Simple Quad class to manage vectors.
*/
	class Quad
	{
	public:
		Quad() = default;
		static Quad createCentreHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents);
	private:
		glm::vec3 m_translate = glm::vec3(0.f); //!< Translate vector
		glm::vec3 m_scale = glm::vec3(1.f); //!< Scale Vector
		friend class Renderer2D;
	};

	/** \class Renderer2D
	** \brief Class which allows the renderering of simple 2D primitives
	*/
	class Renderer2D
	{
	public:
		static void init();
		static void begin(const SceneWideUniforms& swu); //!< Begin a 2D scene
		static void submit(const Quad& quad, const glm::vec4& tint); //!< Render a tinted quad
		static void submit(const Quad& quad, const std::shared_ptr<Texture>& texture); //!< Render a textured quad
		static void submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Texture>& texture); //!< Render a textured and tinted quad;
		static void submit(const Quad& quad, const std::shared_ptr<Texture>& texture, float angle, bool degrees = false);
		static void submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees = false);
		static void submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<Texture>& texture, float angle, bool degrees = false);
		static void end();

	private:
		struct InternalData
		{
			std::shared_ptr<Texture> defaultTexture;
			glm::vec4 defaultTint;
			std::shared_ptr<Shader> shader;
			std::shared_ptr<VertexArray> VAO;
			glm::mat4 model;
		};

		static std::shared_ptr<InternalData> s_data;
	};

}