
#include "ExplosionObject.h"

ExplosionObject::ExplosionObject()
{
	frame_ = 0;
}

ExplosionObject::~ExplosionObject()
{

}

void ExplosionObject::set_clip()
{
	for (int i = 0; i < 6; i++)
	{
		clip_[i].x = i * EXPLOSION_WIDTH;
		clip_[i].y = 0;
		clip_[i].w = EXPLOSION_WIDTH;
		clip_[i].h = EXPLOSION_HEIGHT;
	}
}

void ExplosionObject::ShowExplosion(SDL_Renderer* des)
{
	/*if (frame_ >= 6)
	{
		frame_ = 0;
	}*/

	SDL_Rect renderQuad = { rect_.x, rect_.y, EXPLOSION_WIDTH, EXPLOSION_HEIGHT };
	SDL_RenderCopy(des, p_object_, &clip_[frame_], &renderQuad);
	//SDLCommonFunc::ApplySurfaceClip(this->p_object_, des, &clip_[frame_], rect_.x, rect_.y);

	frame_++;
}

void ExplosionObject::set_pos_of_explosion(const SDL_Rect& rect)
{
	rect_.x = (rect.x + rect.w * 0.5) - EXPLOSION_WIDTH * 0.5;
	rect_.y = (rect.y + rect.h * 0.5) - EXPLOSION_HEIGHT * 0.5;
}

//void ExplosionObject::ShowExplosionInRect(SDL_Renderer* des, const SDL_Rect& rect)
//{
//	for (int ex = 0; ex < 6; ex++)
//	{
//		int x_pos = (rect.x + rect.w * 0.5) - EXPLOSION_WIDTH * 0.5;
//		int y_pos = (rect.y + rect.h * 0.5) - EXPLOSION_HEIGHT * 0.5;
//
//		set_frame(ex);
//		SetRect(x_pos, y_pos);
//		ShowExplosion(des);
//
//		SDL_Delay(200);
//
//		// Update each image of explosion
//		SDL_RenderPresent(des);
//
//	}
//}