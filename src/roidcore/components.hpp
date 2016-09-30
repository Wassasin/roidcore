#pragma once

#include <glm/vec2.hpp>

namespace roidcore
{
	struct velocity : glm::vec2
	{
		velocity()
		: glm::vec2()
		{}
		
		velocity(glm::vec2&& v)
		: glm::vec2(std::move(v))
		{}

		velocity(float x, float y)
		: glm::vec2(x, y)
		{}
	};
	
	struct position : glm::vec2
	{
		position() = default;
		
		position(glm::vec2&& v)
		: glm::vec2(std::move(v))
		{}

		position(float x, float y)
		: glm::vec2(x, y)
		{}
	
		position& operator+=(velocity const& p)
		{
			return this->operator+=(static_cast<glm::vec2>(p));
		}
	};
}
