#pragma once
class ProjectileTemplate
{
public:
	float speed;
	int imageId;
	float imageOrigin[2];
	int glowImageId;
	float glowImageOrigin[2]; 
	bool explodes;

	ProjectileTemplate();
	~ProjectileTemplate();
};

