/**
 * @file RotationTunnel.cpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Implementation file of the RotationTunnel class.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "RotationTunnel.hpp"

RotationTunnel::RotationTunnel() :
	direction(0.0f),
	maxRotation(0.0f),
	length(0.0f),
	axes(0.0f)
{
	type = Model::Type::RotationTunnel;
}
