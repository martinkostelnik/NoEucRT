/**
 * @file Portal.cpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Implementation file of the Portal class.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Portal.hpp"

Portal::Portal() :
	exit(0.0f),
	center(0.0f)
{
	type = Model::Type::Portal;
}
