#pragma once
#include "SceneryObject.h"

class TallCrate : public SceneryObject
{
public:
	TallCrate();
	virtual ~TallCrate();

	// Fix collision rec location 
	virtual void fixCollRec();
};

