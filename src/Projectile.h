
class Projectile
{
private:
	short projectileType;
	float previousX;
	float previousY;
	float currentX;
	float currentY;
	float xVector; //The vectors are a function of velocity in the direction of launch towards clicked location
	float yVector;
	int mass; //Mass is the weight of the object
	int size; //Size is relative, no need to calculate area just use different ints to determine whether it is small/medium/large and so on
	bool negligence;
	int UID;//unique identifer number
public:
	Projectile();
	Projectile(short ProjectileType, float CurrentX, float CurrentY, int Mass, int Size, float XVector, float YVector);
	~Projectile();
	//constructor and deconstructor

	void updateProjectile();
	void updateNegligableProjectile();
	void determineNegligance();
	//base update methods, to be inherited and edited within each projectile
	//For different projectiles, if you ask how you want them to behave I can write their update methods
	//ie: arc'ed projectile, beam, fast moving, light, heavy

	short getProjectileType();
	float getCurrentX();
	float getCurrentY();
	bool getNegligence();
	int getUID();
	//getter methods, 

	void setUID(int newUID);
	
};