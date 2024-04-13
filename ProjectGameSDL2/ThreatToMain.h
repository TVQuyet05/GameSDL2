
#ifndef THREAT_TO_MAIN_H_
#define THREAT_TO_MAIN_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define THREAT_TO_MAIN_SPEED 4
#define BULLET_OF_THREAT_SPEED 6
//#define NUMBERS_BULLET_OF_THREAT 6

class ThreatToMain : public BaseObject
{
public:
	ThreatToMain();
	~ThreatToMain();

	void CalculateAngle(const float& x_dis, const float& y_dis);
	void DoThreat(const SDL_Rect& main, const SDL_Rect& house);

	void set_bullet_list(std::vector<BulletObject*> bullet_list) { p_bullet_list_ = bullet_list; }
	std::vector<BulletObject*> get_bullet_list() const { return p_bullet_list_; }

	void HandleBullet(SDL_Renderer* des);

	void DecreaseBlood() { blood_--; }
	int get_blood() const { return blood_; }

private:
	int width_frame_;
	int height_frame_;

	std::vector<BulletObject*> p_bullet_list_;
	int time_make_bullet_;

	int blood_;
};

#endif // !THREAT_TO_HOUSE_H_
