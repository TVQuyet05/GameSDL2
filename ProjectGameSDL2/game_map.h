
#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_TILES 20

class TileMap : public BaseObject
{
public:
	TileMap() { ; }
	~TileMap() { ; }
};

// tile map tuong tu baseobject co cac so lieu , texture p_object, ...
// tile map la dinh dang hinh anh mot o map la gi


class GameMap
{
public:
	GameMap() { ; }
	~GameMap() { ; }

	void LoadMap(const char* name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	Map getMap() const { return game_map_; }
	void SetMap(Map& map_data) { game_map_ = map_data;}


private:
	Map game_map_;
	TileMap tile_map[MAX_TILES];
};

#endif // !GAME_MAP_H_
