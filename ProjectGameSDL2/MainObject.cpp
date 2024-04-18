#include "MainObject.h"

MainObject::MainObject()
{
	width_frame_ = 0;
	height_frame_ = 0;
	
	/*input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.down_ = 0;
	input_type_.up_ = 0;*/
}

MainObject::~MainObject()
{

}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* bullet_sound)
{
	// Control the character with the keyboard
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
			case SDLK_UP:
			{
				y_val_ = - PLAYER_SPEED;
				break;
			}
			case SDLK_DOWN:
			{
				y_val_ = PLAYER_SPEED;
				break;
			}
			case SDLK_RIGHT:
			{
				x_val_ = PLAYER_SPEED;
				break;
			}
			case SDLK_LEFT:
			{
				x_val_ = - PLAYER_SPEED;
				break;
			}
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
			case SDLK_UP:
			{
				y_val_ = 0;
				break;
			}
			case SDLK_DOWN:
			{
				y_val_ = 0;
				break;
			}
			case SDLK_RIGHT:
			{
				x_val_ = 0;
				break;
			}
			case SDLK_LEFT:
			{
				x_val_ = 0;
				break;
			}
		}
	}

	// Calculate angle of player
	if (events.type == SDL_MOUSEMOTION)
	{
		int x_mouse = events.motion.x;
		int y_mouse = events.motion.y;

		angle_ = 90 + atan2(x_mouse - rect_.x, y_mouse - rect_.y) * 180.0 * -1 / M_PI;
	}

	// Init bullet of player when click left mouse
	if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		if (events.button.button == SDL_BUTTON_LEFT)
		{
			BulletObject* p_bullet = new BulletObject();
			p_bullet->LoadImg("image/bullet_of_player.png", screen);

			p_bullet->set_angle_of_bullet(angle_);
			p_bullet->set_speed_of_bullet(BULLET_OF_PLAYER_SPEED);
			p_bullet->SetRect(this->rect_.x + this->rect_.w/2 - 16, this->rect_.y + this->rect_.h/2 - 3);

			p_bullet->set_is_move(true);
			p_bullet_list_.push_back(p_bullet);

			Mix_PlayChannel(-1, bullet_sound, 0);
		}
	}
	 
}

void MainObject::DoPlayer(const SDL_Rect& other_object) 
{
	rect_.x += x_val_;

	if (rect_.x < 0 || rect_.x + 80 > SCREEN_WIDTH || CheckCollision(other_object)) rect_.x -= x_val_;



	rect_.y += y_val_;

	if (rect_.y < 0 || rect_.y + 80 > SCREEN_HEIGHT || CheckCollision(other_object)) rect_.y -= y_val_;

	//std::cout << rect_.x << " " << rect_.y << "\n";
	
}

void MainObject::HandleBullet(SDL_Renderer* des)
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
}

void MainObject::Show(SDL_Renderer* des)
{
	

	Render(des, NULL);
}