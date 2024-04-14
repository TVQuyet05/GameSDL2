
#ifndef EXPLOSION_H_

#define EXPLOSION_H_

#include "CommonFunc.h"
#include "BaseObject.h"

const int EXPLOSION_WIDTH = 50;
const int EXPLOSION_HEIGHT = 50;

class ExplosionObject : public BaseObject
{
public:
	ExplosionObject();
	~ExplosionObject();
	void set_clip();
	void set_frame(const int& fr) { frame_ = fr; }
	int get_frame() const { return frame_; }

	void ShowExplosion(SDL_Renderer* des);
	void set_pos_of_explosion(const SDL_Rect& rect);
	//void ShowExplosionInRect(SDL_Renderer* des, const SDL_Rect& rect);

private:
	int frame_;

	SDL_Rect clip_[6];
};



#endif // !EXPLOSION_H_