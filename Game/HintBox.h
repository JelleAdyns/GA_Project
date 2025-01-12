#ifndef HINTBOX_H
#define HINTBOX_H

#include <Engine.h>
#include "structsf.h"

struct HintBox
{
	tstring HintText{};
	float VisibleTime{};
	Rectf DestRect{ 0,0,100,100 };
	bool FollowPlayer{};
};

#endif // !HINTBOX_H
