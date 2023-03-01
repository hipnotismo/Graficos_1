#ifndef TILE_H
#define TILE_H
//============================================
#include "Sprite.h"
//============================================
class ENGINE_API Tile : public Sprite
{
public:
	 Tile();
	 ~Tile();

	 bool isWalkable();
	 void walkability(bool bWalkable);

	 unsigned int getId();
	 void setId(unsigned int id);

private:
	unsigned int _id;
	bool _walkable;
};
//============================================
#endif
