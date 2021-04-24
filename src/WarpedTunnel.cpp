#include "WarpedTunnel.hpp"

WarpedTunnel::WarpedTunnel() : 
	moveDirection(0.0f),
	warpDirection(0.0f),
	intensity(0.0f)
{
	type = Model::Type::WarpedTunnel;
}
