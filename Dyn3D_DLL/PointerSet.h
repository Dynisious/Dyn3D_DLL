#pragma once

#include "stdafx.h"
#include <unordered_set>

namespace PointerSet {

	/*
	An unordered set of Pointers to "Type" which determines sameness by the
	value the pointers point to rather than the pointers themselves.*/
	template<typename Type>
	struct _PS {
		struct P_hash : std::hash<Type*> {
			size_t operator()(Type* pnt) const {
				if (pnt)
					return hash<Type>()(*pnt);
				return 0;
			}
		};

		typedef std::unordered_set<Type*, P_hash> Set;
	};

};
