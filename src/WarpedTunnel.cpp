/**
 * @file WarpedTunnel.cpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Implementation file of the WarpedTunnel class.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "WarpedTunnel.hpp"

WarpedTunnel::WarpedTunnel() :
	warpDirection(0.0f),
	intensity(0.0f),
	compressed(true)
{
	type = Model::Type::WarpedTunnel;
}
