#include "Utilities.h"

float lerp(const float& current, const float& target, const float& scale)
{
	return current + (target - current) * scale;
}