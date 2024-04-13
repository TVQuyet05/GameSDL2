
#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "CommonFunc.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();

	void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; }
	SDL_Rect GetRect() const { return rect_; }
	SDL_Texture* GetObject() const { return p_object_; }

	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();

	bool CheckCollision(const SDL_Rect& object2);

protected:
	SDL_Texture* p_object_;
	SDL_Rect rect_;

	float x_val_;
	float y_val_;

	float angle_;
};


#endif // !BASE_OBJECT_H
