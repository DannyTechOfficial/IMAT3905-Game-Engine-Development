/** \file RendererCommon.h */
#pragma once

#include "glm/glm.hpp"
#include <unordered_map>
#include <memory>
#include "rendering/shaderDataType.h"
#include "rendering/vertexArray.h"
#include "rendering/texture.h"
#include "rendering/shader.h"

namespace Engine
{
	using SceneWideUniforms = std::unordered_map<const char *, std::pair<ShaderDataType, void *>>; //!< Declares SceneWideUniforms in dedicated space.
}