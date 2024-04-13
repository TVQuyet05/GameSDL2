
#ifndef THREAT_TO_HOUSE_H_
#define THREAT_TO_HOUSE_H_

#include "CommonFunc.h"
#include "BaseObject.h"

#define THREAT_TO_HOUSE_SPEED 2

class ThreatToHouse : public BaseObject
{
public:
	ThreatToHouse();
	~ThreatToHouse();

	void CalculateAngle();
	bool DoThreat(const SDL_Rect& house);

	void DecreaseBlood() { blood_--; }
	int get_blood() const { return blood_; }

private:
	int width_frame_;
	int height_frame_;

	int blood_;
};
#endif // !THREAT_TO_HOUSE_H_
