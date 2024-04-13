
#include "BulletObject.h"

BulletObject::BulletObject()
{
	speed_of_bullet_ = 0;
	is_move_ = false;
}

BulletObject::~BulletObject()
{

}

void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
	//std::cout << angle_ << "\n";
	float angle_radian = angle_ / 180.0 * M_PI;
	x_val_ = speed_of_bullet_ * cos(angle_radian);
	y_val_ = sqrt(pow(speed_of_bullet_, 2) - pow(x_val_, 2));

	if (angle_ < 0 || angle_ > 180) y_val_ = y_val_ * -1;

	rect_.x += x_val_;
	rect_.y += y_val_;

	if (rect_.x > x_border || rect_.x < 0 || rect_.y > y_border || rect_.y < 0)
	{
		is_move_ = false;
	}
}