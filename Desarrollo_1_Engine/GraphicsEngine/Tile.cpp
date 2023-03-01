#include "Tile.h"
//================================================
Tile::Tile() {
	_id = 0;
	_walkable = false;
}
//================================================
Tile::~Tile() {
}
//================================================
bool Tile::isWalkable() {
	if (!_walkable)
		return false;

	else
		return true;
}
//================================================
void Tile::walkability(bool bWalkable) {
	_walkable = bWalkable;
}
//================================================
unsigned int Tile::getId() {
	return _id;
}
//================================================
void Tile::setId(unsigned int id) {
	_id = id;
}
//================================================