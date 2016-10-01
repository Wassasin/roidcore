#pragma once

#include <roidcore/components.hpp>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/vector.hpp>

#include <roidcore/util.hpp>

namespace roidcore
{
	struct ship
	{
		ship(ship const&) = delete;

		position p;
		velocity v;
	};

	struct station
	{
		station(station const&) = delete;

		position p;
	};

	typedef boost::fusion::vector<
		ship,
		station
	> entities_list;
	typedef uint8_t entities_e;

	struct entity_dyn_id
	{
		entities_e type;
		size_t id;
	};

	template<typename T>
	struct entity_id
	{
		static const entities_e type = get_first_index<entities_list, T>::value;
		size_t id;

		entity_id(size_t id)
			: id(id)
		{}

		entity_dyn_id get_dyn_id() const
		{
			return {type, id};
		}
	};

	template<typename T>
	struct entity_t
	{
		entity_id<T> const id;
		T x;
	};
}

BOOST_FUSION_ADAPT_STRUCT(
	roidcore::ship,
	(roidcore::position, p)
	(roidcore::velocity, v)
)

BOOST_FUSION_ADAPT_STRUCT(
	roidcore::station,
	(roidcore::position, p)
)
