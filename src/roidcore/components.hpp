#pragma once

#include <glm/vec2.hpp>
#include <boost/serialization/strong_typedef.hpp>

namespace roidcore
{
	struct position
	{
		glm::vec2 p;
	};

	struct velocity
	{
		glm::vec2 v;
	};
}
