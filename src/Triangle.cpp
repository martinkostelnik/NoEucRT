/**
 * @file Triangle.cpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Implementation file of the Triangle class.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Triangle.hpp"

Triangle::Triangle(const glm::vec4& v1, const glm::vec4& v2, const glm::vec4& v3) :
	v1(v1),
	v2(v2),
	v3(v3)
{
}
