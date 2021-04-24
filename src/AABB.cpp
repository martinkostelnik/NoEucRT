/**
 * @file AABB.cpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Implementation file of the AABB class.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "AABB.hpp"

#include <limits>

AABB::AABB() :
	min(std::numeric_limits<float>::infinity()),
	max(-std::numeric_limits<float>::infinity())
{
}
