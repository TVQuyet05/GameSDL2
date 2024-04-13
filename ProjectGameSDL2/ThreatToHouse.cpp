
#include "ThreatToHouse.h"

ThreatToHouse::ThreatToHouse() 
{
	rect_.x = rand() % (SCREEN_WIDTH + 100) - 50;
	if (rect_.x >= -10 && rect_.x <= SCREEN_WIDTH)
	{
		rect_.y = (rand() % 2 == 0) ? -20 : (10 + SCREEN_HEIGHT);
	}
	else
	{
		rect_.y = rand() % (SCREEN_HEIGHT + 120) - 60;
	}
	width_frame_ = 0;
	height_frame_ = 0;
	blood_ = 2;
}

ThreatToHouse::~ThreatToHouse()
{

}

void ThreatToHouse::CalculateAngle() {
	angle_ = 180 + atan2(MIDDLE_SCREEN_WIDTH - rect_.x, MIDDLE_SCREEN_HEIGHT - rect_.y) * 180.0 * -1 / M_PI;
}

bool ThreatToHouse::DoThreat(const SDL_Rect& house)
{
	CalculateAngle();
	float x_dis = MIDDLE_SCREEN_WIDTH - rect_.x;
	float y_dis = MIDDLE_SCREEN_HEIGHT - rect_.y;

	float distance = sqrt(pow(x_dis, 2) + pow(y_dis, 2));
	float f = THREAT_TO_HOUSE_SPEED / distance;

	x_val_ = x_dis * f;
	y_val_ = y_dis * f;

	rect_.x += x_val_;
	rect_.y += y_val_;

	if (CheckCollision(house)) {
		rect_.x -= x_dis * 8 / distance;
		rect_.y -= y_dis * 8 / distance;

		return true;
	}

	return false;
}