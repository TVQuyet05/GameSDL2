#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define PLAYER_SPEED 10

#define BULLET_OF_PLAYER_SPEED 5


class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	void HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* bullet_sound);
	void DoPlayer(const SDL_Rect& other_object);
	void Show(SDL_Renderer* des);

	void set_bullet_list(std::vector<BulletObject*> bullet_list) { p_bullet_list_ = bullet_list; }
	std::vector<BulletObject*> get_bullet_list() const { return p_bullet_list_; }
	// Init bullet in function HandleInputAction when click left mouse
	void HandleBullet(SDL_Renderer* des);


private:
	int width_frame_;
	int height_frame_;

	std::vector<BulletObject*> p_bullet_list_;
	
};

#endif