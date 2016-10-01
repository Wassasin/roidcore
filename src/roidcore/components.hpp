#pragma once

#include <glm/vec2.hpp>
#include <boost/strong_typedef.hpp>

namespace roidcore
{
	struct vec2like : public glm::vec2
	{
		using glm::vec2::vec2;

		vec2like(vec2like&) = delete;

		/*
		bool operator<(const vec2like& rhs) const
		{
			return false;
		}
		*/
	};

	//BOOST_STRONG_TYPEDEF(vec2like, velocity);
	//BOOST_STRONG_TYPEDEF(vec2like, position);

	struct velocity : public vec2like
	{
		using vec2like::vec2like;
	};
	struct position : public vec2like
	{
		using vec2like::vec2like;
	};

	position& operator+=(position& p, const velocity& v)
	{
		p += v;
		return p;
	}
}
