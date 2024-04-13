
#ifndef BULLET_OBJECT_H_

#define BULLET_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"

class BulletObject : public BaseObject
{
public:	
	BulletObject();
	~BulletObject();

	void set_speed_of_bullet(const float& speed) { speed_of_bullet_ = speed; }
	void set_angle_of_bullet(const float& angle) { angle_ = angle; }

	void set_is_move(const bool& isMove) { is_move_ = isMove; }
	bool get_is_move() const { return is_move_; }

	
	void HandleMove(const int& x_border, const int& y_border);

private:
	
	bool is_move_;
	float speed_of_bullet_;

};
#endif // !BULLET_OBJECT_HH
