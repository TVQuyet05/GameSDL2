
#include "ThreatToMain.h"

ThreatToMain::ThreatToMain()
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

	time_make_bullet_ = 1;

	blood_ = 4;
}

ThreatToMain::~ThreatToMain()
{

}

void ThreatToMain::CalculateAngle(const float& x_dis, const float& y_dis)
{
	angle_ = 180 + atan2(x_dis, y_dis) * 180 * -1 / M_PI;
}

void ThreatToMain::DoThreat(const SDL_Rect& main, const SDL_Rect& house)
{
	float x_dis = main.x + main.w / 2 - (rect_.x + rect_.w / 2);
	float y_dis = main.y + main.h / 2 - (rect_.y + rect_.h / 2);

	CalculateAngle(x_dis, y_dis);

	float distance = sqrt(pow(x_dis, 2) + pow(y_dis, 2));

	if (distance >= 300) 
	{
		float f = THREAT_TO_MAIN_SPEED / distance;

		x_val_ = x_dis * f;
		y_val_ = y_dis * f;

	}
	else if (distance >= 200)
	{
		x_val_ = 0;
		y_val_ = 0;
	}
	else
	{
		x_val_ = - x_dis * 5 / distance;
		y_val_ = - y_dis * 5 / distance;
	}

	
	rect_.x += x_val_;
	rect_.y += y_val_;

}

void ThreatToMain::HandleBullet(SDL_Renderer* des)
{
	for (int i = 0; i < p_bullet_list_.size(); i++)
	{
		BulletObject* p_bullet = p_bullet_list_.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move() == true)
			{
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_bullet->Render(des);
			}
			else
			{
				p_bullet_list_.erase(p_bullet_list_.begin() + i);
				if (p_bullet != NULL)
				{
					delete p_bullet;
					p_bullet = NULL;
				}
			}
		}
	}

	time_make_bullet_--;

	// Init bullet of threat to main
	if (time_make_bullet_ == 0 /*&& p_bullet_list_.size() < NUMBERS_BULLET_OF_THREAT*/)
	{
		BulletObject* p_bullet = new BulletObject();
		p_bullet->LoadImg("image/bullet_of_threat.png", des);

		p_bullet->set_angle_of_bullet(angle_ - 90);
		p_bullet->set_speed_of_bullet(BULLET_OF_THREAT_SPEED);

		p_bullet->SetRect(this->rect_.x + this->rect_.w / 2 - 16, this->rect_.y + this->rect_.h / 2 - 3);

		p_bullet->set_is_move(true);
		p_bullet_list_.push_back(p_bullet);

		time_make_bullet_ = 20;
	}
}