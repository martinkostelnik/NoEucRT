#include "AABB.hpp"

#include <limits>

AABB::AABB() :
	min(std::numeric_limits<float>::infinity()),
	max(-std::numeric_limits<float>::infinity())
{
}
