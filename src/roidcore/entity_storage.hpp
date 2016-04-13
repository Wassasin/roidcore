#pragma once

#include <roidcore/entities.hpp>

#include <vector>
#include <boost/optional.hpp>

namespace roidcore
{
	template<typename T>
	class entity_storage
	{
		typedef boost::optional<T> entry_t;

		std::vector<entry_t> buffer;
		size_t first_empty;

	public:
		entity_storage()
			: buffer()
			, first_empty(1) // One after end of buffer
		{}

		void reserve(size_t n)
		{
			buffer.reserve(n);
		}

		entity_id<T> emplace_fast(T&& x)
		{
			if(first_empty >= buffer.size())
				first_empty++;
			
			buffer.emplace_back(std::move(x));
			return entity_id<T>(buffer.size()-1);
		}

		entity_id<T> emplace(T&& x)
		{
			if(first_empty >= buffer.size())
			{
				buffer.emplace_back(std::move(x));
				first_empty++;
				return entity_id<T>(buffer.size()-1);
			}

			assert(!buffer[first_empty]);
			buffer[first_empty].reset(std::move(x));

			for(first_empty++; first_empty < buffer.size(); ++first_empty)
			{
				if(!buffer[first_empty])
					return;
			}

			// In last case, first_empty = buffer.size()+1
		}

		template<typename F>
		void foreach(F f)
		{
			for(size_t i = 0; i < buffer.size(); ++i)
			{
				auto& entry_opt = buffer[i];
				if(entry_opt)
					f(entity_id<T>(i), *entry_opt);
			}
		}
		
		template<typename F>
		void foreach(F f) const
		{
			for(size_t i = 0; i < buffer.size(); ++i)
			{
				auto& entry_opt = buffer[i];
				if(entry_opt)
					f(entity_id<T>(i), *entry_opt);
			}
		}
	};
}
