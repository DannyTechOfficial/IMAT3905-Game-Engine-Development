/* \file renderAPI.h */
#pragma once

namespace Engine
{
	class RenderAPI
	{
	public:
		enum class API { None = 0, OpenGL = 1, Direct3D = 2, Vulkan = 3};
		inline static API getAPI() { return s_API; }
	private:
		static API s_API;
	};
}
