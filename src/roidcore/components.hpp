#pragma once

#include <glm/vec2.hpp>

namespace roidcore
{
	template<typename SELF>
	struct vec2like
	{
		float x, y;

		vec2like() = default;
		vec2like(vec2like&&) = default;
		
		vec2like(float _x, float _y)
		: x(_x)
		, y(_y)
		{}
	};

	struct velocity : public vec2like<velocity>
	{
		using vec2like<velocity>::vec2like;
	};
	
	struct position : public vec2like<position>
	{
		using vec2like<position>::vec2like;
		
		position& operator+=(velocity const& v)
		{
			x += v.x;
			y += v.y;
			return *this;
		}
	};
}
