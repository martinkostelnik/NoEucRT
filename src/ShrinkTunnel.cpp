/**
 * @file ShrinkTunnel.cpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Implementation file of the ShrinkTunnel class.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ShrinkTunnel.hpp"

ShrinkTunnel::ShrinkTunnel() :
	direction(0.0f),
	finalSize(0.0f),
	length(0.0f),
	ceiling(0.0f)
{
	type = Model::Type::ShrinkTunnel;
}
